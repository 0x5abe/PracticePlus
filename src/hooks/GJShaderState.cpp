#include "GJShaderState.hpp"
#include <hooks/cocos2d/CCNode.hpp>
#include <util/debug.hpp>

using namespace geode::prelude;

void PPGJShaderState::load(InputStream& i_stream) {
    i_stream >> *this;
}

void PPGJShaderState::save(OutputStream& o_stream) {
    o_stream << *this;
}

inline void operator>>(InputStream& i_stream, PPGJShaderState& o_value) {
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_someIntToValueTweenMap;
    UMAP_SEPARATOR_I
    i_stream >> o_value.m_someIntToDoubleMap;
    UMAP_SEPARATOR_I
    i_stream.read(reinterpret_cast<char*>(o_value.pad_1), 584);
    SEPARATOR_I
}

inline void operator<<(OutputStream& o_stream, PPGJShaderState& i_value) {
    UMAP_SEPARATOR_O
    o_stream << i_value.m_someIntToValueTweenMap;
    UMAP_SEPARATOR_O
    o_stream << i_value.m_someIntToDoubleMap;
    UMAP_SEPARATOR_O
    o_stream.write(reinterpret_cast<char*>(i_value.pad_1), 584);
    SEPARATOR_O
}