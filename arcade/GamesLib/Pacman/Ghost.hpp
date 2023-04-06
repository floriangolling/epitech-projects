//
// Created by jeanningros on 3/19/21.
//

#ifndef GHOST_ARCADE_H
#define GHOST_ARCADE_H

#include "../../utils/Pixel/Pixel.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

namespace Arcade {
    class Ghost {
    public:
        Ghost(int x, int y, Arcade::Color);
        ~Ghost();
        void changeColor();
        void giveTime(double time);
        int giveLife() const;
        void kill();
        Pixel *getPixel() const;
    protected:
        Pixel *_pixel;
        float _timeDead;
        int _xBegin;
        int _yBegin;
        int _isDead;
        Arcade::Color _color;
    };
}

#endif //PACMAN_ARCADE_GAME_H