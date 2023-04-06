/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Created by dmitry,
*/

#ifndef ARCADE_SDL_HPP
#define ARCADE_SDL_HPP

#include <stdexcept>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <vector>
#include "../../utils/IGraphic.hpp"
#include "../../utils/PersonnalType.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../utils/Text/Text.hpp"

namespace Arcade {
    std::map<int, CommandType> keysdlMap {
            {SDLK_a, A},
            {SDLK_b, B},
            {SDLK_c, C},
            {SDLK_d, D},
            {SDLK_e, E},
            {SDLK_f, F},
            {SDLK_g, G},
            {SDLK_h, H},
            {SDLK_i, I},
            {SDLK_j, J},
            {SDLK_k, K},
            {SDLK_l, L},
            {SDLK_m, M},
            {SDLK_n, N},
            {SDLK_o, O},
            {SDLK_p, P},
            {SDLK_q, Q},
            {SDLK_r, R},
            {SDLK_s, S},
            {SDLK_t, T},
            {SDLK_u, U},
            {SDLK_v, V},
            {SDLK_w, W},
            {SDLK_x, X},
            {SDLK_y, Y},
            {SDLK_z, Z},
            {SDLK_0, NUM0},
            {SDLK_1, NUM1},
            {SDLK_2, NUM2},
            {SDLK_3, NUM3},
            {SDLK_4, NUM4},
            {SDLK_5, NUM5},
            {SDLK_6, NUM6},
            {SDLK_7, NUM7},
            {SDLK_8, NUM8},
            {SDLK_9, NUM9},
            {SDLK_LEFT, LEFT},
            {SDLK_RIGHT, RIGHT},
            {SDLK_UP, UP},
            {SDLK_DOWN, DOWN},
            {13, ENTER},
            {SDLK_SPACE, SPACE},
            {SDLK_BACKSPACE, BACKSPACE},
            {SDLK_ESCAPE, ESC},
            {SDLK_F1, F1},
            {SDLK_F2, F2},
            {SDLK_F3, F3},
            {SDLK_F4, F4},
            {SDLK_F5, F5},
            {SDLK_F6, F6},
    };

    class SDL: public IGraphic {
    public:
        SDL();
        void drawPixel(Pixel *pixel);
        void drawText(Text *text);
        void myClear();
        void myRefresh();
        CommandType getInput();
        SDL_Color getSdlColor(Arcade::Color color);
        Uint8 getSdlColorRed(Arcade::Color color);
        Uint8 getSdlColorBlue(Arcade::Color color);
        Uint8 getSdlColorGreen(Arcade::Color color);
        std::string getName();
        virtual ~SDL();
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
    };
}

#endif //ARCADE_SDL_HPP
