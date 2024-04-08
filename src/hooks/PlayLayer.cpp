#include "PlayLayer.hpp"
#include <managers/StartpointManager.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace geode::prelude;

// overrides

bool PPPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
    // reset GameObject uniqueID global
    *reinterpret_cast<unsigned int*>(geode::base::get()+0x4ea028) = 10;

    if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;
    
    setupKeybinds();

    return true;
}

void PPPlayLayer::resetLevel() {
    m_fields->m_enableArrayHook = true;
 
    PlayLayer::resetLevel();
    m_fields->m_enableArrayHook = false;
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

    //Todo: Remvoe
    if (m_fields->m_autoCreateSp1 && m_fields->m_autoCreateSp2) {
        createStartpoint();
        removeStartpoint();
    }
    //EndTodo
}

void PPPlayLayer::onQuit() {
    PlayLayer::onQuit();

    StartpointManager::get().reset();
}

// custom methods

void PPPlayLayer::createStartpoint() {
    addStartpoint(StartpointManager::get().createStartpoint(createCheckpoint(), m_player1->getPosition()));
}

void PPPlayLayer::addStartpoint(CheckpointObject* i_startpoint, int i_index) {
    PlayLayer::addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

bool PPPlayLayer::removeStartpoint(int i_index) {
    StartpointManager& l_startpointManager = StartpointManager::get();
    CheckpointObject* l_startpoint = l_startpointManager.getStartpoint(i_index);
    if (!l_startpoint) return false;
    //Todo: remove
    if (l_startpoint->m_audioState.m_unkMapIntFMODQueuedMusic1.size() > 0 || l_startpoint->m_audioState.m_unkMapIntFMODQueuedMusic2.size()) {
        m_fields->m_autoCreateSp1 = false;
        m_fields->m_autoCreateSp2 = false;
        log::info("!!!!!!!!!!!!!!!!!!!!!!!!HAS MEMBERS IN unkMapIntFMODQueuedMusic!!!!!!!!!!!!!!!!!!!!!!!");
    }
    // if (l_startpoint->m_sequenceTriggerStateUnorderedMap.size() > 0) {
    //     for (std::pair<int,SequenceTriggerState> l_pair : l_startpoint->m_sequenceTriggerStateUnorderedMap) {
    //         if (l_pair.second.m_unkUnorderedMap1.size() > 0 || l_pair.second.m_unkUnorderedMap2.size() > 0) {
    //             m_fields->m_autoCreateSp1 = false;
    //             m_fields->m_autoCreateSp2 = false;
    //             log::info("###############HAS MEMBERS IN SEQTRIGGSTATE###########################");
    //         }
    //     }
    // }
    //EndTodo
    gd::string a;
    a.size();
    PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
    l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
    if (l_startpoint == l_startpointManager.getActiveStartpoint()) {
        StartpointManager::get().setActiveStartpointId(l_startpointManager.getActiveStartpointId()-1);
    }
    l_startpointManager.removeStartpoint(i_index);
    return true;
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
    //TODO REMOVE
    gd::unordered_map<int,double> a = gd::unordered_map<int,double>();
    a.insert({1,0.8});
    for (std::pair<int,double> pair : a) {
        log::info("sizeof std::pair<int,double> {}", sizeof(std::pair<int,double>));
        log::info("val {}", pair.second);
    }
    if (true && !m_fields->m_loggedObjects) {
        m_fields->m_loggedObjects = true;
        for (int i = 0; i < m_objects->count(); i++) {
            GameObject* l_object = reinterpret_cast<GameObject*>(m_objects->objectAtIndex(i));
            log::info("Object at index: {}, m_objectID: {}, m_uniqueID: {}", i, l_object->m_objectID, l_object->m_uniqueID);
        }
    }
    //EndTodo
    l_startpointManager.togglePlusMode(i_value);
    l_startpointManager.updatePlusModeLogic();
    l_startpointManager.updatePlusModeVisibility();
}

void PPPlayLayer::setupKeybinds() {
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