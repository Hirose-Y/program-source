#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include "Core/GLHeaders.h"
#include <unordered_map>

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();

    void ProcessKeyEvent(int key, int action);
    void UpdateKeyState();

    bool IsKeyPressed(int key) const;       // 押してる
    bool IsKeyPressedOnce(int key) const;   // 押した瞬間
    bool IsKeyReleasedOnce(int key) const;  // 離した瞬間
    
private:
    std::unordered_map<int, int> keyStatus;    // 現在のキー状態
    std::unordered_map<int, int> prevKeyStatus; // 前フレームのキー状態

public:
    #ifdef DEBUG_MODE
    void DebugPrintKeyStatus() const;
    #endif
};

#endif /* KEYBOARD_H */