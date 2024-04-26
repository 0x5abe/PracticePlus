#include "CheckpointObject.hpp"
#include <Geode/binding/ActiveSaveObject1.hpp>
#include <Geode/binding/CheckpointObject.hpp>
#include <Geode/binding/DynamicSaveObject.hpp>
#include <Geode/binding/GradientTriggerObject.hpp>
#include <Geode/binding/PlayerCheckpoint.hpp>
#include <Geode/binding/SequenceTriggerState.hpp>
#include <Geode/cocos/cocoa/CCArray.h>
#include <Geode/cocos/platform/CCPlatformMacros.h>
#include <managers/StartpointManager.hpp>
#include <hooks/cocos2d/CCObject.hpp>
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayerCheckpoint.hpp>
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/cocos2d/CCArray.hpp>
#include <hooks/GJShaderState.hpp>
#include <hooks/PlayLayer.hpp>
#include <hooks/SequenceTriggerState.hpp>
#include <hooks/FMODAudioState.hpp>
#include <hooks/EffectManagerState.hpp>
#include <hooks/GJGameState.hpp>
#include <hooks/ActiveSaveObject.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCheckpointObject::load(InputStream& i_stream) {
	reinterpret_cast<PPCCNode*>(this)->load(i_stream);
	i_stream >> *this;
}

void PPCheckpointObject::save(OutputStream& o_stream) {
	log::info("SAVING CHECKPOINT OBJECT");
	reinterpret_cast<PPCCNode*>(this)->save(o_stream);
	o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCheckpointObject& o_value) {
	// GJGameState m_gameState;
	//log::info("INPUT CCNODE uid: {}", o_value.m_uID);
	//log::info("INPUT CCNODE frotationx: {}", o_value.m_fRotationX);
	//log::info("INPUT CCNODE scale y: {}", o_value.m_fScaleY);
	SEPARATOR_I_C(GAME)
	reinterpret_cast<PPGJGameState*>(&o_value.m_gameState)->load(i_stream);
	SEPARATOR_I_C(GAME)

	// GJShaderState m_shaderState;
	SEPARATOR_I_C(SHAD)
	reinterpret_cast<PPGJShaderState*>(&o_value.m_shaderState)->load(i_stream);
	SEPARATOR_I_C(SHAD)

	// FMODAudioState m_audioState;
	SEPARATOR_I_C(AUDI)
	reinterpret_cast<PPFMODAudioState*>(&o_value.m_audioState)->load(i_stream);
	SEPARATOR_I_C(AUDI)

	CCPoint l_physicalCheckpointObjectStartPos;
	i_stream >> l_physicalCheckpointObjectStartPos;
	SEPARATOR_I

	// PlayerCheckpoint* m_player1Checkpoint;
	o_value.m_player1Checkpoint = PlayerCheckpoint::create();
	CC_SAFE_RETAIN(o_value.m_player1Checkpoint);
	reinterpret_cast<PPPlayerCheckpoint*>(o_value.m_player1Checkpoint)->load(i_stream);

	// PlayerCheckpoint* m_player2Checkpoint;
	bool l_hasPlayer2;
	i_stream >> l_hasPlayer2;
	//log::info("Has player 2 in: {}", l_hasPlayer2);
	SEPARATOR_I
	if (l_hasPlayer2) {
		o_value.m_player2Checkpoint = PlayerCheckpoint::create();
		CC_SAFE_RETAIN(o_value.m_player2Checkpoint);
		reinterpret_cast<PPPlayerCheckpoint*>(o_value.m_player2Checkpoint)->load(i_stream);
	}
	
	// int m_unkInt1;
	i_stream >> o_value.m_unkInt1;
	//log::info("o_value.m_unkInt1 in: {}", o_value.m_unkInt1);
	SEPARATOR_I

	// int m_unkInt2;
	i_stream >> o_value.m_unkInt2;
	//log::info("o_value.m_unkInt2 in: {}", o_value.m_unkInt2);
	SEPARATOR_I

	// int m_unkInt3;
	i_stream >> o_value.m_unkInt3;
	//log::info("o_value.m_unkInt3 in: {}", o_value.m_unkInt3);
	SEPARATOR_I

	// short m_unkShort1;
	i_stream >> o_value.m_unkShort1;
	//log::info("o_value.m_unkShort1 in: {}", o_value.m_unkShort1);
	SEPARATOR_I

	// int m_unkInt4;
	i_stream >> o_value.m_unkInt4;
	SEPARATOR_I

	// int m_unkInt5;
	i_stream >> o_value.m_unkInt5;
	VEC_SEPARATOR_I

	i_stream >> o_value.m_vectorDynamicSaveObjects;
	VEC_SEPARATOR_I

	i_stream >> o_value.m_vectorActiveSaveObjects1;
	VEC_SEPARATOR_I

	i_stream >> o_value.m_vectorActiveSaveObjects2;
	VEC_SEPARATOR_I

	// EffectManagerState m_effectManagerState;
	SEPARATOR_I_C(EFFE)
	reinterpret_cast<PPEffectManagerState*>(&o_value.m_effectManagerState)->load(i_stream);
	SEPARATOR_I_C(EFFE)

	// cocos2d::CCArray* m_gradientTriggerObjectArray;
	bool l_hasGradientTriggerObjectArray;
	i_stream >> l_hasGradientTriggerObjectArray;
	SEPARATOR_I
	if (l_hasGradientTriggerObjectArray) {
		o_value.m_gradientTriggerObjectArray = CCArray::create();
		CC_SAFE_RETAIN(o_value.m_gradientTriggerObjectArray);
		static_cast<PPCCArray*>(o_value.m_gradientTriggerObjectArray)->load<GradientTriggerObject>(i_stream);
		ARR_SEPARATOR_I
	}

	// bool m_unkBool1;
	i_stream >> o_value.m_unkBool1;
	SEPARATOR_I

	// gd::unordered_map<int,SequenceTriggerState> m_sequenceTriggerStateUnorderedMap;
	i_stream >> o_value.m_sequenceTriggerStateUnorderedMap;
	UMAP_SEPARATOR_I

	// int m_unkGetsCopiedFromGameState;
	i_stream >> o_value.m_unkGetsCopiedFromGameState;
	SEPARATOR_I

	// custom members

	i_stream >> o_value.m_fields->m_percentage;
	SEPARATOR_I

	// add the loaded startpoint to the list
	PPPlayLayer* l_playLayer = static_cast<PPPlayLayer*>(PlayLayer::get());
	if (l_playLayer) {
		// set the checkpoint as loaded so we can clean it up properly on remove
		o_value.m_fields->m_wasLoaded = true;
		l_playLayer->addStartpoint(StartpointManager::get().createStartpoint(&o_value, l_physicalCheckpointObjectStartPos));
	}
}

