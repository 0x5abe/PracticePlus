#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <hooks/CheckpointObject.hpp>
#include <managers/StartpointManager.hpp>

class $modify(PPPlayLayer, PlayLayer) {
protected:
	void updatePlusModeVisibility(bool i_isPlusMode);

	void updatePlusModeLogic(bool i_isPlusMode);

	std::string getStartpointFilePath(bool i_checkExists = false);

public:
	struct Fields {
		int m_uniqueIdBase = 12;
		bool m_onQuitCalled = false;
		bool m_startedLoadingStartpoints = false;
		bool m_finishedLoadingStartpoints = false;
		float m_startpointLoadingProgress = 0.0f;
		unsigned int m_remainingStartpointLoadCount = 0;
		bool m_startedSavingStartpoints = false;
		bool m_finishedSavingStartpoints = false;
		unsigned int m_bytesToRead = 0;
		unsigned int m_bytesRead = 0;
	};

	// overrides

	$override
	bool init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects);

	$override 
	void createObjectsFromSetupFinished();

	$override
	void setupHasCompleted();

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

	void removeAllStartpoints(bool i_reset);

	bool checkLevelStringHash();

	bool readSpfHeader();

	void loadStartpoints();

	void writeSpfHeader();

	void saveStartpoints();

	inline PPCheckpointObject* getActiveStartpoint() { return StartpointManager::get().getActiveStartpoint(); }

	inline int getActiveStartpointId() { return StartpointManager::get().getActiveStartpointId(); }

	bool setActiveStartpointAndReload(int i_index);

	void reloadFromActiveStartpoint();

	inline bool isPlusMode() { return StartpointManager::get().isPlusMode(); }

	void togglePlusMode(bool i_value);
	
	inline int getGameObjectIndex(GameObject* i_object) {
		return i_object->m_uniqueID-m_fields->m_uniqueIdBase;
	}

	static void ioThreadUpdate();

	void setupKeybinds();
};