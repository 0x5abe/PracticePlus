#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/EffectManagerState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPEffectManagerState, EffectManagerState) {
protected:
    friend void operator>>(InputStream& i_stream, PPEffectManagerState& o_value);
    friend void operator<<(OutputStream& o_stream, PPEffectManagerState& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};