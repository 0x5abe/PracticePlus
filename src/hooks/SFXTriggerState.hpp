#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/SFXTriggerState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPSFXTriggerState, SFXTriggerState) {
protected:
	friend void operator>>(InputStream& i_stream, PPSFXTriggerState& o_value);
	friend void operator<<(OutputStream& o_stream, PPSFXTriggerState& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};