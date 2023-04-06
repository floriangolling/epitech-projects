//
// Created by jeanningros on 3/23/21.
//

#include "Pixel.hpp"

Arcade::Pixel::Pixel(int xPos, int yPos, Arcade::Color color, int size) : _xPos(xPos), _yPos(yPos), _color(color), _size(size) {

}

Arcade::Pixel::~Pixel() {

}

int Arcade::Pixel::getXPos() const {
    return _xPos;
}

void Arcade::Pixel::setXPos(int xPos) {
    _xPos = xPos;
}

int Arcade::Pixel::getYPos() const {
    return _yPos;
}

void Arcade::Pixel::setYPos(int yPos) {
    _yPos = yPos;
}

int Arcade::Pixel::getSize() const {
    return _size;
}

void Arcade::Pixel::setSize(int size) {
    _size = size;
}

Arcade::Color Arcade::Pixel::getColor() const {
    return _color;
}

void Arcade::Pixel::setColor(Arcade::Color color) {
    _color = color;
}

int Arcade::Pixel::getFactor() const {
    return _factor;
}

void Arcade::Pixel::setFactor(int fact) {
    _factor = fact;
}