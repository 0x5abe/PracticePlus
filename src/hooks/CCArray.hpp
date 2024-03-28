#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCArray.hpp>

class $modify(PracticePlusCCArray, cocos2d::CCArray) {
public:
    $override
    unsigned int count();

    $override
    CCObject* lastObject();
};