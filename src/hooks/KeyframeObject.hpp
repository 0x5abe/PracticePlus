#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/KeyframeObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPKeyframeObject, KeyframeObject) {
protected:
    friend void operator>>(InputStream& i_stream, PPKeyframeObject& o_value);
    friend void operator<<(OutputStream& o_stream, PPKeyframeObject& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};