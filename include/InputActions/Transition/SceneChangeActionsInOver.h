#ifndef SCENE_CHANGE_ACTIONS_IN_OVER
#define SCENE_CHANGE_ACTIONS_IN_OVER

#include <string>
#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActions.h"
#include "Scene/SceneType.h"

class SceneChangeActionsInOver : public SceneChangeActions
{
public:
    SceneChangeActionsInOver(InputSystem& input_);
    ~SceneChangeActionsInOver();
    
    bool ShouldChangeSceneTo(SceneType& outType) override;

private:
    InputSystem input;
};

#endif /* SCENE_CHANGE_ACTIONS_IN_OVER */