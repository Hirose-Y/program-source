#ifndef SCENE_CHANGE_ACTIONS_IN_TITLE
#define SCENE_CHANGE_ACTIONS_IN_TITLE

#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActions.h"
#include "GLHeaders.h"
#include "Scene/SceneType.h"

class SceneChangeActionsInTitle : public SceneChangeActions
{
public:
    SceneChangeActionsInTitle(InputSystem& input_);
    ~SceneChangeActionsInTitle();
    
    bool ShouldChangeSceneTo(SceneType& outType) override;

private:
    InputSystem input;
};

#endif /* SCENE_CHANGE_ACTIONS_IN_TITLE */