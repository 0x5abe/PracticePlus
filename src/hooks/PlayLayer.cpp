#include "PlayLayer.hpp"
#include "Geode/Enums.hpp"
#include "Geode/binding/PlayLayer.hpp"
#include "Geode/c++stl/string.hpp"
#include "Geode/cocos/platform/CCFileUtils.h"
#include <Geode/binding/CheckpointObject.hpp>
#include <filesystem>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <ghc/filesystem.hpp>
#include <managers/StartpointManager.hpp>
#include <hooks/GJGameLevel.hpp>
#include <mutex>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>
#include <util/algorithm.hpp>

using namespace geode::prelude;

#define SPF_EXT ".spf"

static char s_spfMagicAndVer[] = "SPF v0.0.1 lol ";
static std::thread s_ioThread = std::thread(&PPPlayLayer::ioThreadUpdate);
static std::mutex s_ioMutex;
static std::condition_variable s_ioConditionVar;

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
	//std::unique_lock<std::mutex> l_ul(s_ioMutex);
	log::info("[setupHasCompleted] begin");
	if (!m_fields->m_finishedLoadingStartpoints) {
		log::info("[setupHasCompleted] hasnt finished loading SP");
		if (!m_fields->m_startedLoadingStartpoints) {
			log::info("[setupHasCompleted] starting SP load");
			m_fields->m_startedLoadingStartpoints = true;
			m_fields->m_startpointLoadingProgress = 0.0f;
			s_ioConditionVar.notify_one();

			log::info("[setupHasCompleted] unlocked ioThread");
			//Todo send signal to load startpoints and update accordingly
			//loadStartpoints();
			//EndTodo
		}
		
		//m_fields->m_startpointLoadingProgress += (m_fields->m_startpointLoadingProgress/8.0f);
		log::info("[setupHasCompleted] m_bytesRead: {}", m_fields->m_bytesRead);
		log::info("[setupHasCompleted] m_bytesToRead: {}", m_fields->m_bytesToRead);
		if (m_fields->m_bytesToRead > 0) {
			m_fields->m_startpointLoadingProgress = (static_cast<float>(m_fields->m_bytesRead)/static_cast<float>(m_fields->m_bytesToRead));
		}
		m_loadingProgress = m_fields->m_startpointLoadingProgress;
		log::info("[setupHasCompleted] m_loadingProgress: {}", m_loadingProgress);

		// if (m_fields->m_startpointLoadingProgress >= 1.0f) {
		// 	m_fields->m_finishedLoadingStartpoints = true;
		// }
	}
	if (m_fields->m_finishedLoadingStartpoints) {
		log::info("[setupHasCompleted] finished loading SP");
		m_loadingProgress = 1.0f;
		PlayLayer::setupHasCompleted();

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
	return true;
}

void PPPlayLayer::removeAllStartpoints(bool i_reset) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	CheckpointObject* l_startpoint;
	for (int i = 0; i < l_startpointManager.getStartpointCount(); i++) {
		l_startpoint = l_startpointManager.getStartpoint(i);
		if (!l_startpoint) continue;
		PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
		l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
	}
	l_startpointManager.removeAllStartpoints(i_reset);
}

void PPPlayLayer::loadStartpoints() {
	//reinterpret_cast<PPGJGameLevel*>(m_level)->describe();
	unsigned int l_savedLevelStringHash;
	std::string l_filePath = getStartpointFilePath();

	log::info("Filepath: \"{}\"", l_filePath);
	if (!std::filesystem::exists(l_filePath)) {
		log::info("File doesnt exist: {}", l_filePath);
		return;
	}
	m_fields->m_bytesToRead = std::filesystem::file_size(l_filePath);
	m_fields->m_bytesRead = 0;

	InputStream l_ifstream = InputStream(l_filePath, &m_fields->m_bytesRead);
	if (!l_ifstream.good()) {
		log::info("!!!!!!!!!!!!!!! Failed to open file path: {} !!!!!!!!!!!!!!!!", l_filePath);
		return;
	}

	//Todo: Alert player and let them choose what to do
	l_ifstream.ignore(sizeof(s_spfMagicAndVer));
	l_ifstream >> l_savedLevelStringHash;
	if (l_savedLevelStringHash != util::algorithm::hash_string(m_level->m_levelString.c_str())) {
		log::info("!!!!!!!!!!!!! Mismatch LevelString HASH !!!!!!!!!!!!!!!");
		//return;
	}
	//EndTodo

	removeAllStartpoints(false);
	log::info("about to load startpoints from stream");
	StartpointManager::get().loadStartpointsFromStream(l_ifstream);
}

