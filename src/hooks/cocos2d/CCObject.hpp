#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>


class $modify(PPCCObject, cocos2d::CCObject) {
protected:
	friend void operator>>(InputStream& i_stream, PPCCObject& o_value);
	friend void operator<<(OutputStream& o_stream, PPCCObject& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);
	
#ifdef PP_DEBUG
	void describe();
#endif
};