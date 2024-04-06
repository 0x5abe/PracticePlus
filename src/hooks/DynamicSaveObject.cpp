#include "DynamicSaveObject.hpp"
#include <util/debug.hpp>

using namespace geode::prelude;

void PPDynamicSaveObject::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPDynamicSaveObject::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPDynamicSaveObject& o_value) {
    int l_objectIndex;
    i_stream >> l_objectIndex;
    SEPARATOR_I
    i_stream >> o_value.m_unkIntUnusedMaybe;
    SEPARATOR_I
    i_stream >> o_value.m_unkDouble1;
    SEPARATOR_I
    i_stream >> o_value.m_unkDouble2;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat1;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat2;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat3;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat4;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat5;
    SEPARATOR_I
    i_stream >> o_value.m_unkFloat6;
    SEPARATOR_I_END

    // get the pointer to the gameObject

    PlayLayer* l_playLayer = PlayLayer::get();
    if (l_playLayer) {
        o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
    }
}

inline void operator<<(OutputStream& o_stream, PPDynamicSaveObject& i_value) {
    if (!i_value.m_gameObject) {
        log::info("no game object??");
    }
    int l_objectIndex = i_value.m_gameObject->m_uniqueID-12;
    o_stream << l_objectIndex;
    SEPARATOR_O
    o_stream << i_value.m_unkIntUnusedMaybe;
    SEPARATOR_O
    o_stream << i_value.m_unkDouble1;
    SEPARATOR_O
    o_stream << i_value.m_unkDouble2;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat1;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat2;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat3;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat4;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat5;
    SEPARATOR_O
    o_stream << i_value.m_unkFloat6;
    SEPARATOR_O_END
}