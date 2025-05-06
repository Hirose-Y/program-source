#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Clear.h"
#include "GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

ClearInputActions::ClearInputActions(InputSystem& input)
: scene(input)
{
    
}