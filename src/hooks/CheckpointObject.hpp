#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CheckpointObject.hpp>
#include <sabe.persistenceapi/include/PersistenceAPI.hpp>

class $modify(PPCheckpointObject, CheckpointObject) {
protected:
	friend void operator>>(persistenceAPI::Stream& i_stream, PPCheckpointObject& o_value);
	friend void operator<<(persistenceAPI::Stream& o_stream, PPCheckpointObject& i_value);

public:
	struct Fields {
		bool m_wasLoaded = false;
		float m_percentage = 0.0f;
		cocos2d::CCPoint m_position;
	};
	
	void load(persistenceAPI::Stream& i_stream);
	void save(persistenceAPI::Stream& o_stream);

	void clean();

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};