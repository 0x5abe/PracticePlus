#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCArray.hpp>
#include <util/InputStream.hpp>
#include <util/OutputStream.hpp>
#include <hooks/CheckpointObject.hpp>

class $modify(PPCCArray, cocos2d::CCArray) {
public:
	$override
	unsigned int count();

	$override
	CCObject* lastObject();

	template <typename T>
	void load(InputStream& i_stream);

	template <typename T>
	void save(OutputStream& o_stream);

	template <>
	void load<GradientTriggerObject>(InputStream& i_stream);

	template <>
	void save<GradientTriggerObject>(OutputStream& o_stream);

#ifdef PP_DEBUG
	template <class T>
	void describe();

	template <>
	void describe<PPCheckpointObject>();

	template <>
	void describe<GradientTriggerObject>();
#endif
};