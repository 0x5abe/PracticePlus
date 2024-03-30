#include "PlayLayer.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <util/math.hpp>

using namespace geode::prelude;

bool PracticePlusPlayLayer::init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects) {
    if (!PlayLayer::init(i_level, i_useReplay, i_dontCreateObjects)) return false;

    setupKeybinds();

    return true;
}

void PracticePlusPlayLayer::resetLevel() {
    m_fields->m_isResetLevel = true;
 
    PlayLayer::resetLevel();

    m_fields->m_isResetLevel = false;
}

void PracticePlusPlayLayer::togglePracticeMode(bool i_value) {
    togglePlusMode(i_value);

    PlayLayer::togglePracticeMode(i_value);
}

void PracticePlusPlayLayer::addStartpoint(CheckpointObject* i_startpoint, int i_index) {
    CC_SAFE_RETAIN(i_startpoint);
    if (i_index != -1) {
        m_fields->m_startpoints.insert(m_fields->m_startpoints.begin() + i_index, i_startpoint);
    } else {
        m_fields->m_startpoints.push_back(i_startpoint);
    }
    addToSection(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject->activateObject();
}

bool PracticePlusPlayLayer::removeStartpoint(int i_index) {
    if (m_fields->m_startpoints.empty()) return false;
    if (i_index == -1) {
        i_index = m_fields->m_startpoints.size() - 1;
    }
    if (0 > i_index || m_fields->m_startpoints.size() <= i_index) {
        return false;
    }
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    removeObjectFromSection(l_startpoint->m_physicalCheckpointObject);
    log::info("Delete Id: {}", i_index);
    m_fields->m_startpoints.erase(m_fields->m_startpoints.begin() + i_index);
    log::info("Passed erase Id: {}", i_index);
    CC_SAFE_RELEASE(l_startpoint);
    if (i_index == m_fields->m_activeStartpointId) {
        setActiveStartpointId(i_index-1);
    }
    return true;
}

CheckpointObject* PracticePlusPlayLayer::getStartpoint(int i_index) {
    log::info("GetStartpoint Id: {}", i_index);
    if (m_fields->m_startpoints.empty()) return nullptr;
    if (0 > i_index || m_fields->m_startpoints.size() <= i_index) {
        return nullptr;
    }
    return m_fields->m_startpoints[i_index];
}

CheckpointObject* PracticePlusPlayLayer::getActiveStartpoint() {
    return getStartpoint(m_fields->m_activeStartpointId);
}

int PracticePlusPlayLayer::getActiveStartpointId() {
    return m_fields->m_activeStartpointId;
}

bool PracticePlusPlayLayer::setActiveStartpointId(int i_index) {
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    if (!l_startpoint) {
        m_fields->m_activeStartpointId = -1;
        return false;
    }
    while (m_checkpointArray->count() > 0) {
        removeCheckpoint(false);
    }
    m_fields->m_activeStartpointId = i_index;
    return true;
}

bool PracticePlusPlayLayer::reloadFromActiveStartpoint() {
    if (m_fields->m_activeStartpointId == -1 || !m_fields->m_isPlusMode) {
        return false;
    }
    resetLevel();
    return true;
}

void PracticePlusPlayLayer::updatePlusModeVisibility() {
     if (m_fields->m_isPlusMode) {
        for (CheckpointObject* l_startpoint : m_fields->m_startpoints) {
            if (l_startpoint) {
                l_startpoint->m_physicalCheckpointObject->setVisible(true);
            }
        }
    } else {
        for (CheckpointObject* l_startpoint : m_fields->m_startpoints) {
            if (l_startpoint) {
                l_startpoint->m_physicalCheckpointObject->setVisible(false);
            }
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

void PracticePlusPlayLayer::setupKeybinds() {
    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode) {
                CheckpointObject *checkpointObject = createCheckpoint();
					//CC_SAFE_RETAIN(checkpointObject);
				log::info("POS X: {}", checkpointObject->m_physicalCheckpointObject->getPositionX());
				log::info("POS Y: {}", checkpointObject->m_physicalCheckpointObject->getPositionY());

				GameObject* newphysicalCPO = GameObject::createWithFrame("square_01_001.png");
				CC_SAFE_RETAIN(checkpointObject->m_physicalCheckpointObject);
				newphysicalCPO->setID("Test");
				newphysicalCPO->setPosition(m_player1->getPosition());
				CC_SAFE_RELEASE(checkpointObject->m_physicalCheckpointObject);
				checkpointObject->m_physicalCheckpointObject = newphysicalCPO;
					
				addStartpoint(checkpointObject);
            }
            return ListenerResult::Propagate;
        },
        "place-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints.size() > 0) {
                removeStartpoint();
            }
            return ListenerResult::Propagate;
        },
        "remove-sp"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints.size() > 0) {
                int l_nextActiveStartpointId;
                if (m_fields->m_activeStartpointId == -1) {
                    l_nextActiveStartpointId = m_fields->m_startpoints.size() - 1;
                } else {
                    l_nextActiveStartpointId = m_fields->m_activeStartpointId - 1;
                    if (l_nextActiveStartpointId != -1) {
                        l_nextActiveStartpointId = util::math::mod(l_nextActiveStartpointId, m_fields->m_startpoints.size());
                    }
                }
                if(setActiveStartpointId(l_nextActiveStartpointId)) {
                    reloadFromActiveStartpoint();
                }
            }
            return ListenerResult::Propagate;
        },
        "switch-sp-prev"_spr
    );

    addEventListener<keybinds::InvokeBindFilter>(
        [this](keybinds::InvokeBindEvent* event) {
            if (event->isDown() && m_fields->m_isPlusMode && m_fields->m_startpoints.size() > 0) {
                int l_nextActiveStartpointId;
                if (m_fields->m_activeStartpointId == -1) {
                    l_nextActiveStartpointId = 0;
                } else {
                    if (m_fields->m_activeStartpointId + 1 == m_fields->m_startpoints.size()) {
                        l_nextActiveStartpointId = -1;
                    } else {
                        l_nextActiveStartpointId = util::math::mod(m_fields->m_activeStartpointId + 1, m_fields->m_startpoints.size());
                    }
                }
                if(setActiveStartpointId(l_nextActiveStartpointId)) {
                    reloadFromActiveStartpoint();
                }
            }
            return ListenerResult::Propagate;
        },
        "switch-sp-next"_spr
    );
}