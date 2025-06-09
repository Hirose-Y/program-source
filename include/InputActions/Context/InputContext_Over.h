#ifndef INPUT_CONTEXT_OVER_H
#define INPUT_CONTEXT_OVER_H

#include <string>
#include "Core/GLHeaders.h"
#include "Input/InputSystem.h"
#include "Scene/SceneType.h"
#include "InputActions/Transition/SceneChangeActionsInOver.h"

class OverInputActions {
public:
    OverInputActions(InputSystem& input);

    SceneChangeActionsInOver scene;
};

#endif /* INPUT_CONTEXT_OVER_H */
