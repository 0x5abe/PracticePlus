#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/EventTriggerInstance.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPEventTriggerInstance, EventTriggerInstance) {
protected:
    friend void operator>>(InputStream& i_stream, PPEventTriggerInstance& o_value);
    friend void operator<<(OutputStream& o_stream, PPEventTriggerInstance& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};