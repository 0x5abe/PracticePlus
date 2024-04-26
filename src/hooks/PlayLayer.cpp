#include "PlayLayer.hpp"
#include <filesystem>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <managers/StartpointManager.hpp>
#include <hooks/GJGameLevel.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>
#include <util/algorithm.hpp>

using namespace geode::prelude;

#define SPF_EXT ".spf"

static char s_spfMagicAndVer[] = "SPF v0.0.1 lol ";

// overrides

bool PPPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
	// reset uniqueID global to save/load GameObjects correctly using their index
	// should look into not having to do this but it's harder than it looks since there's 
	// probably maps with object id as keys, it's not just us saving pointers so I'd have to find those.
	*reinterpret_cast<int*>(geode::base::get()+0x4ea028) = 10;
	m_fields->m_uniqueIdBase = *reinterpret_cast<int*>(geode::base::get()+0x4ea028) + 2;

	if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

	setupKeybinds();
	return true;
}

void PPPlayLayer::createObjectsFromSetupFinished() {
	if (m_fields->m_startedLoadingStartpoints) {
		return;
	}
	PlayLayer::createObjectsFromSetupFinished();
}

void PPPlayLayer::setupHasCompleted() {
	//log::info("[setupHasCompleted] begin");
	if (!m_fields->m_finishedLoadingStartpoints) {
		//log::info("[setupHasCompleted] hasnt finished loading SP");

		loadStartpoints();
		
		//m_fields->m_startpointLoadingProgress += (m_fields->m_startpointLoadingProgress/8.0f);
		log::info("[setupHasCompleted] m_bytesRead: {}", m_fields->m_bytesRead);
		log::info("[setupHasCompleted] m_bytesToRead: {}", m_fields->m_bytesToRead);
		if (m_fields->m_bytesToRead > 0) {
			m_fields->m_startpointLoadingProgress = (static_cast<float>(m_fields->m_bytesRead)/static_cast<float>(m_fields->m_bytesToRead));
		}
		// if (m_fields->m_startpointLoadingProgress != 1.0f) {
		m_loadingProgress = m_fields->m_startpointLoadingProgress;
		// } else {
		// 	m_loadingProgress = 0.99f;
		// }
		log::info("[setupHasCompleted] m_loadingProgress: {}", m_loadingProgress);
	}
	if (m_fields->m_finishedLoadingStartpoints) {
		log::info("[setupHasCompleted] finished loading SP");
		m_loadingProgress = 1.0f;
		PlayLayer::setupHasCompleted();

		//StartpointManager::get().fetchStartpointsFromTempStorage();
		m_fields->m_startedLoadingStartpoints = false;
		m_fields->m_finishedLoadingStartpoints = false;
		m_fields->m_startpointLoadingProgress = 0.0f;
		m_fields->m_bytesToRead = 0;
		m_fields->m_bytesRead = 0;
	}
}

void PPPlayLayer::resetLevel() {
	CCObject* l_checkpoint = m_checkpointArray->lastObject();
	if (!l_checkpoint && isPlusMode() && getActiveStartpointId() != -1) {
		m_checkpointArray->addObject(StartpointManager::get().m_startpoints->objectAtIndex(getActiveStartpointId()));
	}

	PlayLayer::resetLevel();

	if (!l_checkpoint && isPlusMode() && getActiveStartpointId() != -1) {
		m_checkpointArray->removeLastObject();
	}
}

void PPPlayLayer::togglePracticeMode(bool i_value) {
	togglePlusMode(i_value);

	PlayLayer::togglePracticeMode(i_value);
}

void PPPlayLayer::updateVisibility(float i_unkFloat) {
	PlayLayer::updateVisibility(i_unkFloat);

	if (!isPlusMode()) {
		StartpointManager::get().updatePlusModeVisibility();
	}
}

void PPPlayLayer::onQuit() {
	if (!m_fields->m_onQuitCalled) {
		removeAllStartpoints(true);
		m_fields->m_onQuitCalled = true;
	}
	PlayLayer::onQuit();
}

// custom methods

