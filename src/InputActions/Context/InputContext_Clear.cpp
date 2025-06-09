#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Clear.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

ClearInputActions::ClearInputActions(InputSystem& input)
: scene(input)
{
    
}