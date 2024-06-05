
#include "OutputStream.hpp"
#include <hooks/CheckpointObject.hpp>
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/ActiveSaveObject.hpp>
#include <hooks/SequenceTriggerState.hpp>
#include <hooks/FMODQueuedMusic.hpp>
#include <hooks/FMODSoundState.hpp>
#include <hooks/TimerItem.hpp>
#include <hooks/TimerTriggerAction.hpp>
#include <hooks/KeyframeObject.hpp>
#include <hooks/GroupCommandObject2.hpp>
#include <hooks/SpawnTriggerAction.hpp>
#include <hooks/ToggleTriggerAction.hpp>
#include <hooks/CollisionTriggerAction.hpp>
#include <hooks/TouchToggleAction.hpp>
#include <hooks/CountTriggerAction.hpp>
#include <hooks/EventTriggerInstance.hpp>
#include <hooks/EnterEffectInstance.hpp>
#include <hooks/AdvancedFollowInstance.hpp>
#include <hooks/CAState.hpp>
#include <hooks/PlayLayer.hpp>
#include <hooks/SongChannelState.hpp>
#include <hooks/SongTriggerState.hpp>
#include <hooks/SFXTriggerState.hpp>

// vector

template<class T, class U>
inline void writeGenericVector(OutputStream* o_stream, gd::vector<T>& i_value) {
	unsigned int l_size = i_value.size();
	o_stream->write(reinterpret_cast<char*>(&l_size), 4);
	//geode::log::info("VECTOR SIZE CustomWrite SIZE out: {}", l_size);
	if (l_size == 0) return;
	for (int i = 0; i < l_size; i++) {
		reinterpret_cast<U&>(i_value[i]).save(*o_stream); 
	}
}

template <>
void OutputStream::operator<<<DynamicSaveObject>(gd::vector<DynamicSaveObject>& i_value) {
	writeGenericVector<DynamicSaveObject, PPDynamicSaveObject>(this, i_value);
}

template <>
void OutputStream::operator<<<ActiveSaveObject1>(gd::vector<ActiveSaveObject1>& i_value) {
	writeGenericVector<ActiveSaveObject1, PPActiveSaveObject1>(this, i_value);
}

template <>
void OutputStream::operator<<<ActiveSaveObject2>(gd::vector<ActiveSaveObject2>& i_value) {
	writeGenericVector<ActiveSaveObject2, PPActiveSaveObject2>(this, i_value);
}

