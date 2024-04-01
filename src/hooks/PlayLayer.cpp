#include "PlayLayer.hpp"
#include <managers/StartpointManager.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;

// overrides

bool PracticePlusPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
    if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;
    
    setupKeybinds();

    return true;
}

void PracticePlusPlayLayer::resetLevel() {
    m_fields->m_enableArrayHook = true;
 
    PlayLayer::resetLevel();

    m_fields->m_enableArrayHook = false;
}

void PracticePlusPlayLayer::togglePracticeMode(bool i_value) {
    togglePlusMode(i_value);

    PlayLayer::togglePracticeMode(i_value);
}

void PracticePlusPlayLayer::updateVisibility(float i_unkFloat) {
    PlayLayer::updateVisibility(i_unkFloat);

    if (!isPlusMode()) {
        StartpointManager::get().updatePlusModeVisibility();
    }
}

void PracticePlusPlayLayer::onQuit() {
    PlayLayer::onQuit();

    StartpointManager::get().reset();
}

// custom methods

void PracticePlusPlayLayer::createStartpoint() {
    addStartpoint(StartpointManager::get().createStartpoint(createCheckpoint(), m_player1->getPosition()));
}

void PracticePlusPlayLayer::addStartpoint(CheckpointObject* i_startpoint, int i_index) {
    PlayLayer::addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

bool PracticePlusPlayLayer::removeStartpoint(int i_index) {
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

bool PracticePlusPlayLayer::setActiveStartpointAndReload(int i_index) {
    StartpointManager::get().setActiveStartpointId(i_index);
    reloadFromActiveStartpoint();
    return true;
}

void PracticePlusPlayLayer::reloadFromActiveStartpoint() {
    while (m_checkpointArray->count() > 0) {
        PlayLayer::removeCheckpoint(false);
    }
    resetLevel();
}

void PracticePlusPlayLayer::togglePlusMode(bool i_value) {
    StartpointManager& l_startpointManager = StartpointManager::get();

    l_startpointManager.togglePlusMode(i_value);
    l_startpointManager.updatePlusModeLogic();
    l_startpointManager.updatePlusModeVisibility();
}

void PracticePlusPlayLayer::setupKeybinds() {
    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && isPlusMode()) {
                createStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "place-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && isPlusMode()) {
                removeStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "remove-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && isPlusMode()) {
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
            if (event->isDown() && isPlusMode()) {
                if (StartpointManager::get().nextStartpoint()) {
                    reloadFromActiveStartpoint();
                }
            }
            return ListenerResult::Propagate;
        },
        "switch-sp-next"_spr
    );
}