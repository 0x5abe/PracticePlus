#include "PauseLayer.hpp"
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

// overrides

void PPPauseLayer::onEdit(CCObject* i_sender) {
	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
	if (l_playLayer && l_playLayer->m_fields->m_startpointSavingState != SavingState::Ready) {
		Notification::create("Cannot edit level while startpoints are being saved", NotificationIcon::Warning, 1.0f)->show();
		return;
	}

	PauseLayer::onEdit(i_sender);
}

void PPPauseLayer::tryQuit(CCObject* i_sender) {
	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
	if (l_playLayer && l_playLayer->m_fields->m_startpointSavingState != SavingState::Ready) {
		Notification::create("Cannot exit level while startpoints are being saved", NotificationIcon::Warning, 1.0f)->show();
		return;
	}

	PauseLayer::tryQuit(i_sender);
}