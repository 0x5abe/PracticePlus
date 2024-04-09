
#include "InputStream.hpp"
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

//vector

template<class T, class U>
inline void readGenericVector(InputStream* i_stream, std::vector<T>& o_value) {
    o_value.clear();
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomRead SIZE in: {}", l_size);
    if (l_size == 0) return;
    o_value.reserve(l_size);
    for (int i = 0; i < l_size; i++) {
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

//unordered_map

template<class K, class V, class W>
inline void readGenericUnorderedMap(InputStream* i_stream, gd::unordered_map<K,V>& o_value) {
    o_value.clear();
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("Unordered Map CustomRead SIZE in: {}", l_size);
    // todo: research if it's worth it to call reserve
    //o_value.reserve(l_size);
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