void PPPlayLayer::saveStartpoints() {
	reinterpret_cast<PPGJGameLevel*>(m_level)->describe();
	unsigned int l_levelStringHash;
	std::string l_filePath = getStartpointFilePath();
	log::info("Filepath: \"{}\"", l_filePath);

	OutputStream l_ofstream = OutputStream(l_filePath);
	if (!l_ofstream.good()) {
		log::info("Failed to open file path: {}", l_filePath);
		return;
	}
	l_ofstream.write(s_spfMagicAndVer,sizeof(s_spfMagicAndVer));
	l_levelStringHash = util::algorithm::hash_string(m_level->m_levelString.c_str());
	l_ofstream << l_levelStringHash;

	StartpointManager::get().saveStartpointsToStream(l_ofstream);
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

inline std::string PPPlayLayer::getStartpointFilePath() {
	std::string l_filePath = Mod::get()->getSaveDir().generic_string();
	
	switch(m_level->m_levelType) {
		case GJLevelType::Local:
			l_filePath.append(std::format("/local_{}{}", m_level->m_levelID.value(), SPF_EXT));
			break;
		case GJLevelType::Editor:
			l_filePath.append(std::format("/editor_{}_rev{}{}", m_level->m_levelName.c_str(), m_level->m_levelRev, SPF_EXT));
			break;
		case GJLevelType::Saved:
		default:
			l_filePath.append(std::format("/online_{}{}", m_level->m_levelID.value(), SPF_EXT));
			break;
	}
	return l_filePath;
}

void PPPlayLayer::ioThreadUpdate() {
	while (true) {
		log::info("[ioThreadUpdate] begin");
		std::unique_lock<std::mutex> l_ul(s_ioMutex);

		log::info("[ioThreadUpdate] wait condVar");
		s_ioConditionVar.wait(l_ul);
		log::info("[ioThreadUpdate] unpaused condVar");

		PPPlayLayer* l_thisPtr = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (!l_thisPtr) continue;
		
		if (l_thisPtr->m_fields->m_startedLoadingStartpoints) {
			log::info("[ioThreadUpdate] loading startpoints");
			l_thisPtr->loadStartpoints();
			log::info("[ioThreadUpdate] loaded startpoints");
			l_thisPtr->m_fields->m_finishedLoadingStartpoints = true;
		} else if (l_thisPtr->m_fields->m_startedSavingStartpoints) {
			//Todo save
			//l_thisPtr->saveStartpoints();

			//l_thisPtr->m_fields->m_finishedSavingStartpoints = true;
			//EndTodo
		}
	}
}

void PPPlayLayer::setupKeybinds() {
	addEventListener<keybinds::InvokeBindFilter>(
		[this](keybinds::InvokeBindEvent* event) {
			bool l_player1IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player1)+0x81a);
			bool l_player2IsLocked = *reinterpret_cast<byte*>(reinterpret_cast<unsigned int>(m_player2)+0x81a);
			if (event->isDown() && !l_player1IsLocked && !l_player2IsLocked && !m_player1->m_isDead && isPlusMode()) {
				std::unique_lock<std::mutex> l_ul(s_ioMutex);

				createStartpoint();
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
				std::unique_lock<std::mutex> l_ul(s_ioMutex);

				removeStartpoint();
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
				//OutputStream l_ofstream = OutputStream("./testPlayerCheckpoint.spf");
				//StartpointManager::get().saveStartpointsToStream(l_ofstream);
				saveStartpoints();
			}
			return ListenerResult::Propagate;
		},
		"test-key-2"_spr
	);
	// EndTodo
}