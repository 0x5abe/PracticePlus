#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <hooks/CheckpointObject.hpp>
#include <managers/StartpointManager.hpp>

#define SPF_EXT ".spf"
extern PPPlayLayer* s_currentPlayLayer;
extern char s_spfMagicAndVer[11];

enum class LoadingState {
	Ready,
	Setup,
	HandleFileError,
	ReadVersion,
	HandleIncorrectVersion,
	UpdateVersion,
	ReadFinishedSaving,
	HandleDidNotFinishSaving,
	ReadHash,
	HandleIncorrectHash,
	ReadStartpointCount,
	ReadStartpoint,
	WaitingForPopup,
	ErrorCancelLevelLoad
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
		bool m_signalForAsyncLoad = false;
		cocos2d::CCScene* m_transitionFadeScene = nullptr;
		bool m_cancelLevelLoad = false;
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
	
	inline PPCheckpointObject* getActiveStartpoint() { return StartpointManager::get().getActiveStartpoint(); }

	inline int getActiveStartpointId() { return StartpointManager::get().getActiveStartpointId(); }

	bool setActiveStartpointAndReload(int i_index);

	void reloadFromActiveStartpoint();

	inline bool isPlusMode() { return StartpointManager::get().isPlusMode(); }

	void togglePlusMode(bool i_value);

	bool readSpfLevelStringHash();

	bool readSpfVersion();

	bool readSpfFinishedSaving();

	void loadStartpoints();

	void updateAsyncProcessCreateObjectsFromSetup();

	void endAsyncProcessCreateObjectsFromSetup();

	void writeSpfHeader();

	void saveStartpoints();
	
	inline int getGameObjectIndex(GameObject* i_object) {
		return i_object->m_uniqueID-m_fields->m_uniqueIdBase;
	}

	void setupKeybinds();
};