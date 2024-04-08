
#include "OutputStream.hpp"
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
inline void writeGenericVector(OutputStream* o_stream, std::vector<T>& i_value) {
    unsigned int l_size = i_value.size();
    o_stream->write(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomWrite SIZE out: {}", l_size);
    if (l_size == 0) return;
    for (int i = 0; i < l_size; i++) {
        reinterpret_cast<U&>(i_value[i]).save(*o_stream); 
    }
}

template <>
void OutputStream::operator<<<DynamicSaveObject>(std::vector<DynamicSaveObject>& i_value) {
    writeGenericVector<DynamicSaveObject, PPDynamicSaveObject>(this, i_value);
}

template <>
void OutputStream::operator<<<ActiveSaveObject1>(std::vector<ActiveSaveObject1>& i_value) {
    writeGenericVector<ActiveSaveObject1, PPActiveSaveObject1>(this, i_value);
}

template <>
void OutputStream::operator<<<ActiveSaveObject2>(std::vector<ActiveSaveObject2>& i_value) {
    writeGenericVector<ActiveSaveObject2, PPActiveSaveObject2>(this, i_value);
}

template <>
void OutputStream::operator<<<CountTriggerAction>(std::vector<CountTriggerAction>& i_value) {
    geode::log::info("1111111111111111111 VECTOR CustomWrite CountTriggerAction");
    writeGenericVector<CountTriggerAction, PPCountTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<TouchToggleAction>(std::vector<TouchToggleAction>& i_value) {
    geode::log::info("22222222222222222222 VECTOR CustomWrite TouchToggleAction");
    writeGenericVector<TouchToggleAction, PPTouchToggleAction>(this, i_value);
}

template <>
void OutputStream::operator<<<CollisionTriggerAction>(std::vector<CollisionTriggerAction>& i_value) {
    geode::log::info("33333333333333333333 VECTOR CustomWrite CollisionTriggerAction");
    writeGenericVector<CollisionTriggerAction, PPCollisionTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<ToggleTriggerAction>(std::vector<ToggleTriggerAction>& i_value) {
    geode::log::info("4444444444444444444 VECTOR CustomWrite ToggleTriggerAction");
    writeGenericVector<ToggleTriggerAction, PPToggleTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<SpawnTriggerAction>(std::vector<SpawnTriggerAction>& i_value) {
    geode::log::info("55555555555555555555 VECTOR CustomWrite SpawnTriggerAction");
    writeGenericVector<SpawnTriggerAction, PPSpawnTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<GroupCommandObject2>(std::vector<GroupCommandObject2>& i_value) {
    geode::log::info("666666666666666666666 VECTOR CustomWrite GroupCommandObject2");
    writeGenericVector<GroupCommandObject2, PPGroupCommandObject2>(this, i_value);
}

template <>
void OutputStream::operator<<<KeyframeObject>(std::vector<KeyframeObject>& i_value) {
    geode::log::info("777777777777777777 VECTOR CustomWrite KeyframeObject");
    writeGenericVector<KeyframeObject, PPKeyframeObject>(this, i_value);
}

template <>
void OutputStream::operator<<<TimerTriggerAction>(std::vector<TimerTriggerAction>& i_value) {
    geode::log::info("8888888888888888888 VECTOR CustomWrite TimerTriggerAction");
    writeGenericVector<TimerTriggerAction, PPTimerTriggerAction>(this, i_value);
}

//unordered_map

template<class K, class V, class W>
inline void writeGenericUnorderedMap(OutputStream* o_stream, gd::unordered_map<K,V>& i_value) {
    unsigned int l_size = i_value.size();
    o_stream->write(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("Unordered Map CustomWrite SIZE out: {}", l_size);
    if (l_size == 0) return;
    for (std::pair<K,V> l_pair : i_value) {
        o_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
        reinterpret_cast<W&>(l_pair.second).save(*o_stream);
    }
}

template <>
void OutputStream::operator<<<int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& i_value) {
    writeGenericUnorderedMap<int, SequenceTriggerState, PPSequenceTriggerState>(this, i_value);
}

template <>
void OutputStream::operator<<<int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& i_value) {
    writeGenericUnorderedMap<int, FMODQueuedMusic, PPFMODQueuedMusic>(this, i_value);
}

template <>
void OutputStream::operator<<<int, FMODSoundState_padded>(gd::unordered_map<int, FMODSoundState_padded>& i_value) {
    writeGenericUnorderedMap<int, FMODSoundState_padded, PPFMODSoundState_padded>(this, i_value);
}

template <>
void OutputStream::operator<<<int, TimerItem_padded>(gd::unordered_map<int, TimerItem_padded>& i_value) {
    geode::log::info("999999999999999999999 Unordered Map CustomWrite TimerItem_padded");
    writeGenericUnorderedMap<int, TimerItem_padded, PPTimerItem_padded>(this, i_value);
}