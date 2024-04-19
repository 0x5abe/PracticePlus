#include "ToggleTriggerAction.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPToggleTriggerAction::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPToggleTriggerAction::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPToggleTriggerAction& o_value) {
	i_stream.read(reinterpret_cast<char*>(&o_value), 20);
	VEC_SEPARATOR_I
	int l_size = o_value.m_unkVecInt.size();
	i_stream >> o_value.m_unkVecInt;
	VEC_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPToggleTriggerAction& i_value) {
	o_stream.write(reinterpret_cast<char*>(&i_value), 20);
	VEC_SEPARATOR_O
	o_stream << i_value.m_unkVecInt;
	VEC_SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPToggleTriggerAction::describe() {
	log::info("[PPToggleTriggerAction - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this), 20));
	int l_size = m_unkVecInt.size();
	log::info("[PPToggleTriggerAction - describe] m_unkVecInt.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPToggleTriggerAction - describe] m_unkVecInt[{}]: {}", i, m_unkVecInt[i]);
	}
}
#endif