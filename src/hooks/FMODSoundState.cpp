#include "FMODSoundState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPFMODSoundState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPFMODSoundState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPFMODSoundState& o_value) {
	STR_SEPARATOR_I
	i_stream >> o_value.m_unkString;
	STR_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPFMODSoundState,m_unkString) + sizeof(gd::string), 164);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPFMODSoundState& i_value) {
	STR_SEPARATOR_O
	o_stream << i_value.m_unkString;
	STR_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPFMODSoundState,m_unkString) + sizeof(gd::string), 164);
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPFMODSoundState::describe() {
	log::info("[PPFMODSoundState - describe] m_unkString: {}", m_unkString);
	log::info("[PPFMODSoundState - describe] pad_2: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPFMODSoundState,m_unkString) + sizeof(gd::string), 164));
}
#endif