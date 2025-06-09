#ifndef SCENE_CHANGE_ACTIONS_IN_CLEAR
#define SCENE_CHANGE_ACTIONS_IN_CLEAR

#include <string>
#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActions.h"
#include "Scene/SceneType.h"

class SceneChangeActionsInClear : public SceneChangeActions
{
public:
    SceneChangeActionsInClear(InputSystem& input_);
    ~SceneChangeActionsInClear();
    
    bool ShouldChangeSceneTo(SceneType& outType) override;

private:
    InputSystem input;
};

#endif /* SCENE_CHANGE_ACTIONS_IN_CLEAR */