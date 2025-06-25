#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <memory>
#include "Managers/SoundManager.h"

class InputManager;
class Timer;

struct AppContext {
    std::unique_ptr<SoundManager> sound = nullptr;
    // InputManager* input = nullptr;
    // Timer* timer = nullptr;
};

#endif
