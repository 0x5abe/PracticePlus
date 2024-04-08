#pragma once
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Log.hpp>

#define PP_OPERATOR_WRITE(type) virtual void operator<<(type& i_value) { m_stream->write(reinterpret_cast<char*>(&i_value), sizeof(type)); }

class OutputStream {
protected:
    std::ostream* m_stream;
public:
    OutputStream(std::string i_filePath) { m_stream = new std::ofstream(i_filePath, std::ios_base::binary); }
    ~OutputStream() { delete m_stream; }
    
    PP_OPERATOR_WRITE(bool)
    PP_OPERATOR_WRITE(char)
    PP_OPERATOR_WRITE(unsigned char)
    PP_OPERATOR_WRITE(int)
    PP_OPERATOR_WRITE(unsigned int)
    PP_OPERATOR_WRITE(short)
    PP_OPERATOR_WRITE(unsigned short)
    PP_OPERATOR_WRITE(float)
    PP_OPERATOR_WRITE(double)
    PP_OPERATOR_WRITE(cocos2d::CCPoint)
    PP_OPERATOR_WRITE(cocos2d::CCSize)
    PP_OPERATOR_WRITE(cocos2d::CCAffineTransform)

    void write(char* i_value, int i_size) { m_stream->write(i_value, i_size); }

    //custom operators

    //vector

    template <class T>
    void operator<<(std::vector<T>& i_value) {
        unsigned int l_size = i_value.size();
        geode::log::info("VECTOR SIZE out: {}", l_size);
        m_stream->write(reinterpret_cast<char*>(&l_size), 4);
        m_stream->write(reinterpret_cast<char*>(i_value.data()), l_size*sizeof(T));
    }

    template <>
    void operator<<<DynamicSaveObject>(std::vector<DynamicSaveObject>& i_value);

    template <>
    void operator<<<ActiveSaveObject1>(std::vector<ActiveSaveObject1>& i_value);

    template <>
    void operator<<<ActiveSaveObject2>(std::vector<ActiveSaveObject2>& i_value);

    //unordered_map

    template <class K, class V>
    void operator<<(gd::unordered_map<K,V>& i_value) {
        unsigned int l_size = i_value.size();
        geode::log::info("Unordered Map SIZE out: {}", l_size);
        m_stream->write(reinterpret_cast<char*>(&l_size), 4);
        for (std::pair<K,V> l_pair : i_value) {
            m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
            m_stream->write(reinterpret_cast<char*>(&l_pair.second), sizeof(V));
        }
    }

    template <>
    void operator<<<int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& i_value);

    template <>
    void operator<<<int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& i_value);

    template <>
    void operator<<<int, FMODSoundState_padded>(gd::unordered_map<int, FMODSoundState_padded>& i_value);

    //map

    template <class K, class V>
    void operator<<(gd::map<K,V>& i_value) {
        unsigned int l_size = i_value.size();
        geode::log::info("Map SIZE out: {}", l_size);
        m_stream->write(reinterpret_cast<char*>(&l_size), 4);
        for (std::pair<K,V> l_pair : i_value) {
            m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
            m_stream->write(reinterpret_cast<char*>(&l_pair.second), sizeof(V));
        }
    }

    //gd::string

    void operator<<(gd::string& i_value) {
        unsigned int l_size = i_value.size();
        m_stream->write(reinterpret_cast<char*>(&l_size), 4);
        geode::log::info("String SIZE in: {}", l_size);
        if (l_size == 0) return;
        m_stream->write(i_value.data(), l_size);
    }
};