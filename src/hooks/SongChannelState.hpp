#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/SongChannelState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPSongChannelState, SongChannelState) {
protected:
	friend void operator>>(InputStream& i_stream, PPSongChannelState& o_value);
	friend void operator<<(OutputStream& o_stream, PPSongChannelState& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};