#include "FMODQueuedMusic.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPFMODQueuedMusic::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPFMODQueuedMusic::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPFMODQueuedMusic& o_value) {
    STR_SEPARATOR_I
    i_stream >> o_value.m_unkString;
    STR_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.__pad16), 56);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPFMODQueuedMusic& i_value) {
    STR_SEPARATOR_O
    o_stream << i_value.m_unkString;
    STR_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.__pad16), 56);
    SEPARATOR_O
}