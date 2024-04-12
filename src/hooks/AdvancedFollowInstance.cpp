#include "AdvancedFollowInstance.hpp"
#include "Geode/binding/PlayLayer.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPAdvancedFollowInstance::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPAdvancedFollowInstance::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPAdvancedFollowInstance& o_value) {
	int l_objectIndex;
	i_stream >> l_objectIndex;
	PlayLayer* l_playLayer = PlayLayer::get();
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_gameObject = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 24);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPAdvancedFollowInstance& i_value) {
	int l_objectIndex = -1;
	if (i_value.m_gameObject) {
		l_objectIndex = i_value.m_gameObject->m_uniqueID-12;
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 24);
	SEPARATOR_O
}

#ifdef PP_DEBUG
void PPAdvancedFollowInstance::describe() {
	log::info("[PPAdvancedFollowInstance - describe] pad_1: [{}]", hexStr(pad_1, 24));
	int l_objectIndex = -1;
	if (m_gameObject) {
		l_objectIndex = m_gameObject->m_uniqueID-12;
	}
	log::info("[PPAdvancedFollowInstance - describe] m_gameObject l_objectIndex: {}", l_objectIndex);
}
#endif