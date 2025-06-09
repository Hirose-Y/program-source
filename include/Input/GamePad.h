#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <string>

class GamePad {
    public:
        GamePad(int id);
        
        bool IsConnected() const;
        
        float GetAxis(int axis) const;             // アナログスティックの軸
        bool IsButtonPressed(int button) const;    // 押されているか
        bool IsButtonPressedOnce(int button) const;      // 1フレームだけ押されたか
        bool IsAnyButtonPressed() const;           // どれか1つでもボタンが押されたか
        bool IsAnyButtonPressedOnce() const;       // どれか1つでもボタンが1フレームだけ押されたか
        
        void Update();  // 前回のボタン状態を保存
    
    private:
        int joystickId;
        unsigned char prevButtons[32] = {0};       // 前フレームのボタン状態
    };
#endif /* GAMEPAD_H */