inline void operator<<(OutputStream& o_stream, PPCheckpointObject& i_value) {
	//log::info("OUTPUT CCNODE uid: {}", i_value.m_uID);
	//log::info("OUTPUT CCNODE frotationx: {}", i_value.m_fRotationX);
	//log::info("OUTPUT CCNODE scale y: {}", i_value.m_fScaleY);
	// GJGameState m_gameState;
	SEPARATOR_O_C(GAME)
	reinterpret_cast<PPGJGameState*>(&i_value.m_gameState)->save(o_stream);
	SEPARATOR_O_C(GAME)

	// GJShaderState m_shaderState;
	SEPARATOR_O_C(SHAD)
	reinterpret_cast<PPGJShaderState*>(&i_value.m_shaderState)->save(o_stream);
	SEPARATOR_O_C(SHAD)

	// FMODAudioState m_audioState;
	SEPARATOR_O_C(AUDI)
	reinterpret_cast<PPFMODAudioState*>(&i_value.m_audioState)->save(o_stream);
	SEPARATOR_O_C(AUDI)

	// GameObject* m_physicalCheckpointObject;
	o_stream << i_value.m_physicalCheckpointObject->m_startPosition;
	SEPARATOR_O

	// PlayerCheckpoint* m_player1Checkpoint;
	reinterpret_cast<PPPlayerCheckpoint*>(i_value.m_player1Checkpoint)->save(o_stream);

	// PlayerCheckpoint* m_player2Checkpoint;
	bool l_hasPlayer2 = false;
	if (i_value.m_player2Checkpoint) {
		l_hasPlayer2 = true;
	}
	//log::info("Has player 2 out: {}", l_hasPlayer2);
	o_stream << l_hasPlayer2;
	SEPARATOR_O
	if (l_hasPlayer2) {
		reinterpret_cast<PPPlayerCheckpoint*>(i_value.m_player2Checkpoint)->save(o_stream);
	}
	
	// int m_unkInt1;
	//log::info("i_value.m_unkInt1 in: {}", i_value.m_unkInt1);
	o_stream << i_value.m_unkInt1;
	SEPARATOR_O

	// int m_unkInt2;
	//log::info("i_value.m_unkInt2 in: {}", i_value.m_unkInt2);
	o_stream << i_value.m_unkInt2;
	SEPARATOR_O

	// int m_unkInt3;
	//log::info("i_value.m_unkInt3 in: {}", i_value.m_unkInt3);
	o_stream << i_value.m_unkInt3;
	SEPARATOR_O

	// short m_unkShort1;
	//log::info("i_value.m_unkShort1 in: {}", i_value.m_unkShort1);
	o_stream << i_value.m_unkShort1;
	SEPARATOR_O

	// int m_unkInt4;
	o_stream << i_value.m_unkInt4;
	SEPARATOR_O

	// int m_unkInt5;
	o_stream << i_value.m_unkInt5;
	VEC_SEPARATOR_O

	// gd::vector<DynamicSaveObject> m_vectorDynamicSaveObjects;
	o_stream << i_value.m_vectorDynamicSaveObjects;
	VEC_SEPARATOR_O

	// gd::vector<byte> m_vectorActiveSaveObjects1;
	o_stream << i_value.m_vectorActiveSaveObjects1;
	VEC_SEPARATOR_O

	// gd::vector<byte> m_vectorActiveSaveObjects2;
	o_stream << i_value.m_vectorActiveSaveObjects2;
	VEC_SEPARATOR_O

	// EffectManagerState m_effectManagerState;
	SEPARATOR_O_C(EFFE)
	reinterpret_cast<PPEffectManagerState*>(&i_value.m_effectManagerState)->save(o_stream);
	SEPARATOR_O_C(EFFE)

	// cocos2d::CCArray* m_gradientTriggerObjectArray;
	bool l_hasGradientTriggerObjectArray = false;
	if (i_value.m_gradientTriggerObjectArray) {
		l_hasGradientTriggerObjectArray = true;
	}
	o_stream << l_hasGradientTriggerObjectArray;
	SEPARATOR_O
	if (l_hasGradientTriggerObjectArray) {
		static_cast<PPCCArray*>(i_value.m_gradientTriggerObjectArray)->save<GradientTriggerObject>(o_stream);
		ARR_SEPARATOR_O
	}
	
	// bool m_unkBool1;
	o_stream << i_value.m_unkBool1;
	UMAP_SEPARATOR_O

	// gd::unordered_map<int,SequenceTriggerState> m_sequenceTriggerStateUnorderedMap;
	o_stream << i_value.m_sequenceTriggerStateUnorderedMap;
	UMAP_SEPARATOR_O

	// int m_unkGetsCopiedFromGameState;
	o_stream << i_value.m_unkGetsCopiedFromGameState;
	SEPARATOR_O

	// custom members

	o_stream << i_value.m_fields->m_percentage;
	SEPARATOR_O
}