template <>
void OutputStream::operator<<<CountTriggerAction>(gd::vector<CountTriggerAction>& i_value) {
	//geode::log::info("1111111111111111111 VECTOR CustomWrite CountTriggerAction");
	writeGenericVector<CountTriggerAction, PPCountTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<TouchToggleAction>(gd::vector<TouchToggleAction>& i_value) {
	//geode::log::info("22222222222222222222 VECTOR CustomWrite TouchToggleAction");
	writeGenericVector<TouchToggleAction, PPTouchToggleAction>(this, i_value);
}

template <>
void OutputStream::operator<<<CollisionTriggerAction>(gd::vector<CollisionTriggerAction>& i_value) {
	//geode::log::info("33333333333333333333 VECTOR CustomWrite CollisionTriggerAction");
	writeGenericVector<CollisionTriggerAction, PPCollisionTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<ToggleTriggerAction>(gd::vector<ToggleTriggerAction>& i_value) {
	//geode::log::info("4444444444444444444 VECTOR CustomWrite ToggleTriggerAction");
	writeGenericVector<ToggleTriggerAction, PPToggleTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<SpawnTriggerAction>(gd::vector<SpawnTriggerAction>& i_value) {
	//geode::log::info("55555555555555555555 VECTOR CustomWrite SpawnTriggerAction");
	writeGenericVector<SpawnTriggerAction, PPSpawnTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<GroupCommandObject2>(gd::vector<GroupCommandObject2>& i_value) {
	//geode::log::info("666666666666666666666 VECTOR CustomWrite GroupCommandObject2");
	writeGenericVector<GroupCommandObject2, PPGroupCommandObject2>(this, i_value);
}

template <>
void OutputStream::operator<<<KeyframeObject>(gd::vector<KeyframeObject>& i_value) {
	//geode::log::info("777777777777777777 VECTOR CustomWrite KeyframeObject");
	writeGenericVector<KeyframeObject, PPKeyframeObject>(this, i_value);
}

template <>
void OutputStream::operator<<<TimerTriggerAction>(gd::vector<TimerTriggerAction>& i_value) {
	//geode::log::info("8888888888888888888 VECTOR CustomWrite TimerTriggerAction");
	writeGenericVector<TimerTriggerAction, PPTimerTriggerAction>(this, i_value);
}

template <>
void OutputStream::operator<<<EventTriggerInstance>(gd::vector<EventTriggerInstance>& i_value) {
	//geode::log::info("00000000000 VECTOR CustomWrite EventTriggerInstance");
	writeGenericVector<EventTriggerInstance, PPEventTriggerInstance>(this, i_value);
}

template <>
void OutputStream::operator<<<EnterEffectInstance>(gd::vector<EnterEffectInstance>& i_value) {
	//geode::log::info("00232353000064545@@@@00003 VECTOR CustomWrite EnterEffectInstance");
	writeGenericVector<EnterEffectInstance, PPEnterEffectInstance>(this, i_value);
}

template <>
void OutputStream::operator<<<AdvancedFollowInstance>(gd::vector<AdvancedFollowInstance>& i_value) {
	//geode::log::info("UWUWUWUWUWUWUWUUWUWUWUWW VECTOR CustomWrite AdvancedFollowInstance");
	writeGenericVector<AdvancedFollowInstance, PPAdvancedFollowInstance>(this, i_value);
}

template <>
void OutputStream::operator<<<CAState>(gd::vector<CAState>& i_value) {
	//geode::log::info("OWOWOWOWOOWOWOW VECTOR CustomWrite CAState");
	writeGenericVector<CAState, PPCAState>(this, i_value);
}

template <>
void OutputStream::operator<<<PPCheckpointObject*>(gd::vector<PPCheckpointObject*>& i_value) {
	//geode::log::info("OWOWOWOWOOWOWOW VECTOR CustomWrite PPCheckpointobject");
	unsigned int l_size = i_value.size();
	write(reinterpret_cast<char*>(&l_size), 4);
	//geode::log::info("VECTOR SIZE CustomWrite SIZE out: {}", l_size);
	if (l_size == 0) return;
	for (int i = 0; i < l_size; i++) {
		#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
		reinterpret_cast<PPCheckpointObject*>(i_value[i])->describe();
		#endif
		reinterpret_cast<PPCheckpointObject*>(i_value[i])->save(*this); 
	}
}

template <>
void OutputStream::operator<<<SongTriggerState>(gd::vector<SongTriggerState>& i_value) {
	//geode::log::info("AWAWAWAWWAAWAWWAAWAW VECTOR CustomWrite SongTriggerState");
	writeGenericVector<SongTriggerState, PPSongTriggerState>(this, i_value);
}

template <>
void OutputStream::operator<<<SFXTriggerState>(gd::vector<SFXTriggerState>& i_value) {
	//geode::log::info("EWEWEWEWEWEWE VECTOR CustomWrite SongTriggerState");
	writeGenericVector<SFXTriggerState, PPSFXTriggerState>(this, i_value);
}

// unordered_map

template<class K, class V, class W>
inline void writeGenericUnorderedMap(OutputStream* o_stream, gd::unordered_map<K,V>& i_value) {
	unsigned int l_size = i_value.size();
	o_stream->write(reinterpret_cast<char*>(&l_size), 4);
	//geode::log::info("Unordered Map CustomWrite SIZE out: {}", l_size);
	if (l_size == 0) return;
	for (std::pair<K,V> l_pair : i_value) {
		o_stream->write(reinterpret_cast<char*>(&l_pair.first), sizeof(K));
		reinterpret_cast<W&>(l_pair.second).save(*o_stream);
	}
}

template <>
void OutputStream::operator<<<int, SequenceTriggerState>(gd::unordered_map<int, SequenceTriggerState>& i_value) {
	writeGenericUnorderedMap<int, SequenceTriggerState, PPSequenceTriggerState>(this, i_value);
}

template <>
void OutputStream::operator<<<int, FMODQueuedMusic>(gd::unordered_map<int, FMODQueuedMusic>& i_value) {
	writeGenericUnorderedMap<int, FMODQueuedMusic, PPFMODQueuedMusic>(this, i_value);
}

template <>
void OutputStream::operator<<<int, FMODSoundState>(gd::unordered_map<int, FMODSoundState>& i_value) {
	writeGenericUnorderedMap<int, FMODSoundState, PPFMODSoundState>(this, i_value);
}

template <>
void OutputStream::operator<<<int, TimerItem>(gd::unordered_map<int, TimerItem>& i_value) {
	//geode::log::info("999999999999999999999 Unordered Map CustomWrite TimerItem");
	writeGenericUnorderedMap<int, TimerItem, PPTimerItem>(this, i_value);
}

template <>
void OutputStream::operator<<<int, SongChannelState>(gd::unordered_map<int, SongChannelState>& i_value) {
	//geode::log::info("jjjjjjjjjjjjjjjjjjjjj Unordered Map CustomWrite SongChannelState");
	writeGenericUnorderedMap<int, SongChannelState, PPSongChannelState>(this, i_value);
}

template <>
void OutputStream::operator<<<int, EnhancedGameObject*>(gd::unordered_map<int, EnhancedGameObject*>& i_value) {
	unsigned int l_size = i_value.size();
	this->write(reinterpret_cast<char*>(&l_size), 4);
	//geode::log::info("Unordered Map CustomWrite EnhancedGameObject* SIZE out: {}", l_size);
	if (l_size == 0) return;
	int l_objectIndex;
	for (std::pair<int, EnhancedGameObject*> l_pair : i_value) {
		this->write(reinterpret_cast<char*>(&l_pair.first), sizeof(int));
		int l_objectIndex = -1;
		if (!l_pair.second) {
			//geode::log::info("no game object??");
		} else {
			PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
			if (l_playLayer) l_objectIndex = l_playLayer->getGameObjectIndex(l_pair.second);
		}
		this->write(reinterpret_cast<char*>(&l_objectIndex), sizeof(int));
	}
}