#pragma once
#include "Geode/modify/Modify.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CCTransitionFade.hpp>

class $modify(PPCCTransitionFade, cocos2d::CCTransitionFade) {
	public:
	// custom methods
	
	cocos2d::CCScene* getInScene();
};