void PPCheckpointObject::clean() {
	if (!m_fields->m_wasLoaded) return;

	reinterpret_cast<PPGJGameState*>(&m_gameState)->clean();

	reinterpret_cast<PPEffectManagerState*>(&m_effectManagerState)->clean();

	m_vectorDynamicSaveObjects.clear();
	gd::vector<DynamicSaveObject>().swap(m_vectorDynamicSaveObjects);

	m_vectorActiveSaveObjects1.clear();
	gd::vector<ActiveSaveObject1>().swap(m_vectorActiveSaveObjects1);

	m_vectorActiveSaveObjects2.clear();
	gd::vector<ActiveSaveObject2>().swap(m_vectorActiveSaveObjects2);
}

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
void PPCheckpointObject::describe() {
	log::info("[PPCheckpointObject - describe] start");
	reinterpret_cast<PPCCObject*>(this)->describe();
	reinterpret_cast<PPCCNode*>(this)->describe();
	reinterpret_cast<PPGJGameState*>(&m_gameState)->describe();
	reinterpret_cast<PPGJShaderState*>(&m_shaderState)->describe();
	reinterpret_cast<PPFMODAudioState*>(&m_audioState)->describe();
	log::info("[PPCheckpointObject - describe] m_physicalCheckpointObject->m_startPosition: {}", m_physicalCheckpointObject->m_startPosition);
	reinterpret_cast<PPPlayerCheckpoint*>(m_player1Checkpoint)->describe();
	if (m_player2Checkpoint) {
		reinterpret_cast<PPPlayerCheckpoint*>(m_player2Checkpoint)->describe();
	}
	log::info("[PPCheckpointObject - describe] m_unkInt1: {}", m_unkInt1);
	log::info("[PPCheckpointObject - describe] m_unkInt2: {}", m_unkInt2);
	log::info("[PPCheckpointObject - describe] m_unkInt3: {}", m_unkInt3);
	log::info("[PPCheckpointObject - describe] m_unkInt3: {}", m_unkInt3);
	log::info("[PPCheckpointObject - describe] m_unkInt3: {}", m_unkInt3);
	log::info("[PPCheckpointObject - describe] m_unkInt3: {}", m_unkInt3);
	int l_size = m_vectorDynamicSaveObjects.size();
	log::info("[PPEffectManagerState - describe] m_vectorDynamicSaveObjects.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPEffectManagerState - describe] m_vectorDynamicSaveObjects[{}]:", i);
		reinterpret_cast<PPDynamicSaveObject*>(&m_vectorDynamicSaveObjects[i])->describe();
	}
	l_size = m_vectorActiveSaveObjects1.size();
	log::info("[PPEffectManagerState - describe] m_vectorActiveSaveObjects1.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPEffectManagerState - describe] m_vectorActiveSaveObjects1[{}]:", i);
		reinterpret_cast<PPActiveSaveObject1*>(&m_vectorActiveSaveObjects1[i])->describe();
	}
	l_size = m_vectorActiveSaveObjects2.size();
	log::info("[PPEffectManagerState - describe] m_vectorActiveSaveObjects2.size(): {}", l_size);
	for (int i = 0; i < l_size; i++) {
		log::info("[PPEffectManagerState - describe] m_vectorActiveSaveObjects2[{}]:", i);
		reinterpret_cast<PPActiveSaveObject2*>(&m_vectorActiveSaveObjects2[i])->describe();
	}
	reinterpret_cast<PPEffectManagerState*>(&m_effectManagerState)->describe();
	if (m_gradientTriggerObjectArray) {
		reinterpret_cast<PPCCArray*>(m_gradientTriggerObjectArray)->describe<GradientTriggerObject>();
	}
	log::info("[PPCheckpointObject - describe] m_unkBool1: {}", m_unkBool1);
	l_size = m_sequenceTriggerStateUnorderedMap.size();
	log::info("[PPEffectManagerState - describe] m_sequenceTriggerStateUnorderedMap.size(): {}", l_size);
	int i = 0;
	for (std::pair<int, SequenceTriggerState> l_pair : m_sequenceTriggerStateUnorderedMap) {
		log::info("[PPEffectManagerState - describe] m_sequenceTriggerStateUnorderedMap element {} key: {}", i, l_pair.first);
		log::info("[PPEffectManagerState - describe] m_sequenceTriggerStateUnorderedMap element {} value:", i);
		reinterpret_cast<PPSequenceTriggerState*>(&l_pair.second)->describe();
		i++;
	}
	log::info("[PPCheckpointObject - describe] m_unkGetsCopiedFromGameState: {}", m_unkGetsCopiedFromGameState);
}
#endif