//
// Created by jbroesch on 30/03/2021.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_NCURSES_HPP
#define B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_NCURSES_HPP

#include "../../utils/IGraphic.hpp"
#include "../../utils/PersonnalType.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../utils/Text/Text.hpp"
#include <stdexcept>
#include <ncurses.h>
#include <map>
#include <math.h>

namespace Arcade {
    std::map<int, CommandType> keyncursesMap {
            {'a', A},
            {'b', B},
            {'c', C},
            {'d', D},
            {'e', E},
            {'f', F},
            {'g', G},
            {'h', H},
            {'i', I},
            {'j', J},
            {'k', K},
            {'l', L},
            {'m', M},
            {'n', N},
            {'o', O},
            {'p', P},
            {'q', Q},
            {'r', R},
            {'s', S},
            {'t', T},
            {'u', U},
            {'v', V},
            {'w', W},
            {'x', X},
            {'y', Y},
            {'z', Z},
            {0, NUM0},
            {1, NUM1},
            {2, NUM2},
            {3, NUM3},
            {4, NUM4},
            {5, NUM5},
            {6, NUM6},
            {7, NUM7},
            {8, NUM8},
            {9, NUM9},
            {260, LEFT},
            {261, RIGHT},
            {259, UP},
            {258, DOWN},
            {10, ENTER},
            {' ', SPACE},
            {0407, BACKSPACE},
            {27, ESC},
            {265, F1},
            {266, F2},
            {267, F3},
            {268, F4},
            {269, F5},
            {270, F6},
    };

    class Ncurses : public IGraphic {
    public:
        Ncurses();
        ~Ncurses();

        void drawPixel(Pixel *pixel);
        void drawText(Text *text);
        void myClear();
        void myRefresh();
        CommandType getInput();
        std::string getName();
    private:
    };
}
#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_NCURSES_HPP
