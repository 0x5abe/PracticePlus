#include "GroupCommandObject2.hpp"
#include "Geode/binding/KeyframeObject.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>
#include <vector>

using namespace geode::prelude;

void PPGroupCommandObject2::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPGroupCommandObject2::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGroupCommandObject2& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 436);
    VEC_SEPARATOR_I
    o_value.m_unkVecKeyframeObject = gd::vector<KeyframeObject>();
    i_stream >> o_value.m_unkVecKeyframeObject;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 16);
    VEC_SEPARATOR_I
    o_value.m_unkVecInt = gd::vector<int>();
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_3), 12);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPGroupCommandObject2& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 436);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecKeyframeObject;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 16);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_3), 12);
    SEPARATOR_O
}