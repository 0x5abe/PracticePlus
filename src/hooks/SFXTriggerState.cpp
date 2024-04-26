#include "SFXTriggerState.hpp"
#include <Geode/binding/SFXTriggerGameObject.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayLayer.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPSFXTriggerState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPSFXTriggerState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPSFXTriggerState& o_value) {
	int l_objectIndex;
	i_stream >> l_objectIndex;
	PlayLayer* l_playLayer = PlayLayer::get();
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_sfxTriggerGameObject = static_cast<SFXTriggerGameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_sfxTriggerGameObject = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPSFXTriggerState,m_sfxTriggerGameObject) + sizeof(SFXTriggerGameObject*), 156);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPSFXTriggerState& i_value) {
	int l_objectIndex = -1;
	if (i_value.m_sfxTriggerGameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(i_value.m_sfxTriggerGameObject);
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPSFXTriggerState,m_sfxTriggerGameObject) + sizeof(SFXTriggerGameObject*), 156);
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPSFXTriggerState::describe() {
	int l_objectIndex = -1;
	if (m_sfxTriggerGameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(m_sfxTriggerGameObject);
	}
	log::info("[PPSFXTriggerState - describe] m_sfxTriggerGameObject l_objectIndex: {}", l_objectIndex);
	log::info("[PPSFXTriggerState - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPSFXTriggerState,m_sfxTriggerGameObject) + sizeof(SFXTriggerGameObject*), 156));
}
#endif