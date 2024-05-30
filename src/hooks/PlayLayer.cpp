#include "PlayLayer.hpp"
#include <filesystem>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <managers/StartpointManager.hpp>
#include <hooks/GJGameLevel.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>
#include <util/algorithm.hpp>
#include <util/filesystem.hpp>

using namespace geode::prelude;

PPPlayLayer* s_currentPlayLayer = nullptr;
char s_spfMagicAndVer[] = "SPF v0.0.2";

// overrides

bool PPPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
	// reset uniqueID global to save/load GameObjects correctly using their index
	// should look into not having to do this but it's harder than it looks since there's 
	// probably maps with object id as keys, it's not just us saving pointers so I'd have to find those.
	*reinterpret_cast<int*>(geode::base::get()+0x4ea028) = 10;
	m_fields->m_uniqueIdBase = *reinterpret_cast<int*>(geode::base::get()+0x4ea028) + 2;

	// for processing objects asynchronously every time
	s_currentPlayLayer = this;
	m_fields->m_signalForAsyncLoad = !i_dontCreateObjects;
	if (m_fields->m_signalForAsyncLoad) {
		m_loadingProgress = 1.0f;
	}

	if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

	// for processing objects asynchronously every time
	if (m_fields->m_signalForAsyncLoad) {
		m_loadingProgress = 0.0f;
	}

	setupKeybinds();
	return true;
}

void PPPlayLayer::createObjectsFromSetupFinished() {
	if (m_fields->m_startpointLoadingState == LoadingState::Setup) {
		PlayLayer::createObjectsFromSetupFinished();
	}
}

void PPPlayLayer::setupHasCompleted() {
	//log::info("[setupHasCompleted] begin");
	if (m_fields->m_startpointLoadingState != LoadingState::Ready) {
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
	if (m_fields->m_startpointLoadingState == LoadingState::Ready && !m_fields->m_cancelLevelLoad) {
		log::info("[setupHasCompleted] finished loading SP");
		m_loadingProgress = 1.0f;
		PlayLayer::setupHasCompleted();

		//StartpointManager::get().fetchStartpointsFromTempStorage();
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
	s_currentPlayLayer = nullptr;
}

// custom methods

void PPPlayLayer::createStartpoint() {
	PPCheckpointObject* l_startpoint =  static_cast<PPCheckpointObject*>(PlayLayer::createCheckpoint());
	l_startpoint->m_fields->m_percentage = PlayLayer::getCurrentPercent();
	addStartpoint(StartpointManager::get().createStartpoint(l_startpoint, m_player1->getPosition()));

	//Todo: see if we want to save to file here, make it so it only saves the changes instead of the whole thing
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
	return true;
}

void PPPlayLayer::removeAllStartpoints(bool i_reset) {
	StartpointManager& l_startpointManager = StartpointManager::get();
	CheckpointObject* l_startpoint;
	for (int i = 0; i < l_startpointManager.getStartpointCount(); i++) {
		l_startpoint = l_startpointManager.getStartpoint(i);
		if (!l_startpoint) continue;
		//Todo: see wth happens here (has crashed before)
		// May be related to objects appearing invisible
		PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
		l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
		//EndTodo
	}
	l_startpointManager.removeAllStartpoints(i_reset);
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

std::string PPPlayLayer::getStartpointFilePath(bool i_checkExists) {
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
				if (m_fields->m_startpointSavingState == SavingState::Ready) {
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
				if (m_fields->m_startpointSavingState == SavingState::Ready) {
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
				m_fields->m_startpointSavingState = SavingState::Setup;
				CCScene* l_currentScene = CCScene::get();
				if (l_currentScene) {
					l_currentScene->runAction(
						CCSequence::create(
							CCDelayTime::create(0.0f),
							CCCallFunc::create(
								this,
								callfunc_selector(PPPlayLayer::saveStartpoints)
							),
							nullptr
						)
					);
				}
				//saveStartpoints();
			}
			return ListenerResult::Propagate;
		},
		"test-key-2"_spr
	);
	// EndTodo
}