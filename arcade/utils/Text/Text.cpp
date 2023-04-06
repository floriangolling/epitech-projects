//
// Created by jeanningros on 3/22/21.
//

#include "Text.hpp"

Arcade::Text::Text(int xPos, int yPos, const std::string &str, Color color, int size) :  _xPos(xPos), _yPos(yPos) {
    _size = size;
    _str = str;
    _highlight = false;
    _color = color;
}

Arcade::Text::~Text() {
}

bool Arcade::Text::getHighlight() const {
    return _highlight;
}

void Arcade::Text::setHighlight(bool highlight) {
    _highlight = highlight;
}

int Arcade::Text::getXPos() const {
    return _xPos;
}

void Arcade::Text::setXPos(int xPos) {
    _xPos = xPos;
}

int Arcade::Text::getYPos() const {
    return _yPos;
}

void Arcade::Text::setYPos(int yPos) {
    _yPos = yPos;
}

int Arcade::Text::getSize() const {
    return _size;
}

void Arcade::Text::setSize(int size) {
    _size = size;
}

const std::string &Arcade::Text::getStr() const {
    return _str;
}

void Arcade::Text::setStr(const std::string &str) {
    _str = str;
}

Arcade::Color Arcade::Text::getColor() const {
    return _color;
}

void Arcade::Text::setColor(Arcade::Color color) {
    _color = color;
}
