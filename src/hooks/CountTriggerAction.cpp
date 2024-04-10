#include "CountTriggerAction.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCountTriggerAction::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPCountTriggerAction::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCountTriggerAction& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 36);
    VEC_SEPARATOR_I
    o_value.m_unkVecInt = gd::vector<int>();
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPCountTriggerAction& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 36);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
}