void PPPlayLayer::createStartpoint() {
	PPCheckpointObject* l_startpoint =  static_cast<PPCheckpointObject*>(PlayLayer::createCheckpoint());
	l_startpoint->m_fields->m_percentage = PlayLayer::getCurrentPercent();
	addStartpoint(StartpointManager::get().createStartpoint(l_startpoint, m_player1->getPosition()));

	//Todo: see if we want to save to file here, make it so it only saves the changes instead of the whole thing
	// probably better to use Actions than threading, save one SP per tick of the action
}

void PPPlayLayer::addStartpoint(PPCheckpointObject* i_startpoint, int i_index) {
	PlayLayer::addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

bool PPPlayLayer::removeStartpoint(int i_index) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	CheckpointObject* l_startpoint = l_startpointManager.getStartpoint(i_index);
	if (!l_startpoint) return false;
	PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
	l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
	if (l_startpoint == l_startpointManager.getActiveStartpoint()) {
		StartpointManager::get().setActiveStartpointId(l_startpointManager.getActiveStartpointId()-1);
	}
	l_startpointManager.removeStartpoint(i_index);

	//Todo: see if we want to save to file here, make it so it only saves the changes instead of the whole thing
	// probably better to use Actions than threading, save one SP per tick of the action
	return true;
}

void PPPlayLayer::removeAllStartpoints(bool i_reset) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	CheckpointObject* l_startpoint;
	for (int i = 0; i < l_startpointManager.getStartpointCount(); i++) {
		l_startpoint = l_startpointManager.getStartpoint(i);
		if (!l_startpoint) continue;
		//Todo: see wth happens here (has crashed before)
		PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
		l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
		//EndTodo
	}
	l_startpointManager.removeAllStartpoints(i_reset);
}

bool PPPlayLayer::checkLevelStringHash() {
	unsigned int l_savedLevelStringHash;
	InputStream& l_inputStream = StartpointManager::get().m_inputStream;

	l_inputStream >> l_savedLevelStringHash;
	
	if (l_savedLevelStringHash != util::algorithm::hash_string(m_level->m_levelString.c_str())) {
		//Todo: let user decide what to do with a warning
		log::info("!!!!!!!!!!!!! Mismatch LevelString HASH !!!!!!!!!!!!!!!");
		return false;
		//EndTodo
	}
	return true;
}

bool PPPlayLayer::readSpfHeader() {
	InputStream& l_inputStream = StartpointManager::get().m_inputStream;
	l_inputStream.ignore(sizeof(s_spfMagicAndVer));
	return checkLevelStringHash();
}

void PPPlayLayer::loadStartpoints() {
	StartpointManager& l_startpointManager = StartpointManager::get();

	if (!m_fields->m_startedLoadingStartpoints) {
		log::info("[setupHasCompleted] started loading SP");
		m_fields->m_startedLoadingStartpoints = true;
		m_fields->m_startpointLoadingProgress = 0.0f;

		std::string l_filePath = getStartpointFilePath(true);
		if (l_filePath == "") {
			goto finishedLoading;
		}

		m_fields->m_bytesToRead = std::filesystem::file_size(l_filePath);
		m_fields->m_bytesRead = 0;
		InputStream& l_inputStream = StartpointManager::get().m_inputStream;
		if(!l_inputStream.setFileToRead(l_filePath, &m_fields->m_bytesRead)) {
			goto finishedLoading;
		}
		
		if (!readSpfHeader()) {
			goto finishedLoading;
		}

		l_inputStream >> m_fields->m_remainingStartpointLoadCount;
		log::info("Remaining startpoints: {}", m_fields->m_remainingStartpointLoadCount);
	}
	log::info("Remaining startpoints: {}", m_fields->m_remainingStartpointLoadCount);
	if (m_fields->m_remainingStartpointLoadCount > 0) {
		l_startpointManager.loadOneStartpointFromStream();
		m_fields->m_remainingStartpointLoadCount--;
	}
	if (m_fields->m_remainingStartpointLoadCount == 0) {
		finishedLoading:
			m_fields->m_finishedLoadingStartpoints = true;
			return;
	}
}

void PPPlayLayer::writeSpfHeader() {
	OutputStream& l_outputStream = StartpointManager::get().m_outputStream;
	l_outputStream.write(s_spfMagicAndVer,sizeof(s_spfMagicAndVer));
	unsigned int l_levelStringHash = util::algorithm::hash_string(m_level->m_levelString.c_str());
	l_outputStream << l_levelStringHash;
}

