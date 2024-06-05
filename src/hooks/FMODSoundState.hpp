#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/FMODSoundState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPFMODSoundState, FMODSoundState) {
protected:
	friend void operator>>(InputStream& i_stream, PPFMODSoundState& o_value);
	friend void operator<<(OutputStream& o_stream, PPFMODSoundState& i_value);

public:
	void load(InputStream& i_stream);
	void save(OutputStream& o_stream);
	
#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	void describe();
#endif
};