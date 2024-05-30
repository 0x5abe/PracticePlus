#include "CCDirector.hpp"
#include <hooks/PlayLayer.hpp>
#include <hooks/cocos2d/CCTransitionFade.hpp>

using namespace geode::prelude;

// overrides

bool PPCCDirector::replaceScene(CCScene* i_scene) {
	if (s_currentPlayLayer) {
		if (s_currentPlayLayer->m_fields->m_signalForAsyncLoad) {
			s_currentPlayLayer->m_fields->m_signalForAsyncLoad = false;
			s_currentPlayLayer->m_fields->m_transitionFadeScene = i_scene;
			CC_SAFE_RETAIN(s_currentPlayLayer->m_fields->m_transitionFadeScene);

			CCScene* l_currentScene = CCScene::get();
			if (l_currentScene) {
				l_currentScene->runAction(
					CCSequence::create(
						CCDelayTime::create(0.0f),
						CCCallFunc::create(
							s_currentPlayLayer,
							callfunc_selector(PPPlayLayer::updateAsyncProcessCreateObjectsFromSetup)
						),
						nullptr
					)
				);
			}

			return false;
		}
		if (s_currentPlayLayer->m_fields->m_cancelLevelLoad) {
			CCEGLView::get()->showCursor(true);
			CC_SAFE_RELEASE(s_currentPlayLayer->m_fields->m_transitionFadeScene);
			s_currentPlayLayer->m_fields->m_transitionFadeScene = nullptr;
			s_currentPlayLayer = nullptr;
			CCScene* l_currentScene = CCScene::get();
			LevelInfoLayer* l_levelInfoLayer = static_cast<LevelInfoLayer*>(CCScene::get()->getChildByID("LevelInfoLayer"));
			if (l_levelInfoLayer) {
				l_levelInfoLayer->m_isBusy = false;
				CCMenu* l_playMenu = static_cast<CCMenu*>(l_levelInfoLayer->getChildByID("play-menu"));
				if (!l_playMenu) {
					return false;
				}
				//Todo: Fix scale and color of play button
				l_playMenu->setTouchEnabled(true);
				CCNode* l_playButton = l_playMenu->getChildByID("play-button");
				if (!l_playButton) {
					return false;
				}
				CCNode* l_playButtonSprite = static_cast<CCNode*>(l_playButton->getChildren()->objectAtIndex(0));
				if (!l_playButtonSprite) {
					return false;
				}
				l_playButtonSprite->removeAllChildrenWithCleanup(true);
			}
			return false;
		}
	}

	return CCDirector::replaceScene(i_scene);
}