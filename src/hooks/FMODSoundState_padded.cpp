#include "FMODSoundState_padded.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPFMODSoundState_padded::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPFMODSoundState_padded::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPFMODSoundState_padded& o_value) {
	i_stream.read(reinterpret_cast<char*>(&o_value), 4);
	SEPARATOR_I
	STR_SEPARATOR_I
	i_stream >> o_value.m_unkString;
	STR_SEPARATOR_I
	i_stream.read(reinterpret_cast<char*>(&o_value) + offsetof(PPFMODSoundState_padded,m_unkString) + sizeof(gd::string), 164);
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPFMODSoundState_padded& i_value) {
	o_stream.write(reinterpret_cast<char*>(&i_value), 4);
	//log::info("INSIDE WRITE SoundState");
	SEPARATOR_O
	STR_SEPARATOR_O
	o_stream << i_value.m_unkString;
	STR_SEPARATOR_O
	o_stream.write(reinterpret_cast<char*>(&i_value) + offsetof(PPFMODSoundState_padded,m_unkString) + sizeof(gd::string), 164);
	SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPFMODSoundState_padded::describe() {
	log::info("[PPFMODSoundState_padded - describe] pad_1: [{}]", hexStr(reinterpret_cast<unsigned char*>(this), 4));
	log::info("[PPFMODSoundState_padded - describe] m_unkString: {}", m_unkString);
	log::info("[PPFMODSoundState_padded - describe] pad_2: [{}]", hexStr(reinterpret_cast<unsigned char*>(this) + offsetof(PPFMODSoundState_padded,m_unkString) + sizeof(gd::string), 164));
}
#endif