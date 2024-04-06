#include "CheckpointObject.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayerCheckpoint.hpp>
#include <hooks/DynamicSaveObject.hpp>
#include <hooks/cocos2d/CCArray.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCheckpointObject::load(InputStream& i_stream) {
    reinterpret_cast<PPCCNode*>(this)->load(i_stream);
    i_stream >> *this;
}

void PPCheckpointObject::save(OutputStream& o_stream) {
    reinterpret_cast<PPCCNode*>(this)->save(o_stream);
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCheckpointObject& o_value) {
    //GJGameState m_gameState;
	//GJShaderState m_shaderState;
	//FMODAudioState m_audioState;
	//GameObject* m_physicalCheckpointObject;
	//PlayerCheckpoint* m_player1Checkpoint;
    if (!o_value.m_player1Checkpoint) {
        o_value.m_player1Checkpoint = reinterpret_cast<PlayerCheckpoint*>(malloc(sizeof(PlayerCheckpoint)));
    }
    reinterpret_cast<PPPlayerCheckpoint*>(o_value.m_player1Checkpoint)->load(i_stream);
	//PlayerCheckpoint* m_player2Checkpoint;
    bool l_hasPlayer2;
    i_stream >> l_hasPlayer2;
	SEPARATOR_I
    if (l_hasPlayer2) {
        if (!o_value.m_player2Checkpoint) {
            o_value.m_player2Checkpoint = reinterpret_cast<PlayerCheckpoint*>(malloc(sizeof(PlayerCheckpoint)));
        }
        reinterpret_cast<PPPlayerCheckpoint*>(o_value.m_player2Checkpoint)->load(i_stream);
    }
    
	//int m_unkInt1;
    i_stream >> o_value.m_unkInt1;
	SEPARATOR_I
	//int m_unkInt2;
    i_stream >> o_value.m_unkInt2;
	SEPARATOR_I
	//int m_unkInt3;
    i_stream >> o_value.m_unkInt3;
	SEPARATOR_I
	//short m_unkShort1;
    i_stream >> o_value.m_unkShort1;
	SEPARATOR_I
	//PAD = win 0x2;
	//int m_unkInt4;
    i_stream >> o_value.m_unkInt4;
	SEPARATOR_I
	//int m_unkInt5;
    i_stream >> o_value.m_unkInt5;
	VEC_SEPARATOR_I
	//gd::vector<DynamicSaveObject> m_vectorDynamicSaveObjects;
	i_stream >> o_value.m_vectorDynamicSaveObjects;
	VEC_SEPARATOR_I
	i_stream >> o_value.m_vectorActiveSaveObjects1;
	VEC_SEPARATOR_I
	//gd::vector<byte> m_vectorActiveSaveObjects2;
	i_stream >> o_value.m_vectorActiveSaveObjects2;
	VEC_SEPARATOR_I
	//EffectManagerState m_effectManagerState;
	//PAD = win 0x1c;
	//cocos2d::CCArray* m_gradientTriggerObjectArray;
	bool l_hasGradientTriggerObjectArray;
    i_stream >> l_hasGradientTriggerObjectArray;
	SEPARATOR_I
	if (l_hasGradientTriggerObjectArray) {
		static_cast<PPCCArray*>(o_value.m_gradientTriggerObjectArray)->load<GradientTriggerObject>(i_stream);
		ARR_SEPARATOR_I
	}
	//bool m_unkBool1;
    i_stream >> o_value.m_unkBool1;
	SEPARATOR_I
	//PAD = win 0x3;
	//void* m_unkPtr1;
	//PAD = win 0x4;
	//gd::vector<byte> m_unkVector1;
	//PAD = win 0xc;
	//int m_unkGetsCopiedFromGameState;
    i_stream >> o_value.m_unkGetsCopiedFromGameState;
	SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPCheckpointObject& i_value) {
    //GJGameState m_gameState;
	//GJShaderState m_shaderState;
	//FMODAudioState m_audioState;
	//GameObject* m_physicalCheckpointObject;
	//PlayerCheckpoint* m_player1Checkpoint;
    reinterpret_cast<PPPlayerCheckpoint*>(i_value.m_player1Checkpoint)->save(o_stream);
	//PlayerCheckpoint* m_player2Checkpoint;
    bool l_hasPlayer2 = false;
    if (i_value.m_player2Checkpoint) {
        l_hasPlayer2 = true;
    }
    o_stream << l_hasPlayer2;
	SEPARATOR_O
    if (l_hasPlayer2) {
        reinterpret_cast<PPPlayerCheckpoint*>(i_value.m_player2Checkpoint)->save(o_stream);
    }
    
	//int m_unkInt1;
    o_stream << i_value.m_unkInt1;
	SEPARATOR_O
	//int m_unkInt2;
    o_stream << i_value.m_unkInt2;
	SEPARATOR_O
	//int m_unkInt3;
    o_stream << i_value.m_unkInt3;
	SEPARATOR_O
	//short m_unkShort1;
    o_stream << i_value.m_unkShort1;
	SEPARATOR_O
	//PAD = win 0x2;
	//int m_unkInt4;
    o_stream << i_value.m_unkInt4;
	SEPARATOR_O
	//int m_unkInt5;
    o_stream << i_value.m_unkInt5;
	VEC_SEPARATOR_O
	//gd::vector<DynamicSaveObject> m_vectorDynamicSaveObjects;
	o_stream << i_value.m_vectorDynamicSaveObjects;
	VEC_SEPARATOR_O
	//gd::vector<byte> m_vectorActiveSaveObjects1;
	o_stream << i_value.m_vectorActiveSaveObjects1;
	VEC_SEPARATOR_O
	//gd::vector<byte> m_vectorActiveSaveObjects2;
	o_stream << i_value.m_vectorActiveSaveObjects2;
	VEC_SEPARATOR_O
	//EffectManagerState m_effectManagerState;
	//PAD = win 0x1c;
	//cocos2d::CCArray* m_gradientTriggerObjectArray;
	bool l_hasGradientTriggerObjectArray = false;
    if (i_value.m_gradientTriggerObjectArray) {
        l_hasGradientTriggerObjectArray = true;
    }
	o_stream << l_hasGradientTriggerObjectArray;
	SEPARATOR_O
	if (i_value.m_gradientTriggerObjectArray) {
		static_cast<PPCCArray*>(i_value.m_gradientTriggerObjectArray)->save<GradientTriggerObject>(o_stream);
		ARR_SEPARATOR_O
	}
	
	//bool m_unkBool1;
    o_stream << i_value.m_unkBool1;
	SEPARATOR_O
	//PAD = win 0x3;
	//void* m_unkPtr1;
	//PAD = win 0x4;
	//gd::vector<byte> m_unkVector1; ---> NEXT
	//PAD = win 0xc;
	//int m_unkGetsCopiedFromGameState;
    o_stream << i_value.m_unkGetsCopiedFromGameState;
	SEPARATOR_O
}