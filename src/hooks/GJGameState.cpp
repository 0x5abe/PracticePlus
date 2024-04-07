#include "GJGameState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPGJGameState::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPGJGameState::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGJGameState& o_value) {
    i_stream >> o_value.m_unk0;
}

inline void operator<<(OutputStream& o_stream, PPGJGameState& i_value) {
}