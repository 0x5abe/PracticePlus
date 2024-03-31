#include "PlayLayer.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <util/math.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

bool PracticePlusPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
    if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

    m_fields->m_startpoints = cocos2d::CCArray::create();
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

void PracticePlusPlayLayer::addStartpoint(CheckpointObject* i_startpoint, int i_index) {
    if (i_index != -1) {
        m_fields->m_startpoints->insertObject(i_startpoint, i_index);
    } else {
        m_fields->m_startpoints->addObject(i_startpoint);
    }
    PlayLayer::addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

void PracticePlusPlayLayer::createStartpoint() {
    CheckpointObject *checkpointObject = createCheckpoint();

	GameObject* newphysicalCPO = GameObject::createWithFrame("square_01_001.png");
	CC_SAFE_RETAIN(newphysicalCPO);
    newphysicalCPO->m_objectID = 0x2c;
    newphysicalCPO->m_objectType = GameObjectType::Decoration;
    newphysicalCPO->m_glowSprite = nullptr;
    int* l_unkField1 = (int*)((unsigned int)newphysicalCPO+0x3d4);
    *l_unkField1 = 3;
    
	CC_SAFE_RELEASE(checkpointObject->m_physicalCheckpointObject);
    checkpointObject->m_physicalCheckpointObject = newphysicalCPO;
	
	checkpointObject->m_physicalCheckpointObject->setStartPos(m_player1->getPosition());
	addStartpoint(checkpointObject);
}

bool PracticePlusPlayLayer::removeStartpoint(int i_index) {
    if (m_fields->m_startpoints->count() == 0) return false;
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    if (!l_startpoint) return false;
    PlayLayer::removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
    l_startpoint->m_physicalCheckpointObject->removeMeAndCleanup();
    if (i_index == -1) {
        m_fields->m_startpoints->removeLastObject(true);
    } else {
        m_fields->m_startpoints->removeObjectAtIndex(i_index, true);
    }
    if (i_index != -1 && i_index == m_fields->m_activeStartpointId) {
        setActiveStartpointId(i_index-1);
    }
    return true;
}

CheckpointObject* PracticePlusPlayLayer::getStartpoint(int i_index) {
    if (m_fields->m_startpoints->count() == 0) return nullptr;
    if ((-1 > i_index) || (static_cast<int>(m_fields->m_startpoints->count()) <= i_index)) {
        return nullptr;
    }
    if (i_index == -1) {
        return static_cast<CheckpointObject*>(m_fields->m_startpoints->lastObject());
    }
    return static_cast<CheckpointObject*>(m_fields->m_startpoints->objectAtIndex(i_index));
}

CheckpointObject* PracticePlusPlayLayer::getActiveStartpoint() {
    return getStartpoint(m_fields->m_activeStartpointId);
}

int PracticePlusPlayLayer::getActiveStartpointId() {
    return m_fields->m_activeStartpointId;
}

void PracticePlusPlayLayer::setActiveStartpointId(int i_index) {
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    while (m_checkpointArray->count() > 0) {
        PlayLayer::removeCheckpoint(false);
    }
    m_fields->m_activeStartpointId = i_index;
}

bool PracticePlusPlayLayer::reloadFromActiveStartpoint() {
    if (!m_fields->m_isPlusMode) {
        return false;
    }
    resetLevel();
    return true;
}

void PracticePlusPlayLayer::updatePlusModeVisibility() {
    CheckpointObject* l_startpoint;
    if (!m_fields->m_startpoints) {
        return;
    }
    for (int i = 0; i < m_fields->m_startpoints->count(); i++) {
        l_startpoint = getStartpoint(i);
        if (l_startpoint) {
            l_startpoint->m_physicalCheckpointObject->setVisible(m_fields->m_isPlusMode);
        }
    }
}

void PracticePlusPlayLayer::updatePlusModeLogic() {
    if (!m_fields->m_isPlusMode) {
        m_fields->m_activeStartpointId = -1;
    }
}

void PracticePlusPlayLayer::togglePlusMode(bool i_value) {
    m_fields->m_isPlusMode = i_value;

    updatePlusModeLogic();
    updatePlusModeVisibility();
}

void PracticePlusPlayLayer::togglePlusMode() {
    m_fields->m_isPlusMode = !m_fields->m_isPlusMode;

    updatePlusModeLogic();
    updatePlusModeVisibility();
}

void PracticePlusPlayLayer::prevStartpoint() {
    int l_nextActiveStartpointId;
    if (m_fields->m_activeStartpointId == -1) {
        l_nextActiveStartpointId = m_fields->m_startpoints->count() - 1;
    } else {
        l_nextActiveStartpointId = m_fields->m_activeStartpointId - 1;
        if (l_nextActiveStartpointId != -1) {
            l_nextActiveStartpointId = util::math::mod(l_nextActiveStartpointId, m_fields->m_startpoints->count());
        }
    }
    setActiveStartpointId(l_nextActiveStartpointId);
    reloadFromActiveStartpoint();
}

void PracticePlusPlayLayer::nextStartpoint() {
    int l_nextActiveStartpointId;
    if (m_fields->m_activeStartpointId == -1) {
        l_nextActiveStartpointId = 0;
    } else {
        if (m_fields->m_activeStartpointId + 1 == m_fields->m_startpoints->count()) {
            l_nextActiveStartpointId = -1;
        } else {
            l_nextActiveStartpointId = util::math::mod(m_fields->m_activeStartpointId + 1, m_fields->m_startpoints->count());
        }
    }
    setActiveStartpointId(l_nextActiveStartpointId);
    reloadFromActiveStartpoint();
}

void PracticePlusPlayLayer::setupKeybinds() {
    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode) {
                
            }
            return ListenerResult::Propagate;
        },
        "place-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints->count() > 0) {
                removeStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "remove-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints->count() > 0) {
                prevStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "switch-sp-prev"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints->count() > 0) {
                nextStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "switch-sp-next"_spr
    );
}