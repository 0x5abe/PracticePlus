#include "SequenceTriggerState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPSequenceTriggerState::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPSequenceTriggerState::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPSequenceTriggerState& o_value) {
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkUnorderedMap1;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkUnorderedMap2;
    UMAP_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPSequenceTriggerState& i_value) {
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkUnorderedMap1;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkUnorderedMap2;
    UMAP_SEPARATOR_O
}