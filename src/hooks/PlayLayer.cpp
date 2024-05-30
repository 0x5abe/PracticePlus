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

#define SPF_EXT ".spf"

static char s_spfMagicAndVer[] = "SPF v0.0.1 lol ";

PPPlayLayer* s_currentPlayLayer = nullptr;

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

bool PPPlayLayer::readSpfLevelStringHash() {
	unsigned int l_savedLevelStringHash;
	InputStream& l_inputStream = StartpointManager::get().m_inputStream;

	l_inputStream >> l_savedLevelStringHash;
	
	if (l_savedLevelStringHash != util::algorithm::hash_string(m_level->m_levelString.c_str())) {
		log::info("[readSpfLevelStringHash] different levelstring hash");
		return false;
	}
	log::info("[readSpfLevelStringHash] same levelstring hash");
	return true;
}

bool PPPlayLayer::readSpfVersion() {
	char l_spfMagicAndVer[sizeof(s_spfMagicAndVer)];
	InputStream& l_inputStream = StartpointManager::get().m_inputStream;

	l_inputStream.read(l_spfMagicAndVer, sizeof(s_spfMagicAndVer));
	if (std::strncmp(s_spfMagicAndVer, l_spfMagicAndVer, sizeof(s_spfMagicAndVer))) {
		log::info("[readSpfVersion] different version");
		return false;
	}
	log::info("[readSpfVersion] same version");
	return true;
}

void PPPlayLayer::loadStartpoints() {
	StartpointManager& l_startpointManager = StartpointManager::get();
	InputStream& l_inputStream = StartpointManager::get().m_inputStream;
	switch (m_fields->m_startpointLoadingState) {
		case LoadingState::Setup: {
			log::info("[loadStartpoints] started loading SP");
			m_fields->m_startpointLoadingProgress = 0.0f;
			LevelInfoLayer* l_levelInfoLayer = static_cast<LevelInfoLayer*>(CCScene::get()->getChildByID("LevelInfoLayer"));
			if (l_levelInfoLayer) {
				l_levelInfoLayer->m_progressTimer->setColor(ccColor3B(220, 32, 64));
			}

			std::string l_filePath = getStartpointFilePath(true);
			if (l_filePath == "") {
				m_fields->m_startpointLoadingState = LoadingState::Ready;
				break;
			}

			m_fields->m_bytesToRead = std::filesystem::file_size(l_filePath);
			m_fields->m_bytesRead = 0;
			if(m_fields->m_bytesToRead == 0 || !l_inputStream.setFileToRead(l_filePath, &m_fields->m_bytesRead)) {
				m_fields->m_startpointLoadingState = LoadingState::HandleFileError;
				break;
			}

			m_fields->m_startpointLoadingState = LoadingState::ReadVersion;
			// falls through
		}
		case LoadingState::ReadVersion: {
			if (!readSpfVersion()) {
				m_fields->m_startpointLoadingState = LoadingState::HandleIncorrectVersion;
				break;
			}
			m_fields->m_startpointLoadingState = LoadingState::ReadHash;
			// falls through
		}
		case LoadingState::ReadHash: {
			if (!readSpfLevelStringHash()) {
				m_fields->m_startpointLoadingState = LoadingState::HandleIncorrectHash;
				break;
			}
			m_fields->m_startpointLoadingState = LoadingState::ReadStartpointCount;
			// falls through
		}
		case LoadingState::ReadStartpointCount: {
			l_inputStream >> m_fields->m_remainingStartpointLoadCount;
			m_fields->m_startpointLoadingState = LoadingState::ReadStartpoint;
			// falls through
		}
		case LoadingState::ReadStartpoint: {
			log::info("Remaining startpoints: {}", m_fields->m_remainingStartpointLoadCount);
			if (m_fields->m_remainingStartpointLoadCount > 0) {
				l_startpointManager.loadOneStartpointFromStream();
				m_fields->m_remainingStartpointLoadCount--;
			}
			if (m_fields->m_remainingStartpointLoadCount == 0) {
				m_fields->m_startpointLoadingState = LoadingState::Ready;
			}
			break;
		}
		case LoadingState::HandleFileError: {
			CCEGLView::get()->showCursor(true);
			m_fields->m_startpointLoadingState = LoadingState::WaitingForPopup;
			createQuickPopup("Error loading startpoints",
				"The startpoint file for this level could not be opened",
				"Cancel",
				"Ok",
				[&](FLAlertLayer*, bool i_btn2) {
					if (i_btn2) {
						m_fields->m_startpointLoadingState = LoadingState::Ready;
					} else {
						m_fields->m_startpointLoadingState = LoadingState::ErrorCancelLevelLoad;
					}
					CCEGLView::get()->showCursor(false);
    			}
			);
			break;
		}
		case LoadingState::HandleIncorrectVersion: {
			CCEGLView::get()->showCursor(true);
			log::info("!!!!!!!!!!!!!!!! CREATED POPUP");
			m_fields->m_startpointLoadingState = LoadingState::WaitingForPopup;
			createQuickPopup("Error loading startpoints",
				"The version of the startpoint file does not match the current one. Try to update it?",
				"Cancel",
				"Ok",
				[&](FLAlertLayer*, bool i_btn2) {
					if (i_btn2) {
						m_fields->m_startpointLoadingState = LoadingState::UpdateVersion;
					} else {
						m_fields->m_startpointLoadingState = LoadingState::Ready;
					}
					CCEGLView::get()->showCursor(false);
    			}
			);
			break;
		}
		case LoadingState::UpdateVersion: {
			if (true) {
				m_fields->m_startpointLoadingState = LoadingState::ReadHash;
			} else {
				m_fields->m_startpointLoadingState = LoadingState::Ready;
			}
			break;
		}
		case LoadingState::HandleIncorrectHash: {
			CCEGLView::get()->showCursor(true);
			m_fields->m_startpointLoadingState = LoadingState::WaitingForPopup;
			createQuickPopup("Error loading startpoints",
				"The version of the level in the startpoint file does not match the current one. Try to load it anyways? (this might be unstable or crash the game)",
				"Cancel",
				"Ok",
				[&](FLAlertLayer*, bool i_btn2) {
					if (i_btn2) {
						m_fields->m_startpointLoadingState = LoadingState::ReadStartpointCount;
					} else {
						m_fields->m_startpointLoadingState = LoadingState::Ready;
					}
					CCEGLView::get()->showCursor(false);
    			}
			);
			break;
		}
		case LoadingState::WaitingForPopup:
		case LoadingState::Ready: {
			log::info("!!!!!!!!!!!!!!!! DO NOTHING");
			break;
		}
		case LoadingState::ErrorCancelLevelLoad: {
			m_fields->m_cancelLevelLoad = true;
			m_fields->m_startpointLoadingState = LoadingState::Ready;
		}
	}
}

