
#include "InputStream.hpp"
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>
#include <hooks/SequenceTriggerState.hpp>

//vector

template<class T, class U>
inline void readGenericVector(InputStream* i_stream, std::vector<T>& o_value) {
    o_value.clear();
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomRead in: {}", l_size);
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

//unordered_map

//TODO: fix broken
// template<class K, class V, class W>
// inline void readGenericUnorderedMap(InputStream* i_stream, gd::unordered_map<K,V>& o_value) {
//     o_value.clear();
//     unsigned int l_size;
//     i_stream->read(reinterpret_cast<char*>(&l_size), 4);
//     geode::log::info("Unordered Map CustomRead SIZE in: {}", l_size);
//     // todo: research if it's worth it to call reserve
//     //o_value.reserve(l_size);
//     for (int i = 0; i < l_size; i++) {
//         K l_key;
//         V l_value;
//         i_stream->read(reinterpret_cast<char*>(&l_key), sizeof(K));
//         reinterpret_cast<W&>(l_value).load(*i_stream); 
//         o_value.insert({l_key,l_value});
//     }
// }

// template <>
// void InputStream::operator>><int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& o_value) {
//     readGenericUnorderedMap<int, SequenceTriggerState, PPSequenceTriggerState>(this, o_value);
// }