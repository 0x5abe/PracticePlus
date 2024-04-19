#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CAState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCAState, CAState) {
protected:
	friend void operator>>(InputStream& i_stream, PPCAState& o_value);
	friend void operator<<(OutputStream& o_stream, PPCAState& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};