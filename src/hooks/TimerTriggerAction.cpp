#include "TimerTriggerAction.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPTimerTriggerAction::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPTimerTriggerAction::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPTimerTriggerAction& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 32);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPTimerTriggerAction& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 32);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
}


#ifdef PP_DEBUG
void PPTimerTriggerAction::describe() {
    log::info("[PPTimerTriggerAction - describe] pad_1: [{}]", hexStr(pad_1, 32));
    int l_size = m_unkVecInt.size();
    log::info("[PPTimerTriggerAction - describe] m_unkVecInt.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPTimerTriggerAction - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
    }
}
#endif