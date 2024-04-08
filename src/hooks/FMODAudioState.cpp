#include "FMODAudioState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPFMODAudioState::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPFMODAudioState::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPFMODAudioState& o_value) {
    i_stream >> o_value.m_unkFloat1;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat2;
    MAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairIntIntFMODSoundTween1;
    MAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairIntIntFMODSoundTween2;
    MAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairIntIntFMODSoundTween3;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat1;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat2;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat3;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat4;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat5;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat6;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat7;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat8;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat9;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFloat10;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFMODQueuedMusic1;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFMODQueuedMusic2;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapIntFMODSoundState;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkInt1;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt2;
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPFMODAudioState& i_value) {
    o_stream << i_value.m_unkFloat1;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat2;
    MAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairIntIntFMODSoundTween1;
    MAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairIntIntFMODSoundTween2;
    MAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairIntIntFMODSoundTween3;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat1;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat2;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat3;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat4;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat5;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat6;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat7;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat8;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat9;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFloat10;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFMODQueuedMusic1;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFMODQueuedMusic2;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapIntFMODSoundState;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkInt1;
    SEPARATOR_O
    o_stream << i_value.m_unkInt2;
    SEPARATOR_O
}