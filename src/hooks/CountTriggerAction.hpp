#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CountTriggerAction.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCountTriggerAction, CountTriggerAction) {
protected:
    friend void operator>>(InputStream& i_stream, PPCountTriggerAction& o_value);
    friend void operator<<(OutputStream& o_stream, PPCountTriggerAction& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};