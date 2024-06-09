#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCArray.hpp>
#include <hooks/CheckpointObject.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>

class $modify(PPCCArray, cocos2d::CCArray) {
public:
	template <typename T>
	void load(InputStream& i_stream);

	template <typename T>
	void save(OutputStream& o_stream);

	template <typename T>
	void loadOne(InputStream& o_stream);

	template <typename T>
	void saveOne(OutputStream& o_stream, unsigned int i_index);

	template <>
	void load<GradientTriggerObject>(InputStream& i_stream);

	template <>
	void save<GradientTriggerObject>(OutputStream& o_stream);

#if defined(PP_DEBUG) && defined(PP_DESCRIBE)
	template <class T>
	void describe();

	// template <>
	// void describe<PPCheckpointObject>();

	template <>
	void describe<GradientTriggerObject>();
#endif
};