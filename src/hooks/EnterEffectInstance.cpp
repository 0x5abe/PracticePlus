#include "EnterEffectInstance.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>
#include <hooks/PlayLayer.hpp>

using namespace geode::prelude;

void PPEnterEffectInstance::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPEnterEffectInstance::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPEnterEffectInstance& o_value) {
	MAP_SEPARATOR_I
	i_stream >> o_value.m_enterEffectAnimMap;
	MAP_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 140);
	SEPARATOR_I
	int l_objectIndex;
	i_stream >> l_objectIndex;
	PlayLayer* l_playLayer = PlayLayer::get();
	if (l_playLayer && l_objectIndex != -1) {
		o_value.m_gameObject = static_cast<GameObject*>(l_playLayer->m_objects->objectAtIndex(l_objectIndex));
	} else {
		o_value.m_gameObject = nullptr;
	}
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 28);
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecInt;
	VEC_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_3), 4);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPEnterEffectInstance& i_value) {
	MAP_SEPARATOR_O
	o_stream << i_value.m_enterEffectAnimMap;
	MAP_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 140);
	SEPARATOR_O
	int l_objectIndex = -1;
	if (i_value.m_gameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = i_value.m_gameObject->m_uniqueID-(l_playLayer->getUniqueIdBase());
	}
	o_stream << l_objectIndex;
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 28);
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecInt;
	VEC_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_3), 4);
	SEPARATOR_O
}

#ifdef PP_DEBUG
void PPEnterEffectInstance::describe() {
	int i = 0;
	for (std::pair<int, EnterEffectAnimValue> l_pair : m_enterEffectAnimMap) {
		log::info("[PPEnterEffectInstance - describe] m_enterEffectAnimMap element {} key: {}", i, l_pair.first);
		log::info("[PPEnterEffectInstance - describe] m_enterEffectAnimMap element {} value: [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 32));
		i++;
	}
	log::info("[PPEnterEffectInstance - describe] pad_1: [{}]", hexStr(pad_1, 140));
	int l_objectIndex = -1;
	if (m_gameObject) {
		PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
		if (l_playLayer) l_objectIndex = m_gameObject->m_uniqueID-(l_playLayer->getUniqueIdBase());
	}
	log::info("[PPEnterEffectInstance - describe] m_gameObject l_objectIndex: {}", l_objectIndex);
	log::info("[PPEnterEffectInstance - describe] pad_2: [{}]", hexStr(pad_2, 28));
	int l_size = m_unkVecInt.size();
	log::info("[PPEnterEffectInstance - describe] m_unkVecInt.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPEnterEffectInstance - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
	}
	log::info("[PPEnterEffectInstance - describe] pad_3: [{}]", hexStr(pad_3, 4));
}
#endif