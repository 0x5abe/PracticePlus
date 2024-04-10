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
    i_stream >> o_value.m_zoom;
    SEPARATOR_I
    i_stream >> o_value.m_cameraOffset;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint1;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint2;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint3;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint4;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint5;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint6;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint7;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint8;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint9;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint10;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint11;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint12;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint13;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint14;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint15;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint16;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint17;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint18;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint19;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint20;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint21;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint22;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint23;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint24;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint25;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint26;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint27;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint28;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint29;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool1;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt1;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool2;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt2;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool3;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint30;
    SEPARATOR_I
    i_stream >> o_value.m_middleGroundOffsetY;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt3;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt4;
    SEPARATOR_I
    i_stream >> o_value.m_unkShort1;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat2;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat3;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt5;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt6;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt7;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt8;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt9;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt10;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt11;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat4;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint1;
    SEPARATOR_I
    i_stream >> o_value.m_portalY;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool4;
    SEPARATOR_I
    i_stream >> o_value.m_gravityRelated;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt12;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt13;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt14;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt15;
    SEPARATOR_I
    i_stream >> o_value.m_unkShort2;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool5;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool6;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat5;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat6;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat7;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat8;
    SEPARATOR_I
    i_stream >> o_value.m_screenRotation;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt16;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool7;
    SEPARATOR_I
    i_stream >> o_value.m_timeWarpFactor;
    SEPARATOR_I
    i_stream >> o_value.m_timeWarpRelated;
    SEPARATOR_I
    i_stream >> o_value.m_currentChannel;
    SEPARATOR_I
    i_stream >> o_value.m_unkInt17;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_spawnChannelRelated0;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_spawnChannelRelated1;
    UMAP_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkDouble1;
    SEPARATOR_I
    i_stream >> o_value.m_unkDouble2;
    SEPARATOR_I
    i_stream >> o_value.m_unkDouble3;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint2;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint3;
    SEPARATOR_I
    i_stream >> o_value.m_unk1f8;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint4;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint5;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint6;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint7;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint8;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint9;
    SEPARATOR_I
    i_stream >> o_value.m_cameraMove;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool8;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool9;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool10;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool11;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool12;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool13;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool14;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool15;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool16;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool17;
    SEPARATOR_I
    i_stream >> o_value.m_isDualMode;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool18;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat9;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_tweenActions;
    UMAP_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_cameraEdgeValue0;
    SEPARATOR_I
    i_stream >> o_value.m_cameraEdgeValue1;
    SEPARATOR_I
    i_stream >> o_value.m_cameraEdgeValue2;
    SEPARATOR_I
    i_stream >> o_value.m_cameraEdgeValue3;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_gameObjectPhysics;
    UMAP_SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecFloat1;
    VEC_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkUint10;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint11;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint12;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint31;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat10;
    SEPARATOR_I
    i_stream >> o_value.m_timeModRelated;
    SEPARATOR_I
    i_stream >> o_value.m_timeModRelated2;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairIntIntInt;
    UMAP_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkUint13;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint32;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint33;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool19;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool20;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool21;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool22;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool23;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool24;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint14;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool25;
    SEPARATOR_I
    i_stream >> o_value.m_cameraShakeEnabled;
    SEPARATOR_I
    i_stream >> o_value.m_cameraShakeFactor;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint15;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint16;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint64_1;
    SEPARATOR_I
    i_stream >> o_value.m_unkPoint34;
    SEPARATOR_I
    i_stream >> o_value.dualRelated;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_stateObjects;
    UMAP_SEPARATOR_I
    MAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairGJGameEventIntVectorEventTriggerInstance;
    MAP_SEPARATOR_I
    i_stream >> o_value.m_unkMapPairGJGameEventIntInt;
    MAP_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapEnterEffectInstanceVectors1;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_unorderedMapEnterEffectInstanceVectors2;
    UMAP_SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt1;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_unkVecInt2;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_enterEffectInstances1;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_enterEffectInstances2;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_enterEffectInstances3;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_enterEffectInstances4;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_enterEffectInstances5;
    VEC_SEPARATOR_I
    USET_SEPARATOR_I
    i_stream >> o_value.m_unkUnorderedSet1;
    USET_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkBool26;
    SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_advanceFollowInstances;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_dynamicObjActions1;
    VEC_SEPARATOR_I
    i_stream >> o_value.m_dynamicObjActions2;
    VEC_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkBool27;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool28;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint17;
    SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.unkUMap8;
    UMAP_SEPARATOR_I
    MAP_SEPARATOR_I
    i_stream >> o_value.proximityVolumeRelated;
    MAP_SEPARATOR_I
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_songChannelStates;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_songTriggerStateVectors;
    UMAP_SEPARATOR_I
    VEC_SEPARATOR_I
    i_stream >> o_value.m_sfxTriggerStates;
    VEC_SEPARATOR_I
    SEPARATOR_I
    i_stream >> o_value.m_unkBool29;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint18;
    SEPARATOR_I
    i_stream >> o_value.m_ground;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint19;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool30;
    SEPARATOR_I
    i_stream >> o_value.m_unkUint20;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool31;
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPGJGameState& i_value) {
    o_stream << i_value.m_zoom;
    SEPARATOR_O
    o_stream << i_value.m_cameraOffset;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint1;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint2;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint3;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint4;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint5;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint6;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint7;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint8;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint9;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint10;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint11;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint12;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint13;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint14;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint15;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint16;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint17;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint18;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint19;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint20;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint21;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint22;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint23;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint24;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint25;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint26;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint27;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint28;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint29;
    SEPARATOR_O
    o_stream << i_value.m_unkBool1;
    SEPARATOR_O
    o_stream << i_value.m_unkInt1;
    SEPARATOR_O
    o_stream << i_value.m_unkBool2;
    SEPARATOR_O
    o_stream << i_value.m_unkInt2;
    SEPARATOR_O
    o_stream << i_value.m_unkBool3;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint30;
    SEPARATOR_O
    o_stream << i_value.m_middleGroundOffsetY;
    SEPARATOR_O
    o_stream << i_value.m_unkInt3;
    SEPARATOR_O
    o_stream << i_value.m_unkInt4;
    SEPARATOR_O
    o_stream << i_value.m_unkShort1;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat2;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat3;
    SEPARATOR_O
    o_stream << i_value.m_unkInt5;
    SEPARATOR_O
    o_stream << i_value.m_unkInt6;
    SEPARATOR_O
    o_stream << i_value.m_unkInt7;
    SEPARATOR_O
    o_stream << i_value.m_unkInt8;
    SEPARATOR_O
    o_stream << i_value.m_unkInt9;
    SEPARATOR_O
    o_stream << i_value.m_unkInt10;
    SEPARATOR_O
    o_stream << i_value.m_unkInt11;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat4;
    SEPARATOR_O
    o_stream << i_value.m_unkUint1;
    SEPARATOR_O
    o_stream << i_value.m_portalY;
    SEPARATOR_O
    o_stream << i_value.m_unkBool4;
    SEPARATOR_O
    o_stream << i_value.m_gravityRelated;
    SEPARATOR_O
    o_stream << i_value.m_unkInt12;
    SEPARATOR_O
    o_stream << i_value.m_unkInt13;
    SEPARATOR_O
    o_stream << i_value.m_unkInt14;
    SEPARATOR_O
    o_stream << i_value.m_unkInt15;
    SEPARATOR_O
    o_stream << i_value.m_unkShort2;
    SEPARATOR_O
    o_stream << i_value.m_unkBool5;
    SEPARATOR_O
    o_stream << i_value.m_unkBool6;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat5;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat6;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat7;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat8;
    SEPARATOR_O
    o_stream << i_value.m_screenRotation;
    SEPARATOR_O
    o_stream << i_value.m_unkInt16;
    SEPARATOR_O
    o_stream << i_value.m_unkBool7;
    SEPARATOR_O
    o_stream << i_value.m_timeWarpFactor;
    SEPARATOR_O
    o_stream << i_value.m_timeWarpRelated;
    SEPARATOR_O
    o_stream << i_value.m_currentChannel;
    SEPARATOR_O
    o_stream << i_value.m_unkInt17;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_spawnChannelRelated0;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_spawnChannelRelated1;
    UMAP_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkDouble1;
    SEPARATOR_O
    o_stream << i_value.m_unkDouble2;
    SEPARATOR_O
    o_stream << i_value.m_unkDouble3;
    SEPARATOR_O
    o_stream << i_value.m_unkUint2;
    SEPARATOR_O
    o_stream << i_value.m_unkUint3;
    SEPARATOR_O
    o_stream << i_value.m_unk1f8;
    SEPARATOR_O
    o_stream << i_value.m_unkUint4;
    SEPARATOR_O
    o_stream << i_value.m_unkUint5;
    SEPARATOR_O
    o_stream << i_value.m_unkUint6;
    SEPARATOR_O
    o_stream << i_value.m_unkUint7;
    SEPARATOR_O
    o_stream << i_value.m_unkUint8;
    SEPARATOR_O
    o_stream << i_value.m_unkUint9;
    SEPARATOR_O
    o_stream << i_value.m_cameraMove;
    SEPARATOR_O
    o_stream << i_value.m_unkBool8;
    SEPARATOR_O
    o_stream << i_value.m_unkBool9;
    SEPARATOR_O
    o_stream << i_value.m_unkBool10;
    SEPARATOR_O
    o_stream << i_value.m_unkBool11;
    SEPARATOR_O
    o_stream << i_value.m_unkBool12;
    SEPARATOR_O
    o_stream << i_value.m_unkBool13;
    SEPARATOR_O
    o_stream << i_value.m_unkBool14;
    SEPARATOR_O
    o_stream << i_value.m_unkBool15;
    SEPARATOR_O
    o_stream << i_value.m_unkBool16;
    SEPARATOR_O
    o_stream << i_value.m_unkBool17;
    SEPARATOR_O
    o_stream << i_value.m_isDualMode;
    SEPARATOR_O
    o_stream << i_value.m_unkBool18;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat9;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_tweenActions;
    UMAP_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_cameraEdgeValue0;
    SEPARATOR_O
    o_stream << i_value.m_cameraEdgeValue1;
    SEPARATOR_O
    o_stream << i_value.m_cameraEdgeValue2;
    SEPARATOR_O
    o_stream << i_value.m_cameraEdgeValue3;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_gameObjectPhysics;
    UMAP_SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecFloat1;
    VEC_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkUint10;
    SEPARATOR_O
    o_stream << i_value.m_unkUint11;
    SEPARATOR_O
    o_stream << i_value.m_unkUint12;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint31;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat10;
    SEPARATOR_O
    o_stream << i_value.m_timeModRelated;
    SEPARATOR_O
    o_stream << i_value.m_timeModRelated2;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairIntIntInt;
    UMAP_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkUint13;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint32;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint33;
    SEPARATOR_O
    o_stream << i_value.m_unkBool19;
    SEPARATOR_O
    o_stream << i_value.m_unkBool20;
    SEPARATOR_O
    o_stream << i_value.m_unkBool21;
    SEPARATOR_O
    o_stream << i_value.m_unkBool22;
    SEPARATOR_O
    o_stream << i_value.m_unkBool23;
    SEPARATOR_O
    o_stream << i_value.m_unkBool24;
    SEPARATOR_O
    o_stream << i_value.m_unkUint14;
    SEPARATOR_O
    o_stream << i_value.m_unkBool25;
    SEPARATOR_O
    o_stream << i_value.m_cameraShakeEnabled;
    SEPARATOR_O
    o_stream << i_value.m_cameraShakeFactor;
    SEPARATOR_O
    o_stream << i_value.m_unkUint15;
    SEPARATOR_O
    o_stream << i_value.m_unkUint16;
    SEPARATOR_O
    o_stream << i_value.m_unkUint64_1;
    SEPARATOR_O
    o_stream << i_value.m_unkPoint34;
    SEPARATOR_O
    o_stream << i_value.dualRelated;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_stateObjects;
    UMAP_SEPARATOR_O
    MAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairGJGameEventIntVectorEventTriggerInstance;
    MAP_SEPARATOR_O
    o_stream << i_value.m_unkMapPairGJGameEventIntInt;
    MAP_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapEnterEffectInstanceVectors1;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_unorderedMapEnterEffectInstanceVectors2;
    UMAP_SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt1;
    VEC_SEPARATOR_O
    o_stream << i_value.m_unkVecInt2;
    VEC_SEPARATOR_O
    o_stream << i_value.m_enterEffectInstances1;
    VEC_SEPARATOR_O
    o_stream << i_value.m_enterEffectInstances2;
    VEC_SEPARATOR_O
    o_stream << i_value.m_enterEffectInstances3;
    VEC_SEPARATOR_O
    o_stream << i_value.m_enterEffectInstances4;
    VEC_SEPARATOR_O
    o_stream << i_value.m_enterEffectInstances5;
    VEC_SEPARATOR_O
    USET_SEPARATOR_O
    o_stream << i_value.m_unkUnorderedSet1;
    USET_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkBool26;
    SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_advanceFollowInstances;
    VEC_SEPARATOR_O
    o_stream << i_value.m_dynamicObjActions1;
    VEC_SEPARATOR_O
    o_stream << i_value.m_dynamicObjActions2;
    VEC_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkBool27;
    SEPARATOR_O
    o_stream << i_value.m_unkBool28;
    SEPARATOR_O
    o_stream << i_value.m_unkUint17;
    SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.unkUMap8;
    UMAP_SEPARATOR_O
    MAP_SEPARATOR_O
    o_stream << i_value.proximityVolumeRelated;
    MAP_SEPARATOR_O
    UMAP_SEPARATOR_O
    o_stream << i_value.m_songChannelStates;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_songTriggerStateVectors;
    UMAP_SEPARATOR_O
    VEC_SEPARATOR_O
    o_stream << i_value.m_sfxTriggerStates;
    VEC_SEPARATOR_O
    SEPARATOR_O
    o_stream << i_value.m_unkBool29;
    SEPARATOR_O
    o_stream << i_value.m_unkUint18;
    SEPARATOR_O
    o_stream << i_value.m_ground;
    SEPARATOR_O
    o_stream << i_value.m_unkUint19;
    SEPARATOR_O
    o_stream << i_value.m_unkBool30;
    SEPARATOR_O
    o_stream << i_value.m_unkUint20;
    SEPARATOR_O
    o_stream << i_value.m_unkBool31;
    SEPARATOR_O
}