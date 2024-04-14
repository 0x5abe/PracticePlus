#include "GroupCommandObject2.hpp"
#include <Geode/binding/KeyframeObject.hpp>
#include <hooks/KeyframeObject.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPGroupCommandObject2::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPGroupCommandObject2::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGroupCommandObject2& o_value) {
	i_stream.read(reinterpret_cast<char*>(&o_value), 436);
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecKeyframeObject;
	VEC_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPGroupCommandObject2,m_unkVecKeyframeObject) + sizeof(gd::vector<KeyframeObject>), 16);
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecInt;
	VEC_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPGroupCommandObject2,m_unkVecInt) + sizeof(gd::vector<int>), 12);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPGroupCommandObject2& i_value) {
	o_stream.write(reinterpret_cast<char*>(&i_value), 436);
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecKeyframeObject;
	VEC_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPGroupCommandObject2,m_unkVecKeyframeObject) + sizeof(gd::vector<KeyframeObject>), 16);
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecInt;
	VEC_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPGroupCommandObject2,m_unkVecInt) + sizeof(gd::vector<int>), 12);
	SEPARATOR_O
}

#ifdef PP_DEBUG
void PPGroupCommandObject2::describe() {
	log::info("[PPGroupCommandObject2 - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this), 436));
	int l_size = m_unkVecKeyframeObject.size();
	log::info("[PPGroupCommandObject2 - describe] m_unkVecKeyframeObject.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPGroupCommandObject2 - describe] m_unkVecKeyframeObject[{}]:", i);
		reinterpret_cast<PPKeyframeObject*>(&m_unkVecKeyframeObject[i])->describe();
	}
	log::info("[PPGroupCommandObject2 - describe] pad_2: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPGroupCommandObject2,m_unkVecKeyframeObject) + sizeof(gd::vector<KeyframeObject>), 16));
	l_size = m_unkVecInt.size();
	log::info("[PPGroupCommandObject2 - describe] m_unkVecInt.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
	}
	log::info("[PPGroupCommandObject2 - describe] pad_3: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPGroupCommandObject2,m_unkVecInt) + sizeof(gd::vector<int>), 12));
}
#endif