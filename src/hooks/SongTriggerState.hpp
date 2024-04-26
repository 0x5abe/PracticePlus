#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/SongTriggerState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPSongTriggerState, SongTriggerState) {
protected:
	friend void operator>>(InputStream& i_stream, PPSongTriggerState& o_value);
	friend void operator<<(OutputStream& o_stream, PPSongTriggerState& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};