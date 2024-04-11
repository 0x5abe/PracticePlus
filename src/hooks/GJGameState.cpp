#include "GJGameState.hpp"
#include "EnterEffectInstance.hpp"
#include "Geode/Enums.hpp"
#include "Geode/binding/EnhancedGameObject.hpp"
#include "Geode/binding/EnterEffectInstance.hpp"
#include "Geode/binding/EventTriggerInstance.hpp"
#include "Geode/binding/GameObjectPhysics.hpp"
#include "Geode/binding/PlayLayer.hpp"
#include "Geode/binding/SFXTriggerInstance.hpp"
#include "Geode/binding/SFXTriggerState.hpp"
#include "Geode/binding/SongChannelState.hpp"
#include "Geode/binding/SongTriggerState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>
#include <hooks/EventTriggerInstance.hpp>

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
    int l_objectIndex;
    PlayLayer* l_playLayer = PlayLayer::get();
    i_stream >> l_objectIndex;
    if (l_playLayer && l_objectIndex != -1) {
        o_value.m_unkGameObjPtr1 = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
    } else {
        o_value.m_unkGameObjPtr1 = nullptr;
    }
    SEPARATOR_I
    i_stream >> l_objectIndex;
    if (l_playLayer && l_objectIndex != -1) {
        o_value.m_unkGameObjPtr2 = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
    } else {
        o_value.m_unkGameObjPtr2 = nullptr;
    }
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
    int l_objectIndex = -1;
    if (i_value.m_unkGameObjPtr1) {
        l_objectIndex = i_value.m_unkGameObjPtr1->m_uniqueID-12;
    }
    o_stream << l_objectIndex;
    SEPARATOR_O
    l_objectIndex = -1;
    if (i_value.m_unkGameObjPtr2) {
        l_objectIndex = i_value.m_unkGameObjPtr2->m_uniqueID-12;
    }
    o_stream << l_objectIndex;
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

