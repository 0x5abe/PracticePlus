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

    //custom operators

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

    void write(char* i_value, int i_size) { m_stream->write(i_value, i_size); }
};