
#include "InputStream.hpp"
#include "Geode/binding/AdvancedFollowInstance.hpp"
#include "Geode/binding/CAState.hpp"
#include "Geode/binding/EventTriggerInstance.hpp"
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>
#include <hooks/SequenceTriggerState.hpp>
#include <hooks/FMODQueuedMusic.hpp>
#include <hooks/FMODSoundState_padded.hpp>
#include <hooks/TimerItem_padded.hpp>
#include <hooks/TimerTriggerAction.hpp>
#include <hooks/KeyframeObject.hpp>
#include <hooks/GroupCommandObject2.hpp>
#include <hooks/SpawnTriggerAction.hpp>
#include <hooks/ToggleTriggerAction.hpp>
#include <hooks/CollisionTriggerAction.hpp>
#include <hooks/TouchToggleAction.hpp>
#include <hooks/CountTriggerAction.hpp>
#include <hooks/EventTriggerInstance.hpp>
#include <hooks/EnterEffectInstance.hpp>
#include <hooks/AdvancedFollowInstance.hpp>
#include <hooks/CAState.hpp>

//vector

template<class T, class U>
inline void readGenericVector(InputStream* i_stream, std::vector<T>& o_value) {
    o_value = std::vector<T>();
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomRead SIZE in: {}", l_size);
    if (l_size == 0) return;
    o_value.resize(l_size);
    for (int i = 0; i < l_size; i++) {
        geode::log::info("VECTOR SIZE CustomRead SIZE in TRYING TO LOAD: {}", l_size);
        reinterpret_cast<U&>(o_value[i]).load(*i_stream);
    }
}

template <>
void InputStream::operator>><DynamicSaveObject>(std::vector<DynamicSaveObject>& o_value) {
    readGenericVector<DynamicSaveObject, PPDynamicSaveObject>(this, o_value);
}

template <>
void InputStream::operator>><ActiveSaveObject1>(std::vector<ActiveSaveObject1>& o_value) {
    readGenericVector<ActiveSaveObject1, PPActiveSaveObject1>(this, o_value);
}

template <>
void InputStream::operator>><ActiveSaveObject2>(std::vector<ActiveSaveObject2>& o_value) {
    readGenericVector<ActiveSaveObject2, PPActiveSaveObject2>(this, o_value);
}

template <>
void InputStream::operator>><CountTriggerAction>(std::vector<CountTriggerAction>& o_value) {
    readGenericVector<CountTriggerAction, PPCountTriggerAction>(this, o_value);
}

template <>
void InputStream::operator>><TouchToggleAction>(std::vector<TouchToggleAction>& o_value) {
    readGenericVector<TouchToggleAction, PPTouchToggleAction>(this, o_value);
}

template <>
void InputStream::operator>><CollisionTriggerAction>(std::vector<CollisionTriggerAction>& o_value) {
    readGenericVector<CollisionTriggerAction, PPCollisionTriggerAction>(this, o_value);
}

template <>
void InputStream::operator>><ToggleTriggerAction>(std::vector<ToggleTriggerAction>& o_value) {
    readGenericVector<ToggleTriggerAction, PPToggleTriggerAction>(this, o_value);
}

template <>
void InputStream::operator>><SpawnTriggerAction>(std::vector<SpawnTriggerAction>& o_value) {
    readGenericVector<SpawnTriggerAction, PPSpawnTriggerAction>(this, o_value);
}

template <>
void InputStream::operator>><GroupCommandObject2>(std::vector<GroupCommandObject2>& o_value) {
    readGenericVector<GroupCommandObject2, PPGroupCommandObject2>(this, o_value);
}

template <>
void InputStream::operator>><KeyframeObject>(std::vector<KeyframeObject>& o_value) {
    readGenericVector<KeyframeObject, PPKeyframeObject>(this, o_value);
}

template <>
void InputStream::operator>><TimerTriggerAction>(std::vector<TimerTriggerAction>& o_value) {
    readGenericVector<TimerTriggerAction, PPTimerTriggerAction>(this, o_value);
}

template <>
void InputStream::operator>><EventTriggerInstance>(std::vector<EventTriggerInstance>& o_value) {
    readGenericVector<EventTriggerInstance, PPEventTriggerInstance>(this, o_value);
}

template <>
void InputStream::operator>><EnterEffectInstance>(std::vector<EnterEffectInstance>& o_value) {
    readGenericVector<EnterEffectInstance, PPEnterEffectInstance>(this, o_value);
}

template <>
void InputStream::operator>><AdvancedFollowInstance>(std::vector<AdvancedFollowInstance>& o_value) {
    readGenericVector<AdvancedFollowInstance, PPAdvancedFollowInstance>(this, o_value);
}

template <>
void InputStream::operator>><CAState>(std::vector<CAState>& o_value) {
    readGenericVector<CAState, PPCAState>(this, o_value);
}

//unordered_map

template<class K, class V, class W>
inline void readGenericUnorderedMap(InputStream* i_stream, gd::unordered_map<K,V>& o_value) {
    if (o_value.size() != 0) {
        geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
        o_value.clear();
    }
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("Unordered Map CustomRead SIZE in: {}", l_size);
    for (int i = 0; i < l_size; i++) {
        K l_key;
        i_stream->read(reinterpret_cast<char*>(&l_key), sizeof(K));
        reinterpret_cast<W&>(o_value[l_key]).load(*i_stream);
    }
}

template <>
void InputStream::operator>><int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& o_value) {
    readGenericUnorderedMap<int, SequenceTriggerState, PPSequenceTriggerState>(this, o_value);
}

template <>
void InputStream::operator>><int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& o_value) {
    readGenericUnorderedMap<int, FMODQueuedMusic, PPFMODQueuedMusic>(this, o_value);
}

template <>
void InputStream::operator>><int, FMODSoundState_padded>(gd::unordered_map<int, FMODSoundState_padded>& o_value) {
    readGenericUnorderedMap<int, FMODSoundState_padded, PPFMODSoundState_padded>(this, o_value);
}

template <>
void InputStream::operator>><int, TimerItem_padded>(gd::unordered_map<int, TimerItem_padded>& o_value) {
    readGenericUnorderedMap<int, TimerItem_padded, PPTimerItem_padded>(this, o_value);
}

template <>
void InputStream::operator>><int, EnhancedGameObject*>(gd::unordered_map<int, EnhancedGameObject*>& o_value) {
    unsigned int l_size;
    this->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("Unordered Map EnhancedGameObject* CustomRead SIZE in: {}", l_size);
    for (int i = 0; i < l_size; i++) {
        int l_key;
        int l_objectIndex;
        this->read(reinterpret_cast<char*>(&l_key), sizeof(int));
        this->read(reinterpret_cast<char*>(&l_objectIndex), sizeof(int));

        PlayLayer* l_playLayer = PlayLayer::get();
        if (l_playLayer && l_objectIndex != -1) {
            o_value[l_key] = static_cast<EnhancedGameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
        } else {
            o_value[l_key] = nullptr;
        }
    }
}