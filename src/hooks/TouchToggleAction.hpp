#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/TouchToggleAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPTouchToggleAction, TouchToggleAction) {
protected:
    friend void operator>>(InputStream& i_stream, PPTouchToggleAction& o_value);
    friend void operator<<(OutputStream& o_stream, PPTouchToggleAction& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};