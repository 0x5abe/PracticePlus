#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/FMODSoundState_padded.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPFMODSoundState_padded, FMODSoundState_padded) {
protected:
    friend void operator>>(InputStream& i_stream, PPFMODSoundState_padded& o_value);
    friend void operator<<(OutputStream& o_stream, PPFMODSoundState_padded& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
    
#ifdef PP_DEBUG
    void describe();
#endif
};