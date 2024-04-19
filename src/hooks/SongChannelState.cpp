#include "SongChannelState.hpp"
#include "Geode/binding/SongTriggerGameObject.hpp"
#include <Geode/binding/PlayLayer.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayLayer.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPSongChannelState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPSongChannelState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPSongChannelState& o_value) {
	i_stream.read(reinterpret_cast<char*>(&o_value), 4);
	SEPARATOR_I
	int l_objectIndex;
	i_stream >> l_objectIndex;
	PlayLayer* l_playLayer = PlayLayer::get();
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_songTriggerGameObject1 = static_cast<SongTriggerGameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_songTriggerGameObject1 = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPSongChannelState,m_songTriggerGameObject1) + sizeof(SongTriggerGameObject*), 12);
	SEPARATOR_I
	i_stream >> l_objectIndex;
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_songTriggerGameObject2 = static_cast<SongTriggerGameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_songTriggerGameObject2 = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPSongChannelState,m_songTriggerGameObject2) + sizeof(SongTriggerGameObject*), 12);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPSongChannelState& i_value) {
	o_stream.write(reinterpret_cast<char*>(&i_value), 4);
	SEPARATOR_O
	int l_objectIndex = -1;
	if (i_value.m_songTriggerGameObject1) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(i_value.m_songTriggerGameObject1);
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPSongChannelState,m_songTriggerGameObject1) + sizeof(SongTriggerGameObject*), 12);
	SEPARATOR_O
	l_objectIndex = -1;
	if (i_value.m_songTriggerGameObject2) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(i_value.m_songTriggerGameObject2);
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPSongChannelState,m_songTriggerGameObject2) + sizeof(SongTriggerGameObject*), 12);
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPSongChannelState::describe() {
	log::info("[PPSongChannelState - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this), 4));
	int l_objectIndex = -1;
	if (m_songTriggerGameObject1) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(m_songTriggerGameObject1);
	}
	log::info("[PPSongChannelState - describe] m_songTriggerGameObject1 l_objectIndex: {}", l_objectIndex);
	log::info("[PPSongChannelState - describe] pad_2: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPSongChannelState,m_songTriggerGameObject1) + sizeof(SongTriggerGameObject*), 12));
	l_objectIndex = -1;
	if (m_songTriggerGameObject2) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(m_songTriggerGameObject2);
	}
	log::info("[PPSongChannelState - describe] m_songTriggerGameObject2 l_objectIndex: {}", l_objectIndex);
	log::info("[PPSongChannelState - describe] pad_3: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPSongChannelState,m_songTriggerGameObject2) + sizeof(SongTriggerGameObject*), 12));
}
#endif