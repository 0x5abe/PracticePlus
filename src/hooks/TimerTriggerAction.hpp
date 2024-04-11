#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/TimerTriggerAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPTimerTriggerAction, TimerTriggerAction) {
protected:
    friend void operator>>(InputStream& i_stream, PPTimerTriggerAction& o_value);
    friend void operator<<(OutputStream& o_stream, PPTimerTriggerAction& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};