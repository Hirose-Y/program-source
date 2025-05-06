#ifndef SCENE_CHANGE_ACTIONS_IN_PLAY
#define SCENE_CHANGE_ACTIONS_IN_PLAY

#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActions.h"
#include "GLHeaders.h"
#include "Scene/SceneType.h"

class SceneChangeActionsInPlay : public SceneChangeActions
{
public:
    SceneChangeActionsInPlay(InputSystem& input_);
    ~SceneChangeActionsInPlay();
    
    bool ShouldChangeSceneTo(SceneType& outType) override;

private:
    InputSystem input;
};

#endif /* SCENE_CHANGE_ACTIONS_IN_PLAY */