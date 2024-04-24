#pragma once
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Log.hpp>
#include <Geode/binding/AdvancedFollowInstance.hpp>
#include <Geode/binding/CAState.hpp>
#include <Geode/binding/EnhancedGameObject.hpp>
#include <Geode/binding/EnterEffectInstance.hpp>
#include <Geode/binding/SongChannelState.hpp>

#define PP_OPERATOR_WRITE(type) virtual void operator<<(type& i_value) { m_stream->write(reinterpret_cast<char*>(&i_value), sizeof(type)); }

class OutputStream {
protected:
	std::ostream* m_stream;
public:
	OutputStream(std::string i_filePath) { m_stream = new std::ofstream(i_filePath, std::ios_base::binary); }
	~OutputStream() { delete m_stream; }
	
	PP_OPERATOR_WRITE(bool)
	PP_OPERATOR_WRITE(char)
	PP_OPERATOR_WRITE(unsigned char)
	PP_OPERATOR_WRITE(int)
	PP_OPERATOR_WRITE(unsigned int)
	PP_OPERATOR_WRITE(short)
	PP_OPERATOR_WRITE(unsigned short)
	PP_OPERATOR_WRITE(float)
	PP_OPERATOR_WRITE(double)
	PP_OPERATOR_WRITE(cocos2d::CCPoint)
	PP_OPERATOR_WRITE(cocos2d::CCSize)
	PP_OPERATOR_WRITE(cocos2d::CCAffineTransform)
	PP_OPERATOR_WRITE(uint64_t)

	void write(char* i_value, int i_size) { m_stream->write(i_value, i_size); }

	inline bool good() { return m_stream->good(); }

	// custom operators

	// vector

	template <class T>
	void operator<<(gd::vector<T>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("VECTOR SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		m_stream->write(reinterpret_cast<char*>(i_value.data()), l_size*sizeof(T));
	}

	template <>
	void operator<<<DynamicSaveObject>(gd::vector<DynamicSaveObject>& i_value);

	template <>
	void operator<<<ActiveSaveObject1>(gd::vector<ActiveSaveObject1>& i_value);

	template <>
	void operator<<<ActiveSaveObject2>(gd::vector<ActiveSaveObject2>& i_value);

	template <>
	void operator<<<CountTriggerAction>(gd::vector<CountTriggerAction>& i_value);

	template <>
	void operator<<<TouchToggleAction>(gd::vector<TouchToggleAction>& i_value);

	template <>
	void operator<<<CollisionTriggerAction>(gd::vector<CollisionTriggerAction>& i_value);

	template <>
	void operator<<<ToggleTriggerAction>(gd::vector<ToggleTriggerAction>& i_value);

	template <>
	void operator<<<SpawnTriggerAction>(gd::vector<SpawnTriggerAction>& i_value);

	template <>
	void operator<<<GroupCommandObject2>(gd::vector<GroupCommandObject2>& i_value);

	template <>
	void operator<<<KeyframeObject>(gd::vector<KeyframeObject>& i_value);

	template <>
	void operator<<<TimerTriggerAction>(gd::vector<TimerTriggerAction>& i_value);

	template <>
	void operator<<<EventTriggerInstance>(gd::vector<EventTriggerInstance>& i_value);

	template <>
	void operator<<<EnterEffectInstance>(gd::vector<EnterEffectInstance>& i_value);

	template <>
	void operator<<<AdvancedFollowInstance>(gd::vector<AdvancedFollowInstance>& i_value);

	template <>
	void operator<<<CAState>(gd::vector<CAState>& i_value);

	// unordered_map

	template <class K, class V>
	void operator<<(gd::unordered_map<K,V>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Unordered Map SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (std::pair<K,V> l_pair : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
			m_stream->write(reinterpret_cast<char*>(&l_pair.second), sizeof(V));
		}
	}

	template <class K, class V>
	void operator<<(gd::unordered_map<K,gd::vector<V>>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Unordered Map key->vector<T> SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (std::pair<K,gd::vector<V>> l_pair : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
			*this << l_pair.second; 
		}
	}

	template <>
	void operator<<<int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& i_value);

	template <>
	void operator<<<int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& i_value);

	template <>
	void operator<<<int, FMODSoundState_padded>(gd::unordered_map<int, FMODSoundState_padded>& i_value);

	template <>
	void operator<<<int, TimerItem_padded>(gd::unordered_map<int, TimerItem_padded>& i_value);

	template <>
	void operator<<<int, EnhancedGameObject*>(gd::unordered_map<int, EnhancedGameObject*>& i_value);

	template <>
	void operator<<<int, SongChannelState>(gd::unordered_map<int, SongChannelState>& i_value);

	// unordered_set

	template <class K>
	void operator<<(gd::unordered_set<K>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Unordered Set SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (K l_key : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_key), sizeof(K));
		}
	}

	// map

	template <class K, class V>
	void operator<<(gd::map<K,V>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Map SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (std::pair<K,V> l_pair : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
			m_stream->write(reinterpret_cast<char*>(&l_pair.second), sizeof(V));
		}
	}

	template <class K, class V>
	void operator<<(gd::map<K,gd::vector<V>>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Unordered Map key->vector<T> SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (std::pair<K,gd::vector<V>> l_pair : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
			*this << l_pair.second; 
		}
	}

	// set

	template <class K>
	void operator<<(gd::set<K>& i_value) {
		unsigned int l_size = i_value.size();
		//geode::log::info("Set SIZE out: {}", l_size);
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		for (K l_key : i_value) {
			m_stream->write(reinterpret_cast<char*>(&l_key), sizeof(K));
		}
	}

	// gd::string

	void operator<<(gd::string& i_value) {
		unsigned int l_size = i_value.size();
		m_stream->write(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("String SIZE in: {}", l_size);
		if (l_size == 0) return;
		m_stream->write(i_value.data(), l_size);
	}
};