#ifdef PP_DEBUG
void PPGJGameState::describe() {
    log::info("[PPGJGameState - describe] m_zoom: {}", m_zoom);
    log::info("[PPGJGameState - describe] m_cameraOffset: {}", m_cameraOffset);
    log::info("[PPGJGameState - describe] m_unkPoint1: {}", m_unkPoint1);
    log::info("[PPGJGameState - describe] m_unkPoint2: {}", m_unkPoint2);
    log::info("[PPGJGameState - describe] m_unkPoint3: {}", m_unkPoint3);
    log::info("[PPGJGameState - describe] m_unkPoint4: {}", m_unkPoint4);
    log::info("[PPGJGameState - describe] m_unkPoint5: {}", m_unkPoint5);
    log::info("[PPGJGameState - describe] m_unkPoint6: {}", m_unkPoint6);
    log::info("[PPGJGameState - describe] m_unkPoint7: {}", m_unkPoint7);
    log::info("[PPGJGameState - describe] m_unkPoint8: {}", m_unkPoint8);
    log::info("[PPGJGameState - describe] m_unkPoint9: {}", m_unkPoint9);
    log::info("[PPGJGameState - describe] m_unkPoint10: {}", m_unkPoint10);
    log::info("[PPGJGameState - describe] m_unkPoint11: {}", m_unkPoint11);
    log::info("[PPGJGameState - describe] m_unkPoint12: {}", m_unkPoint12);
    log::info("[PPGJGameState - describe] m_unkPoint13: {}", m_unkPoint13);
    log::info("[PPGJGameState - describe] m_unkPoint14: {}", m_unkPoint14);
    log::info("[PPGJGameState - describe] m_unkPoint15: {}", m_unkPoint15);
    log::info("[PPGJGameState - describe] m_unkPoint16: {}", m_unkPoint16);
    log::info("[PPGJGameState - describe] m_unkPoint17: {}", m_unkPoint17);
    log::info("[PPGJGameState - describe] m_unkPoint18: {}", m_unkPoint18);
    log::info("[PPGJGameState - describe] m_unkPoint19: {}", m_unkPoint19);
    log::info("[PPGJGameState - describe] m_unkPoint20: {}", m_unkPoint20);
    log::info("[PPGJGameState - describe] m_unkPoint21: {}", m_unkPoint21);
    log::info("[PPGJGameState - describe] m_unkPoint22: {}", m_unkPoint22);
    log::info("[PPGJGameState - describe] m_unkPoint23: {}", m_unkPoint23);
    log::info("[PPGJGameState - describe] m_unkPoint24: {}", m_unkPoint24);
    log::info("[PPGJGameState - describe] m_unkPoint25: {}", m_unkPoint25);
    log::info("[PPGJGameState - describe] m_unkPoint26: {}", m_unkPoint26);
    log::info("[PPGJGameState - describe] m_unkPoint27: {}", m_unkPoint27);
    log::info("[PPGJGameState - describe] m_unkPoint28: {}", m_unkPoint28);
    log::info("[PPGJGameState - describe] m_unkPoint29: {}", m_unkPoint29);
    log::info("[PPGJGameState - describe] m_unkBool1: {}", m_unkBool1);
    log::info("[PPGJGameState - describe] m_unkInt1: {}", m_unkInt1);
    log::info("[PPGJGameState - describe] m_unkBool2: {}", m_unkBool2);
    log::info("[PPGJGameState - describe] m_unkInt2: {}", m_unkInt2);
    log::info("[PPGJGameState - describe] m_unkBool3: {}", m_unkBool3);
    log::info("[PPGJGameState - describe] m_unkPoint30: {}", m_unkPoint30);
    log::info("[PPGJGameState - describe] m_middleGroundOffsetY: {}", m_middleGroundOffsetY);
    log::info("[PPGJGameState - describe] m_unkInt3: {}", m_unkInt3);
    log::info("[PPGJGameState - describe] m_unkInt4: {}", m_unkInt4);
    log::info("[PPGJGameState - describe] m_unkShort1: {}", m_unkShort1);
    log::info("[PPGJGameState - describe] m_unkFloat2: {}", m_unkFloat2);
    log::info("[PPGJGameState - describe] m_unkFloat3: {}", m_unkFloat3);
    log::info("[PPGJGameState - describe] m_unkInt5: {}", m_unkInt5);
    log::info("[PPGJGameState - describe] m_unkInt6: {}", m_unkInt6);
    log::info("[PPGJGameState - describe] m_unkInt7: {}", m_unkInt7);
    log::info("[PPGJGameState - describe] m_unkInt8: {}", m_unkInt8);
    log::info("[PPGJGameState - describe] m_unkInt9: {}", m_unkInt9);
    log::info("[PPGJGameState - describe] m_unkInt10: {}", m_unkInt10);
    log::info("[PPGJGameState - describe] m_unkInt11: {}", m_unkInt11);
    log::info("[PPGJGameState - describe] m_unkFloat4: {}", m_unkFloat4);
    log::info("[PPGJGameState - describe] m_unkUint1: {}", m_unkUint1);
    log::info("[PPGJGameState - describe] m_portalY: {}", m_portalY);
    log::info("[PPGJGameState - describe] m_unkBool4: {}", m_unkBool4);
    log::info("[PPGJGameState - describe] m_gravityRelated: {}", m_gravityRelated);
    log::info("[PPGJGameState - describe] m_unkInt12: {}", m_unkInt12);
    log::info("[PPGJGameState - describe] m_unkInt13: {}", m_unkInt13);
    log::info("[PPGJGameState - describe] m_unkInt14: {}", m_unkInt14);
    log::info("[PPGJGameState - describe] m_unkInt15: {}", m_unkInt15);
    log::info("[PPGJGameState - describe] m_unkShort2: {}", m_unkShort2);
    log::info("[PPGJGameState - describe] m_unkBool5: {}", m_unkBool5);
    log::info("[PPGJGameState - describe] m_unkBool6: {}", m_unkBool6);
    log::info("[PPGJGameState - describe] m_unkFloat5: {}", m_unkFloat5);
    log::info("[PPGJGameState - describe] m_unkFloat6: {}", m_unkFloat6);
    log::info("[PPGJGameState - describe] m_unkFloat7: {}", m_unkFloat7);
    log::info("[PPGJGameState - describe] m_unkFloat8: {}", m_unkFloat8);
    log::info("[PPGJGameState - describe] m_screenRotation: {}", m_screenRotation);
    log::info("[PPGJGameState - describe] m_unkInt16: {}", m_unkInt16);
    log::info("[PPGJGameState - describe] m_unkBool7: {}", m_unkBool7);
    log::info("[PPGJGameState - describe] m_timeWarpFactor: {}", m_timeWarpFactor);
    log::info("[PPGJGameState - describe] m_timeWarpRelated: {}", m_timeWarpRelated);
    log::info("[PPGJGameState - describe] m_currentChannel: {}", m_currentChannel);
    log::info("[PPGJGameState - describe] m_unkInt17: {}", m_unkInt17);
    int i = 0;
    for (std::pair<int, int> l_pair : m_spawnChannelRelated0) {
        log::info("[PPGJGameState - describe] m_spawnChannelRelated0 element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_spawnChannelRelated0 element {} value: {}", i, l_pair.second);
        i++;
    }
    i = 0;
    for (std::pair<int, bool> l_pair : m_spawnChannelRelated1) {
        log::info("[PPGJGameState - describe] m_spawnChannelRelated1 element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_spawnChannelRelated1 element {} value: {}", i, l_pair.second);
        i++;
    }
    log::info("[PPGJGameState - describe] m_unkDouble1: {}", m_unkDouble1);
    log::info("[PPGJGameState - describe] m_unkDouble2: {}", m_unkDouble2);
    log::info("[PPGJGameState - describe] m_unkDouble3: {}", m_unkDouble3);
    log::info("[PPGJGameState - describe] m_unkUint2: {}", m_unkUint2);
    log::info("[PPGJGameState - describe] m_unkUint3: {}", m_unkUint3);
    log::info("[PPGJGameState - describe] m_unk1f8: {}", m_unk1f8);
    log::info("[PPGJGameState - describe] m_unkUint4: {}", m_unkUint4);
    log::info("[PPGJGameState - describe] m_unkUint5: {}", m_unkUint5);
    log::info("[PPGJGameState - describe] m_unkUint6: {}", m_unkUint6);
    log::info("[PPGJGameState - describe] m_unkUint7: {}", m_unkUint7);
    int l_objectIndex = -1;
    if (m_unkGameObjPtr1) {
        l_objectIndex = m_unkGameObjPtr1->m_uniqueID-12;
    }
    log::info("[PPGJGameState - describe] m_unkGameObjPtr1 objectIndex: {}", l_objectIndex);
    l_objectIndex = -1;
    if (m_unkGameObjPtr2) {
        l_objectIndex = m_unkGameObjPtr2->m_uniqueID-12;
    }
    log::info("[PPGJGameState - describe] m_unkGameObjPtr2 objectIndex: {}", l_objectIndex);
    log::info("[PPGJGameState - describe] m_cameraMove: {}", m_cameraMove);
    log::info("[PPGJGameState - describe] m_unkBool8: {}", m_unkBool8);
    log::info("[PPGJGameState - describe] m_unkBool9: {}", m_unkBool9);
    log::info("[PPGJGameState - describe] m_unkBool10: {}", m_unkBool10);
    log::info("[PPGJGameState - describe] m_unkBool11: {}", m_unkBool11);
    log::info("[PPGJGameState - describe] m_unkBool12: {}", m_unkBool12);
    log::info("[PPGJGameState - describe] m_unkBool13: {}", m_unkBool13);
    log::info("[PPGJGameState - describe] m_unkBool14: {}", m_unkBool14);
    log::info("[PPGJGameState - describe] m_unkBool15: {}", m_unkBool15);
    log::info("[PPGJGameState - describe] m_unkBool16: {}", m_unkBool16);
    log::info("[PPGJGameState - describe] m_unkBool17: {}", m_unkBool17);
    log::info("[PPGJGameState - describe] m_isDualMode: {}", m_isDualMode);
    log::info("[PPGJGameState - describe] m_unkBool18: {}", m_unkBool18);
    log::info("[PPGJGameState - describe] m_unkFloat9: {}", m_unkFloat9);
    int l_size = m_tweenActions.size();
    log::info("[PPGJGameState - describe] m_tweenActions.size(): {}", l_size);
    i = 0;
    for (std::pair<int,GJValueTween> l_pair : m_tweenActions) {
        log::info("[PPGJGameState - describe] m_tweenActions element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_tweenActions element {} value (GJValueTween): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 40));
        i++;
    }
    log::info("[PPGJGameState - describe] m_cameraEdgeValue0: {}", m_cameraEdgeValue0);
    log::info("[PPGJGameState - describe] m_cameraEdgeValue1: {}", m_cameraEdgeValue1);
    log::info("[PPGJGameState - describe] m_cameraEdgeValue2: {}", m_cameraEdgeValue2);
    log::info("[PPGJGameState - describe] m_cameraEdgeValue3: {}", m_cameraEdgeValue3);
    l_size = m_gameObjectPhysics.size();
    log::info("[PPGJGameState - describe] m_gameObjectPhysics.size(): {}", l_size);
    i = 0;
    for (std::pair<int,GameObjectPhysics> l_pair : m_gameObjectPhysics) {
        log::info("[PPGJGameState - describe] m_gameObjectPhysics element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_gameObjectPhysics element {} value (GameObjectPhysics): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 40));
        i++;
    }
    l_size = m_unkVecFloat1.size();
    log::info("[PPGJGameState - describe] m_unkVecFloat1.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_unkVecFloat1[{}]: {}", i, m_unkVecFloat1[i]);
    }
    log::info("[PPGJGameState - describe] m_unkUint10: {}", m_unkUint10);
    log::info("[PPGJGameState - describe] m_unkUint11: {}", m_unkUint11);
    log::info("[PPGJGameState - describe] m_unkUint12: {}", m_unkUint12);
    log::info("[PPGJGameState - describe] m_unkPoint31: {}", m_unkPoint31);
    log::info("[PPGJGameState - describe] m_unkFloat10: {}", m_unkFloat10);
    log::info("[PPGJGameState - describe] m_timeModRelated: {}", m_timeModRelated);
    log::info("[PPGJGameState - describe] m_timeModRelated2: {}", m_timeModRelated2);
    i = 0;
    for (std::pair<std::pair<int, int>, int> l_pair : m_unkMapPairIntIntInt) {
        log::info("[PPGJGameState - describe] m_unkMapPairIntIntInt element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_unkMapPairIntIntInt element {} value: {}", i, l_pair.second);
        i++;
    }
    log::info("[PPGJGameState - describe] m_unkUint13: {}", m_unkUint13);
    log::info("[PPGJGameState - describe] m_unkPoint32: {}", m_unkPoint32);
    log::info("[PPGJGameState - describe] m_unkPoint33: {}", m_unkPoint33);
    log::info("[PPGJGameState - describe] m_unkBool19: {}", m_unkBool19);
    log::info("[PPGJGameState - describe] m_unkBool20: {}", m_unkBool20);
    log::info("[PPGJGameState - describe] m_unkBool21: {}", m_unkBool21);
    log::info("[PPGJGameState - describe] m_unkBool22: {}", m_unkBool22);
    log::info("[PPGJGameState - describe] m_unkBool23: {}", m_unkBool23);
    log::info("[PPGJGameState - describe] m_unkBool24: {}", m_unkBool24);
    log::info("[PPGJGameState - describe] m_unkUint14: {}", m_unkUint14);
    log::info("[PPGJGameState - describe] m_unkBool25: {}", m_unkBool25);
    log::info("[PPGJGameState - describe] m_cameraShakeEnabled: {}", m_cameraShakeEnabled);
    log::info("[PPGJGameState - describe] m_cameraShakeFactor: {}", m_cameraShakeFactor);
    log::info("[PPGJGameState - describe] m_unkUint15: {}", m_unkUint15);
    log::info("[PPGJGameState - describe] m_unkUint16: {}", m_unkUint16);
    log::info("[PPGJGameState - describe] m_unkUint64_1: {}", m_unkUint64_1);
    log::info("[PPGJGameState - describe] m_unkPoint34: {}", m_unkPoint34);
    log::info("[PPGJGameState - describe] dualRelated: {}", dualRelated);
    i = 0;
    for (std::pair<int, EnhancedGameObject*> l_pair : m_stateObjects) {
        log::info("[PPGJGameState - describe] m_stateObjects element {} key: {}", i, l_pair.first);
        int l_objectIndex = -1;
        if (!l_pair.second) {
            log::info("no game object??");
        } else {
            l_objectIndex = l_pair.second->m_uniqueID-12;
        }
        log::info("[PPGJGameState - describe] m_stateObjects element {} value (l_objectIndex): {}", i, l_objectIndex);
        i++;
    }
    i = 0;
    for (std::pair<std::pair<GJGameEvent,int>, std::vector<EventTriggerInstance>> l_pair : m_unkMapPairGJGameEventIntVectorEventTriggerInstance) {
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntVectorEventTriggerInstance element {} key.key: {}", i, *reinterpret_cast<int*>(&l_pair.first.first));
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntVectorEventTriggerInstance element {} key.value: {}", i, l_pair.first.second);
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntVectorEventTriggerInstance element {} value:", i);
        l_size = l_pair.second.size();
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntVectorEventTriggerInstance element {} value.size(): {}", i, l_size);
        for (int j = 0; j < l_size; j++) {
            log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntVectorEventTriggerInstance element {} value[{}]:", i, j);
            reinterpret_cast<PPEventTriggerInstance*>(&l_pair.second[j])->describe();
        }
        i++;
    }
    i = 0;
    for (std::pair<std::pair<GJGameEvent,int>, int> l_pair : m_unkMapPairGJGameEventIntInt) {
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntInt element {} key.key: {}", i, *reinterpret_cast<int*>(&l_pair.first.first));
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntInt element {} key.value: {}", i, l_pair.first.second);
        log::info("[PPGJGameState - describe] m_unkMapPairGJGameEventIntInt element {} value: {}", i, l_pair.second);
        i++;
    }
    i = 0;
    for (std::pair<int, std::vector<EnterEffectInstance>> l_pair : m_unorderedMapEnterEffectInstanceVectors1) {
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors1 element {} key.key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors1 element {} value:", i);
        l_size = l_pair.second.size();
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors1 element {} value.size(): {}", i, l_size);
        for (int j = 0; j < l_size; j++) {
            log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors1 element {} value[{}]:", i, j);
            reinterpret_cast<PPEnterEffectInstance*>(&l_pair.second[j])->describe();
        }
        i++;
    }
    i = 0;
    for (std::pair<int, std::vector<EnterEffectInstance>> l_pair : m_unorderedMapEnterEffectInstanceVectors2) {
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors2 element {} key.key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors2 element {} value:", i);
        l_size = l_pair.second.size();
        log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors2 element {} value.size(): {}", i, l_size);
        for (int j = 0; j < l_size; j++) {
            log::info("[PPGJGameState - describe] m_unorderedMapEnterEffectInstanceVectors2 element {} value[{}]:", i, j);
            reinterpret_cast<PPEnterEffectInstance*>(&l_pair.second[j])->describe();
        }
        i++;
    }
    l_size = m_unkVecInt1.size();
    log::info("[PPGJGameState - describe] m_unkVecInt1.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_unkVecInt1[{}]: {}", i, m_unkVecInt1[i]);
    }
    l_size = m_unkVecInt2.size();
    log::info("[PPGJGameState - describe] m_unkVecInt2.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_unkVecInt2[{}]: {}", i, m_unkVecInt2[i]);
    }
    l_size = m_enterEffectInstances1.size();
    log::info("[PPGJGameState - describe] m_enterEffectInstances1.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_enterEffectInstances1[{}]:", i);
        reinterpret_cast<PPEnterEffectInstance*>(&m_enterEffectInstances1[i])->describe();
    }
    l_size = m_enterEffectInstances2.size();
    log::info("[PPGJGameState - describe] m_enterEffectInstances2.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_enterEffectInstances2[{}]:", i);
        reinterpret_cast<PPEnterEffectInstance*>(&m_enterEffectInstances2[i])->describe();
    }
    l_size = m_enterEffectInstances3.size();
    log::info("[PPGJGameState - describe] m_enterEffectInstances3.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_enterEffectInstances3[{}]:", i);
        reinterpret_cast<PPEnterEffectInstance*>(&m_enterEffectInstances3[i])->describe();
    }
    l_size = m_enterEffectInstances4.size();
    log::info("[PPGJGameState - describe] m_enterEffectInstances4.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_enterEffectInstances4[{}]:", i);
        reinterpret_cast<PPEnterEffectInstance*>(&m_enterEffectInstances4[i])->describe();
    }
    l_size = m_enterEffectInstances5.size();
    log::info("[PPGJGameState - describe] m_enterEffectInstances5.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_enterEffectInstances5[{}]:", i);
        reinterpret_cast<PPEnterEffectInstance*>(&m_enterEffectInstances5[i])->describe();
    }
    i = 0;
    for (int l_value : m_unkUnorderedSet1) {
        log::info("[PPGJGameState - describe] m_unkUnorderedSet1 element {} value: {}", i, l_value);
        i++;
    }
    log::info("[PPGJGameState - describe] m_unkBool26: {}", m_unkBool26);
    l_size = m_advanceFollowInstances.size();
    log::info("[PPGJGameState - describe] m_advanceFollowInstances.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_advanceFollowInstances element {} value (AdvancedFollowInstance): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&m_advanceFollowInstances[i]), 28));
    }
    l_size = m_dynamicObjActions1.size();
    log::info("[PPGJGameState - describe] m_dynamicObjActions1.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_dynamicObjActions1 element {} value (DynamicObjectAction): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&m_dynamicObjActions1[i]), 60));
    }
    l_size = m_dynamicObjActions2.size();
    log::info("[PPGJGameState - describe] m_dynamicObjActions2.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_dynamicObjActions2 element {} value (DynamicObjectAction): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&m_dynamicObjActions2[i]), 60));
    }
    log::info("[PPGJGameState - describe] m_unkBool27: {}", m_unkBool27);
    log::info("[PPGJGameState - describe] m_unkBool28: {}", m_unkBool28);
    log::info("[PPGJGameState - describe] m_unkUint17: {}", m_unkUint17);
    i = 0;
    for (std::pair<int, std::vector<int>> l_pair : unkUMap8) {
        log::info("[PPGJGameState - describe] unkUMap8 element {} key.key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] unkUMap8 element {} value:", i);
        l_size = l_pair.second.size();
        log::info("[PPGJGameState - describe] unkUMap8 element {} value.size(): {}", i, l_size);
        for (int j = 0; j < l_size; j++) {
            log::info("[PPGJGameState - describe] unkUMap8 element {} value[{}]: {}", i, j, l_pair.second[j]);
        }
        i++;
    }
    i = 0;
    for (std::pair<std::pair<int, int>, SFXTriggerInstance> l_pair : proximityVolumeRelated) {
        log::info("[PPGJGameState - describe] proximityVolumeRelated element {} key.key: {}", i, l_pair.first.first);
        log::info("[PPGJGameState - describe] proximityVolumeRelated element {} key.value: {}", i, l_pair.first.second);
        log::info("[PPGJGameState - describe] proximityVolumeRelated element {} value (SFXTriggerInstance): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 16));
        i++;
    }
    i = 0;
    for (std::pair<int, SongChannelState> l_pair : m_songChannelStates) {
        log::info("[PPGJGameState - describe] m_songChannelStates element {} key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_songChannelStates element {} value (SongChannelState): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 36));
        i++;
    }
    i = 0;
    for (std::pair<int, std::vector<SongTriggerState>> l_pair : m_songTriggerStateVectors) {
        log::info("[PPGJGameState - describe] m_songTriggerStateVectors element {} key.key: {}", i, l_pair.first);
        log::info("[PPGJGameState - describe] m_songTriggerStateVectors element {} value:", i);
        l_size = l_pair.second.size();
        log::info("[PPGJGameState - describe] m_songTriggerStateVectors element {} value.size(): {}", i, l_size);
        for (int j = 0; j < l_size; j++) {
            log::info("[PPGJGameState - describe] m_songTriggerStateVectors element {} value[{}]: {}", i, j, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 16));
        }
        i++;
    }
    l_size = m_sfxTriggerStates.size();
    log::info("[PPGJGameState - describe] m_sfxTriggerStates.size(): {}", l_size);
    for (int i = 0; i < l_size; i++) {
        log::info("[PPGJGameState - describe] m_sfxTriggerStates element {} value (SFXTriggerState): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&m_sfxTriggerStates[i]), 160));
    }
    log::info("[PPGJGameState - describe] m_unkBool29: {}", m_unkBool29);
    log::info("[PPGJGameState - describe] m_unkUint18: {}", m_unkUint18);
    log::info("[PPGJGameState - describe] m_ground: {}", m_ground);
    log::info("[PPGJGameState - describe] m_unkUint19: {}", m_unkUint19);
    log::info("[PPGJGameState - describe] m_unkBool30: {}", m_unkBool30);
    log::info("[PPGJGameState - describe] m_unkUint20: {}", m_unkUint20);
    log::info("[PPGJGameState - describe] m_unkBool31: {}", m_unkBool31);
}
#endif