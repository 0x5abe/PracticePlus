#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGameState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPGJGameState, GJGameState) {
protected:
    friend void operator>>(InputStream& i_stream, PPGJGameState& o_value);
    friend void operator<<(OutputStream& o_stream, PPGJGameState& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};