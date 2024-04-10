#pragma once
#include "Geode/binding/CheckpointObject.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <managers/StartpointManager.hpp>

class $modify(PPPlayLayer, PlayLayer) {
protected:
    void updatePlusModeVisibility(bool i_isPlusMode);

    void updatePlusModeLogic(bool i_isPlusMode);

public:
    bool m_enableArrayHook = false;
    //Todo: Remove
    bool m_loggedObjects = false;
    bool m_autoCreateSp1 = true;
    bool m_autoCreateSp2 = true;
    int m_placedCheckpoints = 0;
    //EndTodo

    // overrides

    $override bool init(GJGameLevel* i_level, bool i_useReplay, bool i_dontCreateObjects);

    $override void resetLevel();

    $override void togglePracticeMode(bool i_value);

    $override void updateVisibility(float i_unkFloat);

    $override void onQuit();

    //TodoRemove
    $override CheckpointObject* createCheckpoint();
    //EndTodoRemove
    
    // custom methods

    void addStartpoint(CheckpointObject* i_startpoint, int i_index = -1);

    void createStartpoint();

    bool removeStartpoint(int i_index = -1);

    inline CheckpointObject* getActiveStartpoint() { return StartpointManager::get().getActiveStartpoint(); }

    inline int getActiveStartpointId() { return StartpointManager::get().getActiveStartpointId(); }

    bool setActiveStartpointAndReload(int i_index);

    void reloadFromActiveStartpoint();

    inline bool isPlusMode() { return StartpointManager::get().isPlusMode(); }

    void togglePlusMode(bool i_value);

    void setupKeybinds();
};