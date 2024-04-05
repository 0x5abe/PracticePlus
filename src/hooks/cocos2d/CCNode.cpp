#include "CCNode.hpp"
#include <hooks/cocos2d/CCObject.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPCCNode::load(InputStream& i_stream) {
    reinterpret_cast<PPCCObject*>(this)->load(i_stream);
    i_stream >> *this;
}

void PPCCNode::save(OutputStream& o_stream) {
    reinterpret_cast<PPCCObject*>(this)->save(o_stream);
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPCCNode& o_value) {
    i_stream >> o_value.m_fRotationX;
    SEPARATOR_I
    i_stream >> o_value.m_fRotationY;
    SEPARATOR_I
    i_stream >> o_value.m_fScaleX;
    SEPARATOR_I
    i_stream >> o_value.m_fScaleY;
    SEPARATOR_I
    i_stream >> o_value.m_fVertexZ;
    SEPARATOR_I
    i_stream >> o_value.m_obPosition;
    SEPARATOR_I
    i_stream >> o_value.m_fSkewX;
    SEPARATOR_I
    i_stream >> o_value.m_fSkewY;
    SEPARATOR_I
    i_stream >> o_value.m_obAnchorPointInPoints;
    SEPARATOR_I
    i_stream >> o_value.m_obAnchorPoint;
    SEPARATOR_I
    i_stream >> o_value.m_obContentSize;
    SEPARATOR_I
    i_stream >> o_value.m_sAdditionalTransform;
    SEPARATOR_I
    i_stream >> o_value.m_sTransform;
    SEPARATOR_I
    i_stream >> o_value.m_sInverse;
    SEPARATOR_I
    i_stream >> o_value.m_bRunning;
    SEPARATOR_I
    i_stream >> o_value.m_bTransformDirty;
    SEPARATOR_I
    i_stream >> o_value.m_bInverseDirty;
    SEPARATOR_I
    i_stream >> o_value.m_bAdditionalTransformDirty;
    SEPARATOR_I
    i_stream >> o_value.m_bVisible;
    SEPARATOR_I
    i_stream >> o_value.m_bIgnoreAnchorPointForPosition;
    SEPARATOR_I
    i_stream >> o_value.m_bReorderChildDirty;
    SEPARATOR_I
    i_stream >> o_value.m_bUnkBool1;
    SEPARATOR_I
    i_stream >> o_value.m_bUnkBool2;
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPCCNode& i_value) {
    o_stream << i_value.m_fRotationX;
    SEPARATOR_O
    o_stream << i_value.m_fRotationY;
    SEPARATOR_O
    o_stream << i_value.m_fScaleX;
    SEPARATOR_O
    o_stream << i_value.m_fScaleY;
    SEPARATOR_O
    o_stream << i_value.m_fVertexZ;
    SEPARATOR_O
    o_stream << i_value.m_obPosition;
    SEPARATOR_O
    o_stream << i_value.m_fSkewX;
    SEPARATOR_O
    o_stream << i_value.m_fSkewY;
    SEPARATOR_O
    o_stream << i_value.m_obAnchorPointInPoints;
    SEPARATOR_O
    o_stream << i_value.m_obAnchorPoint;
    SEPARATOR_O
    o_stream << i_value.m_obContentSize;
    SEPARATOR_O
    o_stream << i_value.m_sAdditionalTransform;
    SEPARATOR_O
    o_stream << i_value.m_sTransform;
    SEPARATOR_O
    o_stream << i_value.m_sInverse;
    SEPARATOR_O
    o_stream << i_value.m_bRunning;
    SEPARATOR_O
    o_stream << i_value.m_bTransformDirty;
    SEPARATOR_O
    o_stream << i_value.m_bInverseDirty;
    SEPARATOR_O
    o_stream << i_value.m_bAdditionalTransformDirty;
    SEPARATOR_O
    o_stream << i_value.m_bVisible;
    SEPARATOR_O
    o_stream << i_value.m_bIgnoreAnchorPointForPosition;
    SEPARATOR_O
    o_stream << i_value.m_bReorderChildDirty;
    SEPARATOR_O
    o_stream << i_value.m_bUnkBool1;
    SEPARATOR_O
    o_stream << i_value.m_bUnkBool2;
    SEPARATOR_O
}