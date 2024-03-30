#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

class $modify(PracticePlusPlayLayer, PlayLayer) {
protected:
    std::vector<CheckpointObject*> m_startpoints;
    int m_activeStartpointId = -1;

    void updatePlusModeVisibility();

    void updatePlusModeLogic();
public:
    bool m_isPlusMode = false;
    bool m_isResetLevel = false;

    // overrides

    $override bool init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects);

    $override void resetLevel();

    $override void togglePracticeMode(bool i_value);

    // my stuff

    void addStartpoint(CheckpointObject* i_startpoint, int i_index = -1);

    bool removeStartpoint(int i_index = -1);

    CheckpointObject* getStartpoint(int i_index = -1);

    CheckpointObject* getActiveStartpoint();

    int getActiveStartpointId();

    bool setActiveStartpointId(int i_index = -1);

    bool reloadFromActiveStartpoint();

    void togglePlusMode(bool i_value);

    void togglePlusMode();

    void setupKeybinds();
};