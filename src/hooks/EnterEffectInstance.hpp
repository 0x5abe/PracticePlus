#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/EnterEffectInstance.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPEnterEffectInstance, EnterEffectInstance) {
protected:
	friend void operator>>(InputStream& i_stream, PPEnterEffectInstance& o_value);
	friend void operator<<(OutputStream& o_stream, PPEnterEffectInstance& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);
	
#ifdef PP_DEBUG
	void describe();
#endif
};