void PPPlayLayer::saveStartpoints() {
	reinterpret_cast<PPGJGameLevel*>(m_level)->describe();
	
	std::string l_filePath = getStartpointFilePath();
	
	OutputStream& l_outputStream = StartpointManager::get().m_outputStream;
	if (!l_outputStream.setFileToWrite(l_filePath)) {
		goto finishedSaving;
	}
	
	writeSpfHeader();

	StartpointManager::get().saveStartpointsToStream();

	finishedSaving:
		m_fields->m_startedLoadingStartpoints = false;
		m_fields->m_finishedSavingStartpoints = true;
		return;
}

bool PPPlayLayer::setActiveStartpointAndReload(int i_index) {
	StartpointManager::get().setActiveStartpointId(i_index);
	reloadFromActiveStartpoint();
	return true;
}

void PPPlayLayer::reloadFromActiveStartpoint() {
	while (m_checkpointArray->count() > 0) {
		PlayLayer::removeCheckpoint(false);
	}
	resetLevel();
}

void PPPlayLayer::togglePlusMode(bool i_value) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	l_startpointManager.togglePlusMode(i_value);
	l_startpointManager.updatePlusModeLogic();
	l_startpointManager.updatePlusModeVisibility();
}

inline std::string PPPlayLayer::getStartpointFilePath(bool i_checkExists) {
	std::string l_filePath = Mod::get()->getSaveDir().generic_string();
	
	switch(m_level->m_levelType) {
		case GJLevelType::Local:
			l_filePath.append(std::format("/startpoints/local/{}{}", m_level->m_levelID.value(), SPF_EXT));
			break;
		case GJLevelType::Editor:
			l_filePath.append(std::format("/startpoints/editor/{}_rev{}{}", m_level->m_levelName.c_str(), m_level->m_levelRev, SPF_EXT));
			break;
		case GJLevelType::Saved:
		default:
			l_filePath.append(std::format("/startpoints/online/{}{}", m_level->m_levelID.value(), SPF_EXT));
			break;
	}
	log::info("Filepath: \"{}\"", l_filePath);
	if (i_checkExists && !std::filesystem::exists(l_filePath)) {
		log::info("File doesnt exist: {}", l_filePath);
		return "";
	}
	return l_filePath;
}

void PPPlayLayer::setupKeybinds() {
	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			bool l_player1IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player1)+0x81a);
			bool l_player2IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player2)+0x81a);
			if (event->isDown() && !l_player1IsLocked && !l_player2IsLocked && !m_player1->m_isDead && isPlusMode()) {
				if (!m_fields->m_startedSavingStartpoints) {
					createStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"place-sp"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			bool l_player1IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player1)+0x81a);
			bool l_player2IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player2)+0x81a);
			if (event->isDown() && !l_player1IsLocked && !l_player2IsLocked && isPlusMode()) {
				if (!m_fields->m_startedSavingStartpoints) {
					removeStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"remove-sp"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			bool l_player1IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player1)+0x81a);
			bool l_player2IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player2)+0x81a);
			if (event->isDown() && !l_player1IsLocked && !l_player2IsLocked && isPlusMode()) {
				if (StartpointManager::get().prevStartpoint()) {
					reloadFromActiveStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"switch-sp-prev"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			bool l_player1IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player1)+0x81a);
			bool l_player2IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player2)+0x81a);
			if (event->isDown() && !l_player1IsLocked && !l_player2IsLocked && isPlusMode()) {
				if (StartpointManager::get().nextStartpoint()) {
					reloadFromActiveStartpoint();
				}
			}
			return ListenerResult::Propagate;
		},
		"switch-sp-next"_spr
	);

	// TodoRemove
	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				//removeAllStartpoints(false);
				//m_fields->m_startedLoadingStartpoints = false;
				//InputStream l_ifstream = InputStream("./testPlayerCheckpoint.spf");
				//StartpointManager::get().loadStartpointsFromStream(l_ifstream);
			}
			return ListenerResult::Propagate;
		},
		"test-key-1"_spr
	);

	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			if (event->isDown() && isPlusMode()) {
				m_fields->m_startedLoadingStartpoints = true;
				m_fields->m_finishedSavingStartpoints = false;
				saveStartpoints();
			}
			return ListenerResult::Propagate;
		},
		"test-key-2"_spr
	);
	// EndTodo
}