#include "CheckpointObject.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <hooks/PlayerCheckpoint.hpp>
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
    if (l_hasPlayer2) {
        if (!o_value.m_player2Checkpoint) {
            o_value.m_player2Checkpoint = reinterpret_cast<PlayerCheckpoint*>(malloc(sizeof(PlayerCheckpoint)));
        }
        reinterpret_cast<PPPlayerCheckpoint*>(o_value.m_player2Checkpoint)->load(i_stream);
    }
    
	//int m_unkInt1;
    i_stream >> o_value.m_unkInt1;
	//int m_unkInt2;
    i_stream >> o_value.m_unkInt2;
	//int m_unkInt3;
    i_stream >> o_value.m_unkInt3;
	//short m_unkShort1;
    i_stream >> o_value.m_unkShort1;
	//PAD = win 0x2;
	//int m_unkInt4;
    i_stream >> o_value.m_unkInt4;
	//int m_unkInt5;
    i_stream >> o_value.m_unkInt5;
	//gd::vector<byte> m_unkVectorDynamicObjects;
	//gd::vector<byte> m_unkVectorActiveSaveObjects;
	//gd::vector<byte> m_unkVectorActiveSaveObjects2;
	//EffectManagerState m_effectManagerState;
	//PAD = win 0x1c;
	//cocos2d::CCArray* m_unkArray;
	//bool m_unkBool1;
    i_stream >> o_value.m_unkBool1;
	//PAD = win 0x3;
	//void* m_unkPtr1;
	//PAD = win 0x4;
	//gd::vector<byte> m_unkVector1;
	//PAD = win 0xc;
	//int m_unkGetsCopiedFromGameState;
    i_stream >> o_value.m_unkGetsCopiedFromGameState;
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
    if (l_hasPlayer2) {
        reinterpret_cast<PPPlayerCheckpoint*>(i_value.m_player2Checkpoint)->save(o_stream);
    }
    
	//int m_unkInt1;
    o_stream << i_value.m_unkInt1;
	//int m_unkInt2;
    o_stream << i_value.m_unkInt2;
	//int m_unkInt3;
    o_stream << i_value.m_unkInt3;
	//short m_unkShort1;
    o_stream << i_value.m_unkShort1;
	//PAD = win 0x2;
	//int m_unkInt4;
    o_stream << i_value.m_unkInt4;
	//int m_unkInt5;
    o_stream << i_value.m_unkInt5;
	//gd::vector<byte> m_unkVectorDynamicObjects; ---> NEXT
	//gd::vector<byte> m_unkVectorActiveSaveObjects; ---> NEXT
	//gd::vector<byte> m_unkVectorActiveSaveObjects2; ---> NEXT
	//EffectManagerState m_effectManagerState;
	//PAD = win 0x1c;
	//cocos2d::CCArray* m_unkArray; ---> NEXT
	//bool m_unkBool1;
    o_stream << i_value.m_unkBool1;
	//PAD = win 0x3;
	//void* m_unkPtr1;
	//PAD = win 0x4;
	//gd::vector<byte> m_unkVector1; ---> NEXT
	//PAD = win 0xc;
	//int m_unkGetsCopiedFromGameState;
    o_stream << i_value.m_unkGetsCopiedFromGameState;
}