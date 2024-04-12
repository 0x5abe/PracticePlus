#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/SpawnTriggerAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPSpawnTriggerAction, SpawnTriggerAction) {
protected:
	friend void operator>>(InputStream& i_stream, PPSpawnTriggerAction& o_value);
	friend void operator<<(OutputStream& o_stream, PPSpawnTriggerAction& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);

#ifdef PP_DEBUG
	void describe();
#endif
};