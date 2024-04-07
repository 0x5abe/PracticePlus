#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GJShaderState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPGJShaderState, GJShaderState) {
protected:
    friend void operator>>(InputStream& i_stream, PPGJShaderState& o_value);
    friend void operator<<(OutputStream& o_stream, PPGJShaderState& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};