void PPPlayLayer::updateAsyncProcessCreateObjectsFromSetup() {
	cocos2d::SEL_CallFunc l_sel = callfunc_selector(PPPlayLayer::updateAsyncProcessCreateObjectsFromSetup);
	PPPlayLayer::processCreateObjectsFromSetup();
	if (m_loadingProgress >= 1.0) {
		log::info("Finished loading!!!!!");
		l_sel = callfunc_selector(PPPlayLayer::endAsyncProcessCreateObjectsFromSetup);
	}
	 
	CCScene* l_currentScene = CCScene::get();
	if (l_currentScene) {
		log::info("Loop load!!!!!");
		l_currentScene->runAction(
			CCSequence::create(
				CCDelayTime::create(0.0f),
				CCCallFunc::create(
					this,
					l_sel
				),
				nullptr
			)
		);
	}
}

void PPPlayLayer::endAsyncProcessCreateObjectsFromSetup() {
	if (m_fields->m_transitionFadeScene) {
		CCDirector::get()->replaceScene(m_fields->m_transitionFadeScene);
		CC_SAFE_RELEASE(m_fields->m_transitionFadeScene);
		m_fields->m_transitionFadeScene = nullptr;
	}
}

void PPPlayLayer::writeSpfHeader() {
	OutputStream& l_outputStream = StartpointManager::get().m_outputStream;
	l_outputStream.write(s_spfMagicAndVer,sizeof(s_spfMagicAndVer));
	unsigned int l_levelStringHash = util::algorithm::hash_string(m_level->m_levelString.c_str());
	l_outputStream << l_levelStringHash;
}

void PPPlayLayer::saveStartpoints() {
	StartpointManager& l_startpointManager = StartpointManager::get();
	log::info("SaveStartpoints Gets run");
	switch (m_fields->m_startpointSavingState) {
		case SavingState::Setup: {
			log::info("Goes into beginning");

			reinterpret_cast<PPGJGameLevel*>(m_level)->describe();
			m_fields->m_remainingStartpointSaveCount = l_startpointManager.getStartpointCount();
			if (m_fields->m_remainingStartpointSaveCount == 0) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}
		
			std::string l_filePath = getStartpointFilePath();
			std::string l_fileDirectory = util::filesystem::getParentDirectoryFromPath(l_filePath);
			if (!std::filesystem::exists(l_fileDirectory) && !std::filesystem::create_directories(l_fileDirectory)) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}

			OutputStream& l_outputStream = StartpointManager::get().m_outputStream;
			if (!l_outputStream.setFileToWrite(l_filePath)) {
				m_fields->m_startpointSavingState = SavingState::Ready;
				break;
			}
			
			writeSpfHeader();

			l_outputStream << m_fields->m_remainingStartpointSaveCount;

			m_fields->m_startpointSavingState = SavingState::Started;
			// falls through
		}
		case SavingState::Started: {
			if (m_fields->m_remainingStartpointSaveCount > 0) {
				l_startpointManager.saveOneStartpointToStream(l_startpointManager.getStartpointCount()-m_fields->m_remainingStartpointSaveCount);
				m_fields->m_remainingStartpointSaveCount--;
				log::info("Remaining save count: {}", m_fields->m_remainingStartpointSaveCount);
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
				break;
			}
			if (m_fields->m_remainingStartpointSaveCount == 0) {
				l_startpointManager.endOutputStream();
				m_fields->m_startpointSavingState = SavingState::Ready;
			}
		}
		case SavingState::Ready: {
			break;
		}
	}
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