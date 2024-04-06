
#include "InputStream.hpp"
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>

template<class T, class V>
inline void readGenericVector(InputStream* i_stream, std::vector<T>& o_value) {
    o_value.clear();
    unsigned int l_size;
    i_stream->read(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomRead in: {}", l_size);
    if (l_size == 0) return;
    o_value.reserve(l_size);
    for (int i = 0; i < l_size; i++) {
        reinterpret_cast<V&>(o_value[i]).load(*i_stream); 
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