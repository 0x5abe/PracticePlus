#include "EffectManagerState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPEffectManagerState::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPEffectManagerState::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPEffectManagerState& o_value) {
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecCAState;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecPulseEffectAction;
    VEC_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_vectorPulseEffectAction;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_vectorCountTriggerAction;
    UMAP_SEPARATOR_I
    USET_SEPARATOR_I
    i_stream >> o_value.m_unorderedSet_int1;
    USET_SEPARATOR_I
    MAP_SEPARATOR_I
    i_stream >> o_value.m_mapInt_Int;
    MAP_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_OpacityEffectAction;
    UMAP_SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_vectorTouchToggleAction;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_vectorCollisionTriggerAction;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_vectorToggleTriggerAction;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_vectorSpawnTriggerAction;
    VEC_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_int;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_bool;
    UMAP_SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_vectorGroupCommandObject2;
    VEC_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_pair_double_double;
    UMAP_SEPARATOR_I
    USET_SEPARATOR_I
    i_stream >> o_value.m_unorderedSet_int2;
    USET_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_TimerItem;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapInt_vectorTimerTriggerAction;
    UMAP_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPEffectManagerState& i_value) {
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecCAState;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecPulseEffectAction;
    VEC_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_vectorPulseEffectAction;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_vectorCountTriggerAction;
    UMAP_SEPARATOR_O
    USET_SEPARATOR_O
    o_stream << i_value.m_unorderedSet_int1;
    USET_SEPARATOR_O
    MAP_SEPARATOR_O
    o_stream << i_value.m_mapInt_Int;
    MAP_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_OpacityEffectAction;
    UMAP_SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_vectorTouchToggleAction;
    VEC_SEPARATOR_O
    o_stream << i_value.m_vectorCollisionTriggerAction;
    VEC_SEPARATOR_O
    o_stream << i_value.m_vectorToggleTriggerAction;
    VEC_SEPARATOR_O
    o_stream << i_value.m_vectorSpawnTriggerAction;
    VEC_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_int;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_bool;
    UMAP_SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_vectorGroupCommandObject2;
    VEC_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_pair_double_double;
    UMAP_SEPARATOR_O
    USET_SEPARATOR_O
    o_stream << i_value.m_unorderedSet_int2;
    USET_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_TimerItem;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapInt_vectorTimerTriggerAction;
    UMAP_SEPARATOR_O
}