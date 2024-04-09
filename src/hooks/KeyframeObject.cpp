#include "KeyframeObject.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPKeyframeObject::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPKeyframeObject::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPKeyframeObject& o_value) {
    log::info("INSIDE KeyframeObject save");
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 32);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble1;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble2;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble3;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble4;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble5;
    VEC_SEPARATOR_I
    SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 52);
    SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble6;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble7;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble8;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble9;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecDouble10;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_3), 132);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPKeyframeObject& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 32);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble1;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble2;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble3;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble4;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble5;
    VEC_SEPARATOR_O
    SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 52);
    SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble6;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble7;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble8;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble9;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecDouble10;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_3), 132);
    SEPARATOR_O
}