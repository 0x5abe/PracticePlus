#include "DynamicSaveObject.hpp"
#include <hooks/PlayLayer.hpp>
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
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_gameObject = nullptr;
	}
}

inline void operator<<(OutputStream& o_stream, PPDynamicSaveObject& i_value) {
	int l_objectIndex = -1;
	if (!i_value.m_gameObject) {
		//log::info("no game object??");
	} else {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(i_value.m_gameObject);
	}
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

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPDynamicSaveObject::describe() {
	int l_objectIndex = -1;
	if (!m_gameObject) {
		log::info("[PPDynamicSaveObject - describe] no game object?? @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	} else {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(m_gameObject);
	}
	
	log::info("[PPDynamicSaveObject - describe] l_objectIndex: {}", l_objectIndex);
	log::info("[PPDynamicSaveObject - describe] m_unkIntUnusedMaybe: {}", m_unkIntUnusedMaybe);
	log::info("[PPDynamicSaveObject - describe] m_unkDouble1: {}", m_unkDouble1);
	log::info("[PPDynamicSaveObject - describe] m_unkDouble2: {}", m_unkDouble2);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat1: {}", m_unkFloat1);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat2: {}", m_unkFloat2);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat3: {}", m_unkFloat3);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat4: {}", m_unkFloat4);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat5: {}", m_unkFloat5);
	log::info("[PPDynamicSaveObject - describe] m_unkFloat6: {}", m_unkFloat6);
}
#endif