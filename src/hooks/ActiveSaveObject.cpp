#include "ActiveSaveObject.hpp"
#include <util/debug.hpp>

using namespace geode::prelude;

void PPActiveSaveObject1::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPActiveSaveObject1::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPActiveSaveObject1& o_value) {
    int l_objectIndex;
    i_stream >> l_objectIndex;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool1;
    SEPARATOR_I
    i_stream >> o_value.m_unkBool2;
    SEPARATOR_I_END

    // get the pointer to the gameObject

    PlayLayer* l_playLayer = PlayLayer::get();
    if (l_playLayer) {
        o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
    }
}

inline void operator<<(OutputStream& o_stream, PPActiveSaveObject1& i_value) {
    if (!i_value.m_gameObject) {
        log::info("no game object??");
    }
    int l_objectIndex = i_value.m_gameObject->m_uniqueID-12;
    o_stream << l_objectIndex;
    SEPARATOR_O
    o_stream << i_value.m_unkBool1;
    SEPARATOR_O
    o_stream << i_value.m_unkBool2;
    SEPARATOR_O_END
}

void PPActiveSaveObject2::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPActiveSaveObject2::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPActiveSaveObject2& o_value) {
    int l_objectIndex;
    i_stream >> l_objectIndex;
    SEPARATOR_I
    unsigned int l_easingType;
    i_stream >> l_easingType;
    o_value.m_easingType = static_cast<EasingType>(l_easingType);
    SEPARATOR_I_END

    // get the pointer to the gameObject

    PlayLayer* l_playLayer = PlayLayer::get();
    if (l_playLayer) {
        o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
    }
}

inline void operator<<(OutputStream& o_stream, PPActiveSaveObject2& i_value) {
    if (!i_value.m_gameObject) {
        log::info("no game object??");
    }
    int l_objectIndex = i_value.m_gameObject->m_uniqueID-12;
    o_stream << l_objectIndex;
    SEPARATOR_O
    unsigned int l_easingType = static_cast<unsigned int>(i_value.m_easingType);
    o_stream << l_easingType;
    SEPARATOR_O_END
}