#pragma once
#include "Geode/binding/CheckpointGameObject.hpp"
#include <iostream>
#include <Geode/Geode.hpp>
#include <Geode/loader/Log.hpp>
#include <Geode/binding/AdvancedFollowInstance.hpp>
#include <Geode/binding/EnhancedGameObject.hpp>
#include <Geode/binding/EnterEffectInstance.hpp>
#include <Geode/binding/EventTriggerInstance.hpp>
#include <Geode/binding/SongChannelState.hpp>

#define PP_OPERATOR_READ(type) virtual void operator>>(type& o_value) { read(reinterpret_cast<char*>(&o_value), sizeof(type)); }

class InputStream {
protected:
	std::istream* m_stream;
	unsigned int* m_bytesRead;
public:
	InputStream(std::string i_filePath) { m_stream = new std::ifstream(i_filePath, std::ios_base::binary); }
	InputStream(std::string i_filePath, unsigned int* i_bytesRead) {
		m_stream = new std::ifstream(i_filePath, std::ios_base::binary);
		m_bytesRead = i_bytesRead;
	}
	~InputStream() { delete m_stream; }

	void read(char* o_value, int i_size) { 
		m_stream->read(o_value, i_size); 
		
		if (m_bytesRead) {
			*m_bytesRead += i_size;
			if ((int)m_stream->tellg() != *m_bytesRead) {
				geode::log::info("DIFFERENCE IN POS AND BYTESREAD");
				geode::log::info("pos in stream: {}", (int)m_stream->tellg());
				geode::log::info("bytes read: {}", *m_bytesRead);
			}
		}
	}
	void ignore(int i_size) {
		m_stream->ignore(i_size);
		if (m_bytesRead) *m_bytesRead += i_size;
	}

	inline bool good() { return m_stream->good(); }

	PP_OPERATOR_READ(bool)
	PP_OPERATOR_READ(char)
	PP_OPERATOR_READ(unsigned char)
	PP_OPERATOR_READ(int)
	PP_OPERATOR_READ(unsigned int)
	PP_OPERATOR_READ(short)
	PP_OPERATOR_READ(unsigned short)
	PP_OPERATOR_READ(float)
	PP_OPERATOR_READ(double)
	PP_OPERATOR_READ(cocos2d::CCPoint)
	PP_OPERATOR_READ(cocos2d::CCSize)
	PP_OPERATOR_READ(cocos2d::CCAffineTransform)
	PP_OPERATOR_READ(uint64_t)

	// custom operators

	// vector

	template <class T>
	void operator>>(gd::vector<T>& o_value) {
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("VECTOR SIZE in: {}", l_size);
		if (l_size == 0) return;
		T value;
		for (int i=0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&value), sizeof(T));
			o_value.push_back(value);
		}
	}
	
	template <>
	void operator>><float>(gd::vector<float>& o_value) {
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("VECTOR SIZE in: {}", l_size);
		if (l_size == 0) return;
		o_value.reserve(l_size);
		float value;
		for (int i=0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&value), sizeof(float));
			//geode::log::info("VALUE VEC READ FLOAT: {}", value);
			o_value.push_back(value);
		}
	}

	template <>
	void operator>><DynamicSaveObject>(gd::vector<DynamicSaveObject>& o_value);

	template <>
	void operator>><ActiveSaveObject1>(gd::vector<ActiveSaveObject1>& o_value);

	template <>
	void operator>><ActiveSaveObject2>(gd::vector<ActiveSaveObject2>& o_value);

	template <>
	void operator>><CountTriggerAction>(gd::vector<CountTriggerAction>& o_value);

	template <>
	void operator>><TouchToggleAction>(gd::vector<TouchToggleAction>& o_value);

	template <>
	void operator>><CollisionTriggerAction>(gd::vector<CollisionTriggerAction>& o_value);

	template <>
	void operator>><ToggleTriggerAction>(gd::vector<ToggleTriggerAction>& o_value);

	template <>
	void operator>><SpawnTriggerAction>(gd::vector<SpawnTriggerAction>& o_value);

	template <>
	void operator>><GroupCommandObject2>(gd::vector<GroupCommandObject2>& o_value);

	template <>
	void operator>><KeyframeObject>(gd::vector<KeyframeObject>& o_value);

	template <>
	void operator>><TimerTriggerAction>(gd::vector<TimerTriggerAction>& o_value);

	template <>
	void operator>><EventTriggerInstance>(gd::vector<EventTriggerInstance>& o_value);

	template <>
	void operator>><EnterEffectInstance>(gd::vector<EnterEffectInstance>& o_value);

	template <>
	void operator>><AdvancedFollowInstance>(gd::vector<AdvancedFollowInstance>& o_value);

	template <>
	void operator>><CAState>(gd::vector<CAState>& o_value);

	template <>
	void operator>><CheckpointObject*>(gd::vector<CheckpointObject*>& o_value);

	// unordered_map

	template <class K, class V>
	void operator>>(gd::unordered_map<K,V>& o_value) {
		if (o_value.size() != 0) {
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Unordered Map SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		V l_value;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			read(reinterpret_cast<char*>(&l_value), sizeof(V));
			o_value[l_key] = l_value;
		}
	}

	template <class K, class V>
	void operator>>(gd::unordered_map<K,gd::vector<V>>& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Unordered Map key->vector<T> SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		V l_value;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			*this >> o_value[l_key];
		}
	}

	template <>
	void operator>><int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& o_value);

	template <>
	void operator>><int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& o_value);

	template <>
	void operator>><int, FMODSoundState_padded>(gd::unordered_map<int, FMODSoundState_padded>& o_value);

	template <>
	void operator>><int, TimerItem_padded>(gd::unordered_map<int, TimerItem_padded>& o_value);

	template <>
	void operator>><int, EnhancedGameObject*>(gd::unordered_map<int, EnhancedGameObject*>& o_value);

	template <>
	void operator>><int, SongChannelState>(gd::unordered_map<int, SongChannelState>& o_value);

	// unordered_set

	template <class K>
	void operator>>(gd::unordered_set<K>& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Unordered Set SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			o_value.insert(l_key);
		}
	}

	// map

	template <class K, class V>
	void operator>>(gd::map<K,V>& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Map SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		V l_value;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			read(reinterpret_cast<char*>(&l_value), sizeof(V));
			o_value[l_key] = l_value;
		}
	}

	template <class K, class V>
	void operator>>(gd::map<K,gd::vector<V>>& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Map key->vector<T> SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		V l_value;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			*this >> o_value[l_key];
		}
	}
	
	// set

	template <class K>
	void operator>>(gd::set<K>& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("Set SIZE in: {}", l_size);
		if (l_size == 0) return;
		K l_key;
		for (int i = 0; i < l_size; i++) {
			read(reinterpret_cast<char*>(&l_key), sizeof(K));
			o_value.insert(l_key);
		}
	}

	// gd::string

	void operator>>(gd::string& o_value) {
		if (o_value.size() != 0) {
			//geode::log::info("VECTOR SIZE SHOULD NOT BE HERE AGRIA: {}", o_value.size());
			o_value.clear();
		}
		unsigned int l_size;
		read(reinterpret_cast<char*>(&l_size), 4);
		//geode::log::info("String SIZE in: {}", l_size);
		if (l_size == 0) return;
		char* l_buf = new char[l_size+1];
		read(l_buf, l_size);
		l_buf[l_size] = '\0';
		o_value = l_buf;
		delete[] l_buf;
	}
};