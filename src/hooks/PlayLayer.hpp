#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

class $modify(PracticePlusPlayLayer, PlayLayer) {
protected:
    std::vector<CheckpointObject*> m_startpoints;
    int m_activeStartpointId = -1;
public:
    bool m_isPlusMode = true;
    bool m_isResetLevel = false;

    // overrides

    $override void resetLevel();

    // my stuff

    void addStartpoint(CheckpointObject* i_startpoint, int i_index = -1);

    bool removeStartPoint(int i_index = -1);

    CheckpointObject* getStartpoint(int i_index = -1);

    CheckpointObject* getActiveStartpoint();

    int getActiveStartpointId();

    bool setActiveStartpointId(int i_index = -1);

    bool reloadFromActiveStartpoint();

    void togglePlusMode();
};