#include "CollisionTriggerAction.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCollisionTriggerAction::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPCollisionTriggerAction::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCollisionTriggerAction& o_value) {
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 32);
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt;
    VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPCollisionTriggerAction& i_value) {
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 32);
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt;
    VEC_SEPARATOR_O
}