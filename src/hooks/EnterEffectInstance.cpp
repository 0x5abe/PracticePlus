#include "EnterEffectInstance.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPEnterEffectInstance::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPEnterEffectInstance::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPEnterEffectInstance& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 180);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 4);
    VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPEnterEffectInstance& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 180);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 4);
    VEC_SEPARATOR_O
}