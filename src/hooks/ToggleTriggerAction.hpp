#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/ToggleTriggerAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPToggleTriggerAction, ToggleTriggerAction) {
protected:
	friend void operator>>(InputStream& i_stream, PPToggleTriggerAction& o_value);
	friend void operator<<(OutputStream& o_stream, PPToggleTriggerAction& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#ifdef PP_DEBUG
	void describe();
#endif
};