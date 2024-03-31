#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

class $modify(PracticePlusPlayLayer, PlayLayer) {
protected:
    geode::Ref<cocos2d::CCArray> m_startpoints = nullptr;
    int m_activeStartpointId = -1;

    void updatePlusModeVisibility();

    void updatePlusModeLogic();
public:
    bool m_isPlusMode = false;
    bool m_enableArrayHook = false;
    bool m_removeStartpoint = false;

    // overrides

    $override bool init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects);

    $override void resetLevel();

    $override void togglePracticeMode(bool i_value);

    // custom methods

    void addStartpoint(CheckpointObject* i_startpoint, int i_index = -1);

    void createStartpoint();

    bool removeStartpoint(int i_index = -1);

    CheckpointObject* getStartpoint(int i_index = -1);

    CheckpointObject* getActiveStartpoint();

    int getActiveStartpointId();

    void setActiveStartpointId(int i_index = -1);

    bool reloadFromActiveStartpoint();

    void togglePlusMode(bool i_value);

    void togglePlusMode();

    void prevStartpoint();

    void nextStartpoint();

    void setupKeybinds();
};