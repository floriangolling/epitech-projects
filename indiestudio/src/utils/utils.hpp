//
// Created by jbroesch on 5/17/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_UTIS_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_UTIS_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include "../lodepng/lodepng.h"
#include "raymath.h"

namespace Indie {

    enum State {
        ALIVE,
        DEAD
    };

    enum Direction {
        UPIA,
        DOWNIA,
        LEFTIA,
        RIGHTIA,
        NONEIA,
        HORIZONTALIA,
        VERTICALIA
    };

    typedef struct IndieMatrix {
        float m0, m4, m8, m12;
        float m1, m5, m9, m13;
        float m2, m6, m10, m14;
        float m3, m7, m11, m15;
    } IndieMatrix;

    enum typePlayer {
        HUMAN,
        COMPUTER
    };

    typedef struct Vector {
        float x=0;
        float y=0;
        float z=0;
    } Vector;

    typedef struct Rect {
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
    } Rect;

    enum ButtonState {
        BUT_NO_EVENT,
        BUT_HOVER,
        BUT_CLICK
    };

    enum typeAnimation {
        MENUANIMATION,
        GAMEANIMATION,
        SELECTORANIMATION
    };

    enum Event {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum Ikey {
        UNKNOWN,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        COMAKEY,
        KEYUP,
        KEYDOWN,
        KEYLEFT,
        KEYRIGHT,
        ESC,
        SPACE,
        WINDOWCLOSE,
        NO_EVENT
    };

    enum GamepadEnum {
        GAMEPAD1 = 1,
        GAMEPAD2,
        GAMEPAD3,
        GAMEPAD4,
        GAMEPAD5,
        GAMEPAD6,
        GAMEPAD7,
        GAMEPAD8,
        GAMEPAD9,
        GAMEPAD10,
        GAMEPAD11,
        GAMEPAD12,
        GAMEPAD13,
        GAMEPAD15 = 15
    };

    enum SceneEnum {
        MAINMENU,
        SETTINGSMENU,
        LOADMENU,
        PLAYMENU,
        HOWTOMENU,
        PAUSEMENU,
        GAME
    };

    enum ModelSelection {
        MODEL_IDDLE,
        MODEL_ACTION,
        MODEL_DEATH
    };

}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_UTIS_HPP
