
#include "StartpointManager.hpp"
#include <util/math.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void StartpointManager::reset() {
    m_isPlusMode = false;
    m_activeStartpointId = -1;
    m_startpoints->removeAllObjects();
}

CheckpointObject* StartpointManager::createStartpoint(CheckpointObject* i_startpoint, CCPoint i_startPosition) {
	GameObject* l_newPhysicalCPO = GameObject::createWithFrame("square_01_001.png");
	CC_SAFE_RETAIN(l_newPhysicalCPO);
    l_newPhysicalCPO->m_objectID = 0x2c;
    l_newPhysicalCPO->m_objectType = GameObjectType::Decoration;
    l_newPhysicalCPO->m_glowSprite = nullptr;
    int* l_unkField1 = (int*)((unsigned int)l_newPhysicalCPO+0x3d4);
    *l_unkField1 = 3;
    
	CC_SAFE_RELEASE(i_startpoint->m_physicalCheckpointObject);
    i_startpoint->m_physicalCheckpointObject = l_newPhysicalCPO;
	
	i_startpoint->m_physicalCheckpointObject->setStartPos(i_startPosition);

    m_startpoints->addObject(i_startpoint);

	return i_startpoint;
}

void StartpointManager::removeStartpoint(int i_index) {
    if (i_index == -1) {
        m_startpoints->removeLastObject(true);
    } else {
        m_startpoints->removeObjectAtIndex(i_index, true);
    }
}

CheckpointObject* StartpointManager::getStartpoint(int i_index) {
    if (m_startpoints->count() == 0) return nullptr;
    if ((-1 > i_index) || (static_cast<int>(m_startpoints->count()) <= i_index)) {
        return nullptr;
    }
    if (i_index == -1) {
        return static_cast<CheckpointObject*>(m_startpoints->lastObject());
    }
    return static_cast<CheckpointObject*>(m_startpoints->objectAtIndex(i_index));
}

CheckpointObject* StartpointManager::getActiveStartpoint() {
    return getStartpoint(m_activeStartpointId);
}

void StartpointManager::setActiveStartpointId(int i_index) {
    if (i_index < -1) {
        i_index = -1;
    }
    m_activeStartpointId = i_index;
}

void StartpointManager::togglePlusMode(bool i_value) {
    m_isPlusMode = i_value;
    m_prevPlusMode = !i_value;
}

void StartpointManager::togglePlusMode() {
    togglePlusMode(!m_isPlusMode);
}

bool StartpointManager::prevStartpoint() {
    if (m_startpoints->count() == 0) return false;
    int l_nextActiveStartpointId;
    if (m_activeStartpointId == -1) {
        l_nextActiveStartpointId = m_startpoints->count() - 1;
    } else {
        l_nextActiveStartpointId = m_activeStartpointId - 1;
        if (l_nextActiveStartpointId != -1) {
            l_nextActiveStartpointId = util::math::mod(l_nextActiveStartpointId, m_startpoints->count());
        }
    }
    setActiveStartpointId(l_nextActiveStartpointId);
    return true;
}

bool StartpointManager::nextStartpoint() {
    if (m_startpoints->count() == 0) return false;
    int l_nextActiveStartpointId;
    if (m_activeStartpointId == -1) {
        l_nextActiveStartpointId = 0;
    } else {
        if (m_activeStartpointId + 1 == m_startpoints->count()) {
            l_nextActiveStartpointId = -1;
        } else {
            l_nextActiveStartpointId = util::math::mod(m_activeStartpointId + 1, m_startpoints->count());
        }
    }
    setActiveStartpointId(l_nextActiveStartpointId);
    return true;
}

void StartpointManager::updatePlusModeVisibility() {
    CheckpointObject* l_startpoint;
    if (!m_startpoints) {
        return;
    }
    for (int i = 0; i < m_startpoints->count(); i++) {
        l_startpoint = getStartpoint(i);
        if (l_startpoint) {
            l_startpoint->m_physicalCheckpointObject->setVisible(m_isPlusMode);
        }
    }
}

void StartpointManager::updatePlusModeLogic() {
    if (!m_isPlusMode) {
        setActiveStartpointId(-1);
    }
}

#ifdef DEBUG
Ref<CCArray> StartpointManager::getStartpointArray() {
    return m_startpoints;
}
#endif