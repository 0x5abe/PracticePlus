#pragma once
#include "Geode/binding/GameObject.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <hooks/CheckpointObject.hpp>
#include <managers/StartpointManager.hpp>

class $modify(PPPlayLayer, PlayLayer) {
protected:
	void updatePlusModeVisibility(bool i_isPlusMode);

	void updatePlusModeLogic(bool i_isPlusMode);

public:
	int m_uniqueIdBase = 12;
	bool m_onQuitCalled = false;

	// overrides

	$override
	bool init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects);

	$override
	void resetLevel();

	$override
	void togglePracticeMode(bool i_value);

	$override
	void updateVisibility(float i_unkFloat);

	$override
	void onQuit();
	
	// custom methods

	void addStartpoint(PPCheckpointObject* i_startpoint, int i_index = -1);

	void createStartpoint();

	bool removeStartpoint(int i_index = -1);

	inline PPCheckpointObject* getActiveStartpoint() { return StartpointManager::get().getActiveStartpoint(); }

	inline int getActiveStartpointId() { return StartpointManager::get().getActiveStartpointId(); }

	bool setActiveStartpointAndReload(int i_index);

	void reloadFromActiveStartpoint();

	inline bool isPlusMode() { return StartpointManager::get().isPlusMode(); }

	void togglePlusMode(bool i_value);
	
	inline int getGameObjectIndex(GameObject* i_object) {
		return i_object->m_uniqueID-m_fields->m_uniqueIdBase;
	}

	void setupKeybinds();
};