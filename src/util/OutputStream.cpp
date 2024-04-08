
#include "OutputStream.hpp"
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>
#include <hooks/SequenceTriggerState.hpp>
#include <hooks/FMODQueuedMusic.hpp>
#include <hooks/FMODSoundState_padded.hpp>

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