#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <string>
#include "Input/Keyboard.h"
#include "Input/GamePad.h"

class InputSystem
{
public:
    InputSystem();
    ~InputSystem();

    void Update();

    // ウィンドウからのキーボードイベントを受け取る
    void OnKeyEvent(int key, int action);

    const Keyboard& GetKeyboard() const { return keyboard; }
    const GamePad& GetGamePad() const { return gamePad; }
private:
    Keyboard keyboard;
    GamePad gamePad;
};

#endif /* INPUTSYSTEM_H */