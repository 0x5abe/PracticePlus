#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/FMODQueuedMusic.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPFMODQueuedMusic, FMODQueuedMusic) {
protected:
    friend void operator>>(InputStream& i_stream, PPFMODQueuedMusic& o_value);
    friend void operator<<(OutputStream& o_stream, PPFMODQueuedMusic& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
    
#ifdef PP_DEBUG
    void describe();
#endif
};