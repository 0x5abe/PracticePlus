
#include "OutputStream.hpp"
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>

template<class T, class U>
inline void writeGenericVector(OutputStream* o_stream, std::vector<T>& i_value) {
    unsigned int l_size = i_value.size();
    o_stream->write(reinterpret_cast<char*>(&l_size), 4);
    geode::log::info("VECTOR SIZE CustomWrite out: {}", l_size);
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