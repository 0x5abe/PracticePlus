#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/DynamicSaveObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>


class $modify(PPDynamicSaveObject, DynamicSaveObject) {
public:
	friend void operator>>(InputStream& i_stream, PPDynamicSaveObject& o_value);
	friend void operator<<(OutputStream& o_stream, PPDynamicSaveObject& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#ifdef PP_DEBUG
	void describe();
#endif
};