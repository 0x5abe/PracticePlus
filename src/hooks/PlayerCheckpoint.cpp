#include "PlayerCheckpoint.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPPlayerCheckpoint::load(InputStream& i_stream) {
    reinterpret_cast<PPCCNode*>(this)->load(i_stream);
    i_stream >> *this;
}

void PPPlayerCheckpoint::save(OutputStream& o_stream) {
    reinterpret_cast<PPCCNode*>(this)->save(o_stream);
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPPlayerCheckpoint& o_value) {
    i_stream >> o_value.m_position;
    SEPARATOR_I
    i_stream >> o_value.m_lastPosition;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt1;
    SEPARATOR_I
    i_stream >> o_value.m_isUpsideDown;
    SEPARATOR_I
    i_stream >> o_value.m_unk7b3;
    SEPARATOR_I
    i_stream >> o_value.m_isShip;
    SEPARATOR_I
    i_stream >> o_value.m_isBall;
    SEPARATOR_I
    i_stream >> o_value.m_isBird;
    SEPARATOR_I
    i_stream >> o_value.m_isSwing;
    SEPARATOR_I
    i_stream >> o_value.m_isDart;
    SEPARATOR_I
    i_stream >> o_value.m_isRobot;
    SEPARATOR_I
    i_stream >> o_value.m_isSpider;
    SEPARATOR_I
    i_stream >> o_value.m_isOnGround;
    SEPARATOR_I
    i_stream >> o_value.m_hasGhostTrail;
    SEPARATOR_I
    i_stream.read((char*)o_value.m_unkBytes1, 4);
    SEPARATOR_I
    i_stream >> o_value.m_speed;
    SEPARATOR_I
    i_stream >> o_value.m_isHidden;
    SEPARATOR_I
    i_stream >> o_value.m_isGoingLeft;
    SEPARATOR_I
    i_stream.read((char*)o_value.m_unkBytes2, 42);
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat1;
    SEPARATOR_I
    i_stream >> o_value.m_possiblyFlags;
    SEPARATOR_I
    i_stream >> o_value.m_timeOrPercentRelated;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_yPositionVector;
    VEC_SEPARATOR_I
    i_stream.read((char*)o_value.m_unkBytes3, 8);
    log::info("PlayerCheckpoint o_value.m_unkBytes3 in: {}", *(double*)o_value.m_unkBytes3);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPPlayerCheckpoint& i_value) {
    o_stream << i_value.m_position;
    SEPARATOR_O
    o_stream << i_value.m_lastPosition;
    SEPARATOR_O
    o_stream << i_value.m_unkInt1;
    SEPARATOR_O
    o_stream << i_value.m_isUpsideDown;
    SEPARATOR_O
    o_stream << i_value.m_unk7b3;
    SEPARATOR_O
    o_stream << i_value.m_isShip;
    SEPARATOR_O
    o_stream << i_value.m_isBall;
    SEPARATOR_O
    o_stream << i_value.m_isBird;
    SEPARATOR_O
    o_stream << i_value.m_isSwing;
    SEPARATOR_O
    o_stream << i_value.m_isDart;
    SEPARATOR_O
    o_stream << i_value.m_isRobot;
    SEPARATOR_O
    o_stream << i_value.m_isSpider;
    SEPARATOR_O
    o_stream << i_value.m_isOnGround;
    SEPARATOR_O
    o_stream << i_value.m_hasGhostTrail;
    SEPARATOR_O
    o_stream.write((char*)i_value.m_unkBytes1, 4);
    SEPARATOR_O
    o_stream << i_value.m_speed;
    SEPARATOR_O
    o_stream << i_value.m_isHidden;
    SEPARATOR_O
    o_stream << i_value.m_isGoingLeft;
    SEPARATOR_O
    o_stream.write((char*)i_value.m_unkBytes2, 42);
    SEPARATOR_O
    o_stream << i_value.m_unkFloat1;
    SEPARATOR_O
    o_stream << i_value.m_possiblyFlags;
    SEPARATOR_O
    o_stream << i_value.m_timeOrPercentRelated;
    VEC_SEPARATOR_O
    o_stream << i_value.m_yPositionVector;
    VEC_SEPARATOR_O
    o_stream.write((char*)i_value.m_unkBytes3, 8);
    log::info("PlayerCheckpoint i_value.m_unkBytes3 out: {}", *(double*)i_value.m_unkBytes3);
    SEPARATOR_O
}