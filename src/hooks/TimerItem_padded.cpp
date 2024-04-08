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
    i_stream.read(reinterpret_cast<char*>(o_value.__pad15), 60);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.__pad17), 4);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPTimerItem_padded& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.__pad15), 60);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.__pad17), 4);
    SEPARATOR_O
}