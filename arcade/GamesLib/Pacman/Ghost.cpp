// Created by floflolebg

#include "Ghost.hpp"

namespace Arcade {
    Ghost::Ghost(int x, int y, Arcade::Color color) {
        _pixel = new Pixel(x, y, color, 1);
        _color = color;
        _isDead = 0;
        _timeDead = 0;
        _xBegin = x;
        _yBegin = y;
    }

    Ghost::~Ghost() {
        delete (_pixel);
    }

    void Ghost::changeColor() {
        if (_isDead == 1) {
            _pixel->setColor(Color::MAGENTA);
        } else {
            _pixel->setColor(_color);
        }
    }

    void Ghost::giveTime(double time) {
        _timeDead += time;
        if (_timeDead > 5) {
            _timeDead = 0;
            _isDead = 0;
            changeColor();
        }
    }

    int Ghost::giveLife() const {
        return (_isDead);
    }

    void Ghost::kill() {
        _isDead = 1;
        _pixel->setXPos(_xBegin);
        _pixel->setYPos(_yBegin);
        changeColor();
    }

    Pixel *Ghost::getPixel() const {
        return (_pixel);
    }
}