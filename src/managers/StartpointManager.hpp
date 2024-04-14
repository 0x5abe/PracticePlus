#pragma once
#include "Geode/binding/PlayLayer.hpp"
#include <Geode/Geode.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>
#include <hooks/cocos2d/CCArray.hpp>

class StartpointManager {
	friend class PPCCArray;
protected:
	geode::Ref<cocos2d::CCArray> m_startpoints = nullptr;
	int m_activeStartpointId = -1;
	bool m_isPlusMode = false;
	bool m_prevPlusMode = false;
	bool m_practiceModeIsPlusMode = true;

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
		static StartpointManager l_instance;
		return l_instance;
	}

	void reset();

	CheckpointObject* createStartpoint(CheckpointObject* i_checkpointObject, cocos2d::CCPoint i_startPosition);

	void removeStartpoint(int i_index);

	CheckpointObject* getStartpoint(int i_index = -1);

	CheckpointObject* getActiveStartpoint();

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

	bool prevStartpoint();

	bool nextStartpoint();

	void updatePlusModeVisibility();

	void updatePlusModeLogic();

	void setupKeybinds();

	void loadStartpointsFromStream(InputStream& i_stream);

	void saveStartpointsToStream(OutputStream& o_stream);

	void clean();

#ifdef PP_DEBUG
	geode::Ref<cocos2d::CCArray> getStartpointArray();
#endif
};