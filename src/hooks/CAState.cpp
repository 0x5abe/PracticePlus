#include "CAState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCAState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPCAState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCAState& o_value) {
	i_stream.read(reinterpret_cast<char*>(&o_value), 68);
	SEPARATOR_I;
}

inline void operator<<(OutputStream& o_stream, PPCAState& i_value) {
	o_stream.write(reinterpret_cast<char*>(&i_value), 68);
	SEPARATOR_O;
}

#ifdef PP_DEBUG
void PPCAState::describe() {
}
#endif