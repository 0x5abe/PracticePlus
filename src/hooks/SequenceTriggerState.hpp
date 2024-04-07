#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/SequenceTriggerState.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPSequenceTriggerState, SequenceTriggerState) {
protected:
    friend void operator>>(InputStream& i_stream, PPSequenceTriggerState& o_value);
    friend void operator<<(OutputStream& o_stream, PPSequenceTriggerState& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};