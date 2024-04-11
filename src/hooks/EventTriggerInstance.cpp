#include "EventTriggerInstance.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPEventTriggerInstance::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPEventTriggerInstance::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPEventTriggerInstance& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 16);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPEventTriggerInstance& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 16);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
}

#ifdef PP_DEBUG
void PPEventTriggerInstance::describe() {
    log::info("[PPEventTriggerInstance - describe] pad_1: [{}]", hexStr(pad_1, 16));
    int l_size = m_unkVecInt.size();
    log::info("[PPEventTriggerInstance - describe] m_unkVecInt.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPEventTriggerInstance - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
    }
}
#endif