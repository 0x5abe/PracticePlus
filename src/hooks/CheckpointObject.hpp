#pragma once
#include "Geode/binding/CheckpointObject.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CheckpointObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCheckpointObject, CheckpointObject) {
protected:
	friend void operator>>(InputStream& i_stream, PPCheckpointObject& o_value);
	friend void operator<<(OutputStream& o_stream, PPCheckpointObject& i_value);

	bool m_wasLoaded = false;

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

	void clean();

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};