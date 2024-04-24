#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPGJGameLevel, GJGameLevel) {
protected:
	friend void operator>>(InputStream& i_stream, PPGJGameLevel& o_value);
	friend void operator<<(OutputStream& o_stream, PPGJGameLevel& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

	void clean();

//#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
//#endif
};