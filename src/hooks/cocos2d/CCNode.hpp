#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>


class $modify(PPCCNode, cocos2d::CCNode) {
protected:
    friend void operator>>(InputStream& i_stream, PPCCNode& o_value);
    friend void operator<<(OutputStream& o_stream, PPCCNode& i_value);

public:
    void load(InputStream& i_stream);
    void save(OutputStream& o_stream);
};