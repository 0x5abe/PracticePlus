#include "SequenceTriggerState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPSequenceTriggerState::load(InputStream& i_stream) {
	i_stream >> *this;
}

void PPSequenceTriggerState::save(OutputStream& o_stream) {
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPSequenceTriggerState& o_value) {
	UMAP_SEPARATOR_I
	i_stream >> o_value.m_unkUnorderedMap1;
	UMAP_SEPARATOR_I
	i_stream >> o_value.m_unkUnorderedMap2;
	UMAP_SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPSequenceTriggerState& i_value) {
	UMAP_SEPARATOR_O
	o_stream << i_value.m_unkUnorderedMap1;
	UMAP_SEPARATOR_O
	o_stream << i_value.m_unkUnorderedMap2;
	UMAP_SEPARATOR_O
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPSequenceTriggerState::describe() {
	int l_size = m_unkUnorderedMap1.size();
	log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap1.size(): {}", l_size);
	int i = 0;
	for (std::pair<int,float> l_pair : m_unkUnorderedMap1) {
		log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap1 element {} key: {}", i, l_pair.first);
		log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap1 element {} value: {}", i, l_pair.second);
		i++;
	}
	l_size = m_unkUnorderedMap2.size();
	log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap2.size(): {}", l_size);
	i = 0;
	for (std::pair<int,int> l_pair : m_unkUnorderedMap2) {
		log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap2 element {} key: {}", i, l_pair.first);
		log::info("[PPSequenceTriggerState - describe] m_unkUnorderedMap2 element {} value: {}", i, l_pair.second);
		i++;
	}
}
#endif