#include "GJGameLevel.hpp"
#include <Geode/binding/PlayLayer.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/EventTriggerInstance.hpp>
#include <hooks/PlayLayer.hpp>
#include <hooks/EnterEffectInstance.hpp>
#include <util/debug.hpp>
#include <util/algorithm.hpp>

using namespace geode::prelude;

void PPGJGameLevel::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPGJGameLevel::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGJGameLevel& o_value) {
}

inline void operator<<(OutputStream& o_stream, PPGJGameLevel& i_value) {
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPGJGameLevel::describe() {
	log::info("[PPGJGameLevel - describe] m_levelName: {}", m_levelName);
	log::info("[PPGJGameLevel - describe] m_levelDesc: {}", m_levelDesc);
	//log::info("[PPGJGameLevel - describe] m_levelString: {}", m_levelString);
	log::info("[PPGJGameLevel - describe] m_levelString HASH: {}", util::algorithm::hash_string(m_levelString.c_str()));
	log::info("[PPGJGameLevel - describe] m_creatorName: {}", m_recordString);
	log::info("[PPGJGameLevel - describe] m_uploadDate: {}", m_uploadDate);
	log::info("[PPGJGameLevel - describe] m_updateDate: {}", m_updateDate);
	log::info("[PPGJGameLevel - describe] m_unkString1: {}", m_unkString1);
	log::info("[PPGJGameLevel - describe] m_unkString2: {}", m_unkString2);
	log::info("[PPGJGameLevel - describe] m_levelRev: {}", m_levelRev);
	log::info("[PPGJGameLevel - describe] m_levelIndex: {}", m_levelIndex);
	log::info("[PPGJGameLevel - describe] m_levelVersion: {}", m_levelVersion);
}
#endif