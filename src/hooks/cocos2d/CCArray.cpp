#include "CCArray.hpp"
#include <hooks/PlayLayer.hpp>
#include <hooks/cocos2d/CCObject.hpp>

using namespace geode::prelude;

unsigned int PPCCArray::count() {
    unsigned int l_count = CCArray::count();
    PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
    if (l_playLayer && this == l_playLayer->m_checkpointArray) {
        if (l_playLayer->m_fields->m_enableArrayHook &&
            l_playLayer->isPlusMode() &&
            l_playLayer->getActiveStartpointId() != -1
        ) {
            l_count += 1;
        }
    }
    return l_count;
}

CCObject* PPCCArray::lastObject() {
    CCObject* l_lastObject = CCArray::lastObject();
    PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
    if (l_playLayer && this == l_playLayer->m_checkpointArray && !l_lastObject) {
        if (l_playLayer->m_fields->m_enableArrayHook &&
            l_playLayer->isPlusMode() &&
            l_playLayer->getActiveStartpointId() != -1
        ) {
            l_lastObject = static_cast<CCObject*>(l_playLayer->getActiveStartpoint());
        }
    }
    return l_lastObject;
}