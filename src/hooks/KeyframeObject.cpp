#include "KeyframeObject.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPKeyframeObject::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPKeyframeObject::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPKeyframeObject& o_value) {
	log::info("INSIDE KeyframeObject save");
	i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 32);
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble1;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble2;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble3;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble4;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble5;
	VEC_SEPARATOR_I
	SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_2), 52);
	SEPARATOR_I
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble6;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble7;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble8;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble9;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_unkVecDouble10;
	VEC_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(o_value.pad_3), 132);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPKeyframeObject& i_value) {
	o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 32);
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble1;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble2;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble3;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble4;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble5;
	VEC_SEPARATOR_O
	SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_2), 52);
	SEPARATOR_O
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble6;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble7;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble8;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble9;
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecDouble10;
	VEC_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(i_value.pad_3), 132);
	SEPARATOR_O
}

#ifdef PP_DEBUG
void PPKeyframeObject::describe() {
	log::info("[PPKeyframeObject - describe] pad_1: [{}]", hexStr(pad_1, 32));
	int l_size = m_unkVecDouble1.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble1.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble1[{}]: {}", i, m_unkVecDouble1[i]);
	}
	l_size = m_unkVecDouble2.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble2.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble2[{}]: {}", i, m_unkVecDouble2[i]);
	}
	l_size = m_unkVecDouble3.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble3.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble3[{}]: {}", i, m_unkVecDouble3[i]);
	}
	l_size = m_unkVecDouble4.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble4.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble4[{}]: {}", i, m_unkVecDouble4[i]);
	}
	l_size = m_unkVecDouble5.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble5.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble5[{}]: {}", i, m_unkVecDouble5[i]);
	}
	log::info("[PPKeyframeObject - describe] pad_2: [{}]", hexStr(pad_2, 52));
	l_size = m_unkVecDouble6.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble6.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble6[{}]: {}", i, m_unkVecDouble6[i]);
	}
	l_size = m_unkVecDouble7.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble7.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble7[{}]: {}", i, m_unkVecDouble7[i]);
	}
	l_size = m_unkVecDouble8.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble8.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble8[{}]: {}", i, m_unkVecDouble8[i]);
	}
	l_size = m_unkVecDouble9.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble9.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble9[{}]: {}", i, m_unkVecDouble9[i]);
	}
	l_size = m_unkVecDouble10.size();
	log::info("[PPKeyframeObject - describe] m_unkVecDouble10.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPKeyframeObject - describe] m_unkVecDouble10[{}]: {}", i, m_unkVecDouble10[i]);
	}
	log::info("[PPKeyframeObject - describe] pad_3: [{}]", hexStr(pad_3, 132));
}
#endif