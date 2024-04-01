#include "CCArray.hpp"
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

unsigned int PracticePlusCCArray::count() {
    unsigned int l_count = CCArray::count();
    PracticePlusPlayLayer* l_playLayer = static_cast<PracticePlusPlayLayer*>(PlayLayer::get());
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

CCObject* PracticePlusCCArray::lastObject() {
    CCObject* l_lastObject = CCArray::lastObject();
    PracticePlusPlayLayer* l_playLayer = static_cast<PracticePlusPlayLayer*>(PlayLayer::get());
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