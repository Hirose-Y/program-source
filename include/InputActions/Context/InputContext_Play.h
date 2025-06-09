#ifndef INPUT_CONTEXT_PLAY_H
#define INPUT_CONTEXT_PLAY_H

#include <string>
#include "Input/InputSystem.h"
#include "InputActions/Transition/SceneChangeActionsInPlay.h"
#include "InputActions/Player/PlayerActions.h"
#include "InputActions/World/WorlsActions.h"
#include "InputActions/Camera/CameraActions.h"

class PlayInputActions {
public:
    PlayInputActions(InputSystem& input_);
    InputSystem input;

    int ShowInfomation(bool& pause, int& mode) const;

    SceneChangeActionsInPlay scene;
    PlayerActions player;
    WorldActions world;
    CameraActions camera;
};

#endif /* INPUT_CONTEXT_PLAY_H */