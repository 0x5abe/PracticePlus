#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/TimerItem_padded.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPTimerItem_padded, TimerItem_padded) {
protected:
    friend void operator>>(InputStream& i_stream, PPTimerItem_padded& o_value);
    friend void operator<<(OutputStream& o_stream, PPTimerItem_padded& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};