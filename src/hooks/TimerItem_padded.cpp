#include "TimerItem_padded.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPTimerItem_padded::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPTimerItem_padded::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPTimerItem_padded& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 60);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 4);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPTimerItem_padded& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 60);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 4);
    SEPARATOR_O
}


#ifdef PP_DEBUG
void PPTimerItem_padded::describe() {
    log::info("[PPTimerItem_padded - describe] pad_1: [{}]", hexStr(pad_1, 60));
    int l_size = m_unkVecInt.size();
    log::info("[PPTimerItem_padded - describe] m_unkVecInt.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPTimerItem_padded - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
    }
    log::info("[PPTimerItem_padded - describe] pad_2: [{}]", hexStr(pad_1, 4));
}
#endif