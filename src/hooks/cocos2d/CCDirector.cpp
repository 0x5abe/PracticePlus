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

			return false;
		}
	}

	return CCDirector::replaceScene(i_scene);
}