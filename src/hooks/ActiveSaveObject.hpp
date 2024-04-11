#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/ActiveSaveObject1.hpp>
#include <Geode/modify/ActiveSaveObject2.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>


class $modify(PPActiveSaveObject1, ActiveSaveObject1) {
public:
    friend void operator>>(InputStream& i_stream, PPActiveSaveObject1& o_value);
    friend void operator<<(OutputStream& o_stream, PPActiveSaveObject1& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};

class $modify(PPActiveSaveObject2, ActiveSaveObject2) {
public:
    friend void operator>>(InputStream& i_stream, PPActiveSaveObject2& o_value);
    friend void operator<<(OutputStream& o_stream, PPActiveSaveObject2& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);

#ifdef PP_DEBUG
    void describe();
#endif
};