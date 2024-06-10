
#pragma once
#include "Geode/binding/EndLevelLayer.hpp"
#include "Geode/cocos/cocoa/CCObject.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <sabe.persistencyutils/include/PersistencyUtils.hpp>

class $modify(PPEndLevelLayer, EndLevelLayer) {
public:

	// overrides
	$override
	void onMenu(cocos2d::CCObject* i_sender);
};