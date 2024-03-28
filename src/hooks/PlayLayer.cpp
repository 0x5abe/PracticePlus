#include "PlayLayer.hpp"

using namespace geode::prelude;

void PracticePlusPlayLayer::resetLevel() {
    bool l_lastIsTestMode = m_isTestMode;
    m_fields->m_isResetLevel = true;
    if (m_fields->m_isPlusMode) {
        m_isTestMode = true;
    }

    PlayLayer::resetLevel();

    m_isTestMode = l_lastIsTestMode;
    m_fields->m_isResetLevel = false;
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
    m_fields->m_startpoints.push_back(i_startpoint);
    setActiveStartpointId(m_fields->m_startpoints.size() - 1);
}

bool PracticePlusPlayLayer::removeStartPoint(int i_index) {
    if (m_fields->m_startpoints.empty()) return false;
    if (i_index == -1) {
        i_index = m_fields->m_startpoints.size()-1;
    }
    if (m_fields->m_startpoints.size() <= i_index) {
        return false;
    }
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    CC_SAFE_RELEASE(l_startpoint);
    
    m_fields->m_startpoints.erase(m_fields->m_startpoints.begin() + i_index);
    
    if (i_index == m_fields->m_activeStartpointId) {
        m_activeStartpointId--;
    }
    return true;
}

CheckpointObject* PracticePlusPlayLayer::getStartpoint(int i_index) {
    if (m_fields->m_startpoints.empty()) return nullptr;
    if (i_index == -1) {
        i_index = m_fields->m_startpoints.size()-1;
    }
    if (m_fields->m_startpoints.size() <= i_index) {
        return nullptr;
    }
    return m_fields->m_startpoints[i_index];
}

CheckpointObject* PracticePlusPlayLayer::getActiveStartpoint() {
    if (m_fields->m_startpoints.empty()) return nullptr;
    return m_fields->m_startpoints[m_fields->m_activeStartpointId];
}

int PracticePlusPlayLayer::getActiveStartpointId() {
    return m_fields->m_activeStartpointId;
}

bool PracticePlusPlayLayer::setActiveStartpointId(int i_index) {
    CheckpointObject* l_startpoint = getStartpoint(i_index);
    if (!l_startpoint) return false;
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

void PracticePlusPlayLayer::togglePlusMode() {
    m_fields->m_isPlusMode = !m_fields->m_isPlusMode;

    if (m_fields->m_isPlusMode) {
        m_isTestMode = true;
        for (CheckpointObject* l_startpoint : m_fields->m_startpoints) {
            l_startpoint->m_physicalCheckpointObject->activateObject();
        }
    } else {
        m_isTestMode = false;
        for (CheckpointObject* l_startpoint : m_fields->m_startpoints) {
            l_startpoint->m_physicalCheckpointObject->deactivateObject(true);
        }
    }
}