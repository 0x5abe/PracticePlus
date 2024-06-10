#include "EndLevelLayer.hpp"
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;
using namespace persistencyUtils;

// overrides

void PPEndLevelLayer::onMenu(CCObject* i_sender) {
	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
	if (l_playLayer && l_playLayer->m_fields->m_startpointSavingState != SavingState::Ready) {
		Notification::create("Cannot exit level while startpoints are being saved", NotificationIcon::Warning, 1.0f)->show();
		return;
	}

	PPEndLevelLayer::onMenu(i_sender);
}