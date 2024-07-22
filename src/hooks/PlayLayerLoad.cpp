#include "PlayLayer.hpp"
#include <filesystem>
#include <managers/StartpointManager.hpp>
#include <util/algorithm.hpp>
#include <util/filesystem.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

bool PPPlayLayer::readSpfLevelStringHash() {
	unsigned int l_savedLevelStringHash;
	Stream& l_stream = StartpointManager::get().m_stream;

	l_stream >> l_savedLevelStringHash;
	
	if (l_savedLevelStringHash != util::algorithm::hash_string(m_level->m_levelString.c_str())) {
		log::info("[readSpfLevelStringHash] different levelstring hash");
		return false;
	}
	log::info("[readSpfLevelStringHash] same levelstring hash");
	return true;
}

bool PPPlayLayer::readSpfVersion() {
	char l_spfMagicAndVer[sizeof(s_spfMagicAndVer)];
	Stream& l_stream = StartpointManager::get().m_stream;

	l_stream.read(l_spfMagicAndVer, sizeof(s_spfMagicAndVer));
	if (std::strncmp(s_spfMagicAndVer, l_spfMagicAndVer, sizeof(s_spfMagicAndVer))) {
		log::info("[readSpfVersion] different version");
		return false;
	}
	log::info("[readSpfVersion] same version");
	return true;
}

bool PPPlayLayer::readSpfFinishedSaving() {
	bool l_params[16-sizeof(s_spfMagicAndVer)];
	Stream& l_stream = StartpointManager::get().m_stream;

	l_stream.read(reinterpret_cast<char*>(l_params), 16-sizeof(s_spfMagicAndVer));
	if (l_params[0] == false) {
		log::info("[readSpfFinishedSaving] did not finish writing");
		return false;
	}
	log::info("[readSpfVersion] finished writing");
	return true;
}

void PPPlayLayer::loadStartpoints() {
	StartpointManager& l_startpointManager = StartpointManager::get();
	Stream& l_stream = StartpointManager::get().m_stream;
	switch (m_fields->m_startpointLoadingState) {
		case LoadingState::Setup: {
			//log::info("[loadStartpoints] started loading SP");
			m_fields->m_startpointLoadingProgress = 0.0f;

			std::string l_filePath = getStartpointFilePath(true);
			if (l_filePath == "") {
				m_fields->m_startpointLoadingState = LoadingState::Ready;
				m_fields->m_startpointLoadingProgress = 0.99f;
				break;
			}

			LevelInfoLayer* l_levelInfoLayer = static_cast<LevelInfoLayer*>(CCScene::get()->getChildByID("LevelInfoLayer"));
			if (l_levelInfoLayer) {
				l_levelInfoLayer->m_progressTimer->setColor(ccColor3B(220, 32, 64));
			}

			m_fields->m_bytesToRead = std::filesystem::file_size(l_filePath);
			m_fields->m_bytesRead = 0;
			if(m_fields->m_bytesToRead == 0 || !l_stream.setFile(l_filePath, &m_fields->m_bytesRead)) {
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
			m_fields->m_startpointLoadingState = LoadingState::ReadFinishedSaving;
			// falls through
		}
		case LoadingState::ReadFinishedSaving: {
			if (!readSpfFinishedSaving()) {
				m_fields->m_startpointLoadingState = LoadingState::HandleDidNotFinishSaving;
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
			l_stream >> m_fields->m_remainingStartpointLoadCount;
			m_fields->m_startpointLoadingState = LoadingState::ReadStartpoint;
			// falls through
		}
		case LoadingState::ReadStartpoint: {
			//log::info("Remaining startpoints: {}", m_fields->m_remainingStartpointLoadCount);
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
			//log::info("!!!!!!!!!!!!!!!! CREATED POPUP");
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
				m_fields->m_startpointLoadingState = LoadingState::ReadFinishedSaving;
			} else {
				m_fields->m_startpointLoadingState = LoadingState::Ready;
			}
			break;
		}
		case LoadingState::HandleDidNotFinishSaving: {
			CCEGLView::get()->showCursor(true);
			m_fields->m_startpointLoadingState = LoadingState::WaitingForPopup;
			createQuickPopup("Error loading startpoints",
				"The startpoint file for this level appears to be corrupted",
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
			//log::info("!!!!!!!!!!!!!!!! DO NOTHING");
			break;
		}
		case LoadingState::ErrorCancelLevelLoad: {
			m_fields->m_cancelLevelLoad = true;
			LevelInfoLayer* l_levelInfoLayer = static_cast<LevelInfoLayer*>(CCScene::get()->getChildByID("LevelInfoLayer"));
			if (l_levelInfoLayer) {
				l_levelInfoLayer->m_progressTimer->setVisible(false);
			}
			l_startpointManager.endStream();
			m_fields->m_startpointLoadingState = LoadingState::Ready;
		}
	}
}

void PPPlayLayer::updateAsyncProcessCreateObjectsFromSetup() {
	cocos2d::SEL_CallFunc l_sel = callfunc_selector(PPPlayLayer::updateAsyncProcessCreateObjectsFromSetup);
	PPPlayLayer::processCreateObjectsFromSetup();
	if (m_loadingProgress >= 1.0) {
		//log::info("Finished loading!!!!!");
		l_sel = callfunc_selector(PPPlayLayer::endAsyncProcessCreateObjectsFromSetup);
	}
	 
	CCScene* l_currentScene = CCScene::get();
	if (l_currentScene) {
		//log::info("Loop load!!!!!");
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