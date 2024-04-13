#include "GJShaderState.hpp"
#include "Geode/binding/GJValueTween.hpp"
#include <cstdint>
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPGJShaderState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPGJShaderState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGJShaderState& o_value) {
	UMAP_SEPARATOR_I
	i_stream >> o_value.m_someIntToValueTweenMap;
	UMAP_SEPARATOR_I
	i_stream >> o_value.m_someIntToDoubleMap;
	UMAP_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPGJShaderState,m_someIntToDoubleMap) + sizeof(gd::unordered_map<int, double>), 584);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPGJShaderState& i_value) {
	UMAP_SEPARATOR_O
	o_stream << i_value.m_someIntToValueTweenMap;
	UMAP_SEPARATOR_O
	o_stream << i_value.m_someIntToDoubleMap;
	UMAP_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPGJShaderState,m_someIntToDoubleMap) + sizeof(gd::unordered_map<int, double>), 584);
	SEPARATOR_O
}

#ifdef PP_DEBUG
void PPGJShaderState::describe() {
	int l_size = m_someIntToValueTweenMap.size();
	log::info("[PPGJShaderState - describe] m_someIntToValueTweenMap.size(): {}", l_size);
	int i = 0;
	for (std::pair<int,GJValueTween> l_pair : m_someIntToValueTweenMap) {
		log::info("[PPGJShaderState - describe] m_someIntToValueTweenMap element {} key: {}", i, l_pair.first);
		log::info("[PPGJShaderState - describe] m_someIntToValueTweenMap element {} value (GJValueTween): [{}]", i, hexStr(reinterpret_cast<uint8_t*>(&l_pair.second), 40));
		i++;
	}
	l_size = m_someIntToDoubleMap.size();
	log::info("[PPGJShaderState - describe] m_someIntToDoubleMap.size(): {}", l_size);
	for (std::pair<int,double> l_pair : m_someIntToDoubleMap) {
		log::info("[PPGJShaderState - describe] m_someIntToDoubleMap element {} key: {}", i, l_pair.first);
		log::info("[PPGJShaderState - describe] m_someIntToDoubleMap element {} value: [{}]", i, l_pair.second);
		i++;
	}
	log::info("[PPGJShaderState - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPGJShaderState,m_someIntToDoubleMap) + sizeof(gd::unordered_map<int, double>), 584));
}
#endif