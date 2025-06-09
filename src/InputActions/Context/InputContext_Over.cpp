#include "Input/InputSystem.h"
#include "InputActions/Context/InputContext_Over.h"
#include "Core/GLHeaders.h"
#include "Scene/SceneType.h"
#include <iostream>

OverInputActions::OverInputActions(InputSystem& input)
: scene(input)
{
    
}