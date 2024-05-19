#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <hooks/CheckpointObject.hpp>
#include <managers/StartpointManager.hpp>

enum class LoadingState {
	Ready,
	Setup,
	HandleFileError,
	ReadVersion,
	HandleIncorrectVersion,
	UpdateVersion,
	ReadHash,
	HandleIncorrectHash,
	ReadStartpointCount,
	ReadStartpoint,
	WaitingForPopup,
	ErrorEndLevelLoad
};

enum class SavingState {
	Ready,
	Setup,
	Started
};

class $modify(PPPlayLayer, PlayLayer) {
protected:
	void updatePlusModeVisibility(bool i_isPlusMode);

	void updatePlusModeLogic(bool i_isPlusMode);

	std::string getStartpointFilePath(bool i_checkExists = false);

public:
	struct Fields {
		int m_uniqueIdBase = 12;
		bool m_onQuitCalled = false;
		LoadingState m_startpointLoadingState = LoadingState::Setup;
		float m_startpointLoadingProgress = 0.0f;
		unsigned int m_remainingStartpointLoadCount = 0;
		SavingState m_startpointSavingState = SavingState::Ready;
		unsigned int m_remainingStartpointSaveCount = 0;
		unsigned int m_bytesToRead = 0;
		unsigned int m_bytesRead = 0;
		bool m_readyToLoad = false;
		bool m_updateStartpointFileVersion = false;
		bool m_popupOpen = false;
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

	bool readSpfLevelStringHash();

	bool readSpfVersion();

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