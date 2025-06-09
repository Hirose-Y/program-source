#ifndef INPUT_CONTEXT_TITLE_H
#define INPUT_CONTEXT_TITLE_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"
#include "Scene/SceneType.h"
#include "InputActions/Transition/SceneChangeActionsInTitle.h"

class TitleInputActions {
public:
    TitleInputActions(InputSystem& input);

    SceneChangeActionsInTitle scene;
};

#endif /* INPUT_CONTEXT_TITLE_H */