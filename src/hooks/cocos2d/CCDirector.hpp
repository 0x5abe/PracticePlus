#pragma once
#include "Geode/modify/Modify.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>

class $modify(PPCCDirector, cocos2d::CCDirector) {
	public:
	// overrides

	$override
	bool replaceScene(cocos2d::CCScene* i_scene);
};