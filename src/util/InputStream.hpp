#pragma once
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Log.hpp>

#define PP_OPERATOR_READ(type) virtual void operator>>(type& o_value) { m_stream->read(reinterpret_cast<char*>(&o_value), sizeof(type)); }
class InputStream {
protected:
    std::istream* m_stream;
public:
    InputStream(std::string i_filePath) { m_stream = new std::ifstream(i_filePath); }
    ~InputStream() { delete m_stream; }

    PP_OPERATOR_READ(bool)
    PP_OPERATOR_READ(char)
    PP_OPERATOR_READ(unsigned char)
    PP_OPERATOR_READ(int)
    PP_OPERATOR_READ(unsigned int)
    PP_OPERATOR_READ(short)
    PP_OPERATOR_READ(unsigned short)
    PP_OPERATOR_READ(float)
    PP_OPERATOR_READ(double)
    PP_OPERATOR_READ(cocos2d::CCPoint)
    PP_OPERATOR_READ(cocos2d::CCSize)
    PP_OPERATOR_READ(cocos2d::CCAffineTransform)

    //custom operators

    //vector

    template <class T>
    void operator>>(std::vector<T>& o_value) {
        o_value.clear();
        unsigned int l_size;
        m_stream->read(reinterpret_cast<char*>(&l_size), 4);
        geode::log::info("VECTOR SIZE in: {}", l_size);
        o_value.reserve(l_size);
        m_stream->read(reinterpret_cast<char*>(o_value.data()), l_size*sizeof(T));
    }

    template <>
    void operator>><DynamicSaveObject>(std::vector<DynamicSaveObject>& o_value);

    template <>
    void operator>><ActiveSaveObject1>(std::vector<ActiveSaveObject1>& o_value);

    template <>
    void operator>><ActiveSaveObject2>(std::vector<ActiveSaveObject2>& o_value);

    //unordered_map

    template <class K, class V>
    void operator>>(gd::unordered_map<K,V>& o_value) {
        o_value.clear();
        unsigned int l_size;
        m_stream->read(reinterpret_cast<char*>(&l_size), 4);
        geode::log::info("Unordered Map SIZE in: {}", l_size);
        // todo: research if it's worth it to call reserve
        //o_value.reserve(l_size);
        for (int i = 0; i < l_size; i++) {
            K l_key;
            V l_value;
            m_stream->read(reinterpret_cast<char*>(&l_key), sizeof(K));
            m_stream->read(reinterpret_cast<char*>(&l_value), sizeof(V));
            o_value[l_key] = l_value;
        }
    }

    template <>
    void operator>><int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& o_value);

    void read(char* o_value, int i_size) { m_stream->read(o_value, i_size); }
    void ignore(int i_size) { m_stream->ignore(i_size); }
};