#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerCheckpoint.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPPlayerCheckpoint, PlayerCheckpoint) {
protected:
	friend void operator>>(InputStream& i_stream, PPPlayerCheckpoint& o_value);
	friend void operator<<(OutputStream& o_stream, PPPlayerCheckpoint& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#ifdef PP_DEBUG
	void describe();
#endif
};