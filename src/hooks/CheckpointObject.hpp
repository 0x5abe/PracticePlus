#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CheckpointObject.hpp>
#include <sabe.persistencyutils/include/PersistencyUtils.hpp>

class $modify(PPCheckpointObject, CheckpointObject) {
protected:
	friend void operator>>(persistencyUtils::InputStream& i_stream, PPCheckpointObject& o_value);
	friend void operator<<(persistencyUtils::OutputStream& o_stream, PPCheckpointObject& i_value);

public:
	struct Fields {
		bool m_wasLoaded = false;
		float m_percentage = 0.0f;
		cocos2d::CCPoint m_position;
	};
	
	void load(persistencyUtils::InputStream& i_stream);
	void save(persistencyUtils::OutputStream& o_stream);

	void clean();

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};