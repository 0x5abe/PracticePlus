#pragma once
#include <Geode/Geode.hpp>
#include <hooks/cocos2d/CCArray.hpp>
#include <hooks/CheckpointObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class PPPlayLayer;

class StartpointManager {
	friend class PPPlayLayer;

protected:
	geode::Ref<cocos2d::CCArray> m_startpoints = nullptr;
	int m_activeStartpointId = -1;
	bool m_isPlusMode = false;
	bool m_prevPlusMode = false;
	bool m_practiceModeIsPlusMode = true;
	bool m_visibleStartpoints = true;
	InputStream m_inputStream;
	OutputStream m_outputStream;

	StartpointManager() {
		m_startpoints = cocos2d::CCArray::create();
	}

	~StartpointManager() {
		clean();
	}

	StartpointManager(const StartpointManager&) = delete;
	StartpointManager& operator=(const StartpointManager&) = delete;
	StartpointManager(StartpointManager&&) = delete;
	StartpointManager& operator=(StartpointManager&&) = delete;

public:
	static StartpointManager& get() {
		static StartpointManager s_instance;
		return s_instance;
	}

	PPCheckpointObject* createStartpoint(PPCheckpointObject* i_checkpointObject);

	void removeStartpoint(int i_index);

	void removeAllStartpoints(bool i_reset);

	inline unsigned int getStartpointCount() { return m_startpoints->count(); }

	PPCheckpointObject* getStartpoint(int i_index = -1);

	PPCheckpointObject* getActiveStartpoint();

	inline int getActiveStartpointId() { return m_activeStartpointId; }

	void setActiveStartpointId(int i_index = -1);

	inline bool isPlusMode() { 
		if (!m_practiceModeIsPlusMode) return m_isPlusMode;
		PlayLayer* l_playLayer = PlayLayer::get();
		if (l_playLayer) {
			return l_playLayer->m_isPracticeMode;
		}
		return false;
 	}

	void togglePlusMode(bool i_value);

	void togglePlusMode();

	void toggleVisibleStartpoints(bool i_visible);

	void toggleVisibleStartpoints();

	bool prevStartpoint();

	bool nextStartpoint();

	void updatePlusModeVisibility();

	void updatePlusModeLogic();

	void setupKeybinds();

	void loadOneStartpointFromStream();

	void saveOneStartpointToStream(unsigned int index);

	void clean();

	void endOutputStream();

#if defined(PP_DEBUG)
	geode::Ref<cocos2d::CCArray> getStartpointArray();
#endif
};