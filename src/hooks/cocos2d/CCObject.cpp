#include "CCObject.hpp"
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCCObject::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPCCObject::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCCObject& o_value) {
	i_stream >> (int&)(o_value.m_eObjType);
	SEPARATOR_I
	i_stream >> o_value.m_nZOrder;
	SEPARATOR_I
	i_stream >> o_value.m_uOrderOfArrival;
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPCCObject& i_value) {
	o_stream << (int&)(i_value.m_eObjType);
	SEPARATOR_O
	o_stream << i_value.m_nZOrder;
	SEPARATOR_O
	o_stream << i_value.m_uOrderOfArrival;
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPCCObject::describe() {
	log::info("[PPCCObject - describe] m_eObjType: {}", static_cast<int>(m_eObjType));
	log::info("[PPCCObject - describe] m_nZOrder: {}", m_nZOrder);
	log::info("[PPCCObject - describe] m_uOrderOfArrival: {}", m_uOrderOfArrival);
}
#endif