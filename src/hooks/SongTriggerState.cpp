#include "SongTriggerState.hpp"
#include <Geode/binding/SongTriggerGameObject.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayLayer.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPSongTriggerState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPSongTriggerState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPSongTriggerState& o_value) {
	int l_objectIndex;
	i_stream >> l_objectIndex;
	PlayLayer* l_playLayer = PlayLayer::get();
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_songTriggerGameObject = static_cast<SongTriggerGameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_songTriggerGameObject = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPSongTriggerState,m_songTriggerGameObject) + sizeof(SongTriggerGameObject*), 8);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPSongTriggerState& i_value) {
	int l_objectIndex = -1;
	if (i_value.m_songTriggerGameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(i_value.m_songTriggerGameObject);
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPSongTriggerState,m_songTriggerGameObject) + sizeof(SongTriggerGameObject*), 8);
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPSongTriggerState::describe() {
	int l_objectIndex = -1;
	if (m_songTriggerGameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(m_songTriggerGameObject);
	}
	log::info("[PPSongTriggerState - describe] m_songTriggerGameObject l_objectIndex: {}", l_objectIndex);
	log::info("[PPSongTriggerState - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPSongTriggerState,m_songTriggerGameObject) + sizeof(SongTriggerGameObject*), 8));
}
#endif