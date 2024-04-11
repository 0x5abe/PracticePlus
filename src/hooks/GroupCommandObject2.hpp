#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GroupCommandObject2.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPGroupCommandObject2, GroupCommandObject2) {
protected:
    friend void operator>>(InputStream& i_stream, PPGroupCommandObject2& o_value);
    friend void operator<<(OutputStream& o_stream, PPGroupCommandObject2& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
    
#ifdef PP_DEBUG
    void describe();
#endif
};