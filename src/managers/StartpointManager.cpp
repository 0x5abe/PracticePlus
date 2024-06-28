
#include "StartpointManager.hpp"
#include <Geode/Enums.hpp>
#include <Geode/binding/CheckpointObject.hpp>
#include <Geode/binding/GJGameState.hpp>
#include <hooks/PlayLayer.hpp>
#include <hooks/CheckpointObject.hpp>
#include <util/algorithm.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;
using namespace persistenceAPI;

PPCheckpointObject* StartpointManager::createStartpoint(PPCheckpointObject* i_startpoint) {
	//log::info("[StartpointManager::createStartpoint] begin");
	GameObject* l_newPhysicalCPO = GameObject::createWithFrame("square_01_001.png");
	CC_SAFE_RETAIN(l_newPhysicalCPO);
	l_newPhysicalCPO->m_objectID = 0x2c;
	l_newPhysicalCPO->m_objectType = GameObjectType::Decoration;
	l_newPhysicalCPO->m_glowSprite = nullptr;
	// TODO: FIX THIS OFFSET
	int* l_unkField1 = reinterpret_cast<int*>(reinterpret_cast<size_t>(l_newPhysicalCPO)+0x3d4);
	*l_unkField1 = 3;

	CC_SAFE_RELEASE(i_startpoint->m_physicalCheckpointObject);
	i_startpoint->m_physicalCheckpointObject = l_newPhysicalCPO;
	
	i_startpoint->m_physicalCheckpointObject->setStartPos(i_startpoint->m_fields->m_position);
	//log::info("sizeof CCDictionary {}", sizeof(cocos2d::CCDictionary));
	//log::info("sizeof CCDictElement {}", sizeof(cocos2d::CCDictElement));
	//log::info("sizeof CAState {}", sizeof(CAState));
	//log::info("sizeof EffectManagerState {}", sizeof(EffectManagerState));
	//log::info("sizeof GJGameState {}", sizeof(GJGameState));

	PPCheckpointObject* l_curStartpoint;
	bool l_wasAdded = false;
	for (unsigned int i = 0; i < m_startpoints->count(); i++) {
		l_curStartpoint = static_cast<PPCheckpointObject*>(m_startpoints->objectAtIndex(i));
		if (l_curStartpoint->m_fields->m_percentage > i_startpoint->m_fields->m_percentage) {
			m_startpoints->insertObject(i_startpoint, i);
			l_wasAdded = true;
			break;
		}
	}
	if (!l_wasAdded) {
		m_startpoints->addObject(i_startpoint);
	}

	return i_startpoint;
}

void StartpointManager::removeStartpoint(int i_index) {
	if (i_index == -1) {
		PPCheckpointObject* l_startpoint = static_cast<PPCheckpointObject*>(m_startpoints->lastObject());
		/* Since we are allocating the memory for the startpoints vectors we can't let the game free them (it does it differently)
		   so we do it ourselves */
		l_startpoint->clean();
		m_startpoints->removeLastObject(true);
	} else {
		m_startpoints->removeObjectAtIndex(i_index, true);
	}
}

void StartpointManager::removeAllStartpoints(bool i_reset) {
	clean();
	m_startpoints->removeAllObjects();
	if (i_reset) {
		m_isPlusMode = false;
		m_activeStartpointId = -1;
	}
}

PPCheckpointObject* StartpointManager::getStartpoint(int i_index) {
	if (m_startpoints->count() == 0) return nullptr;
	if ((-1 > i_index) || (static_cast<int>(m_startpoints->count()) <= i_index)) {
		return nullptr;
	}
	if (i_index == -1) {
		return static_cast<PPCheckpointObject*>(m_startpoints->lastObject());
	}
	return static_cast<PPCheckpointObject*>(m_startpoints->objectAtIndex(i_index));
}

PPCheckpointObject* StartpointManager::getActiveStartpoint() {
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

void StartpointManager::toggleVisibleStartpoints(bool i_visible) {
	m_visibleStartpoints = i_visible;
}

void StartpointManager::toggleVisibleStartpoints() {
	toggleVisibleStartpoints(!m_visibleStartpoints);
}

bool StartpointManager::prevStartpoint() {
	if (m_startpoints->count() == 0) return false;
	int l_nextActiveStartpointId;
	if (m_activeStartpointId == -1) {
		l_nextActiveStartpointId = m_startpoints->count() - 1;
	} else {
		l_nextActiveStartpointId = m_activeStartpointId - 1;
		if (l_nextActiveStartpointId != -1) {
			l_nextActiveStartpointId = util::algorithm::mod(l_nextActiveStartpointId, m_startpoints->count());
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
			l_nextActiveStartpointId = util::algorithm::mod(m_activeStartpointId + 1, m_startpoints->count());
		}
	}
	setActiveStartpointId(l_nextActiveStartpointId);
	return true;
}

void StartpointManager::updatePlusModeVisibility() {
	PPCheckpointObject* l_startpoint;
	if (!m_startpoints) {
		return;
	}
	for (int i = 0; i < m_startpoints->count(); i++) {
		l_startpoint = getStartpoint(i);
		if (l_startpoint) {
			l_startpoint->m_physicalCheckpointObject->setVisible(isPlusMode() && m_visibleStartpoints);
		}
	}
}

void StartpointManager::updatePlusModeLogic() {
	if (!isPlusMode()) {
		setActiveStartpointId(-1);
	}
}

void StartpointManager::loadOneStartpointFromStream() {
	//log::info("start load one");
	PPCheckpointObject* l_object = reinterpret_cast<PPCheckpointObject*>(CheckpointObject::create());
	l_object->load(m_inputStream); 

	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
	if (l_playLayer) {
		l_playLayer->addStartpoint(StartpointManager::get().createStartpoint(l_object));
	}
}

void StartpointManager::saveOneStartpointToStream(unsigned int i_index) {
	//log::info("Saving Startpoints to stream");
	static_cast<PPCheckpointObject*>(m_startpoints->objectAtIndex(i_index))->save(m_outputStream);
	//log::info("Saved Startpoints to stream");
}

void StartpointManager::clean() {
	for (int i = 0; i < m_startpoints->count(); i++) {
		PPCheckpointObject* l_startpoint = static_cast<PPCheckpointObject*>(m_startpoints->objectAtIndex(i));
		l_startpoint->clean();
	}
}

void StartpointManager::endOutputStream() {
	m_outputStream.end();
}

#if defined(PP_DEBUG)
Ref<CCArray> StartpointManager::getStartpointArray() {
	return m_startpoints;
}
#endif