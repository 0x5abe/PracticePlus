#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCArray.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCCArray, cocos2d::CCArray) {
public:
    $override
    unsigned int count();

    $override
    CCObject* lastObject();

    template <typename T>
    void load(InputStream& i_stream);

    template <typename T>
    void save(OutputStream& o_stream);

    template <>
    void load<GradientTriggerObject>(InputStream& i_stream);

    template <>
    void save<GradientTriggerObject>(OutputStream& o_stream);
};