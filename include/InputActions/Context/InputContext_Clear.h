#ifndef INPUT_CONTEXT_CLEAR_H
#define INPUT_CONTEXT_CLEAR_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"
#include "Scene/SceneType.h"
#include "InputActions/Transition/SceneChangeActionsInClear.h"

class ClearInputActions {
public:
    ClearInputActions(InputSystem& input);

    SceneChangeActionsInClear scene;
};

#endif /* INPUT_CONTEXT_CLEAR_H */
