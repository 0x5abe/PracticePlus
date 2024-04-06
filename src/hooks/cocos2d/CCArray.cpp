#include "CCArray.hpp"
#include <hooks/PlayLayer.hpp>
#include <hooks/cocos2d/CCObject.hpp>
#include <hooks/CheckpointObject.hpp>

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

template <typename T>
void PPCCArray::load(InputStream& i_stream) {
    removeAllObjects();
    unsigned int l_size;
    i_stream >> l_size;
    T* l_objects = reinterpret_cast<T*>(malloc(l_size*sizeof(T)));
    geode::log::info("CCARRAY SIZE in: {}", l_size);
    for (int i = 0; i < l_size; i++) {
        reinterpret_cast<T*>(l_objects)->load(i_stream); 
        addObject(l_objects);
        l_objects++;
    }
}

template <typename T>
void PPCCArray::save(OutputStream& o_stream) {
    unsigned int l_size = count();
    o_stream << l_size;
    geode::log::info("CCARRAY SIZE out: {}", l_size);
    for (int i = 0; i < l_size; i++) {
       reinterpret_cast<T*>(objectAtIndex(i))->save(o_stream); 
    }
}

template <>
void PPCCArray::load<GradientTriggerObject>(InputStream& i_stream) {
    removeAllObjects();
    unsigned int l_size;
    i_stream >> l_size;
    geode::log::info("CCARRAY GradientTriggerObject SIZE in: {}", l_size);
    for (int i = 0; i < l_size; i++) {
        int l_objectIndex;
        i_stream >> l_objectIndex;
        addObject(PlayLayer::get()->m_objects->objectAtIndex(l_objectIndex));
    }
}

template <>
void PPCCArray::save<GradientTriggerObject>(OutputStream& o_stream) {
    unsigned int l_size = count();
    o_stream << l_size;
    geode::log::info("CCARRAY GradientTriggerObject SIZE out: {}", l_size);
    for (int i = 0; i < l_size; i++) {
       int l_objectIndex = static_cast<GameObject*>(objectAtIndex(i))->m_uniqueID-12;
       o_stream << l_objectIndex;
    }
}

template void PPCCArray::load<PPCheckpointObject>(InputStream& i_stream);
template void PPCCArray::save<PPCheckpointObject>(OutputStream& o_stream);