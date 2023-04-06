/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Created by dmitry,
*/

#include "Sfml.hpp"

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::GRAPHIC;
}

extern "C" Arcade::IGraphic *getLib()
{
    return new Arcade::Sfml();
}

Arcade::Sfml::Sfml() {
    _window.create(sf::VideoMode(1200, 850), "Arcade", sf::Style::Close | sf::Style::Resize);
    _window.setFramerateLimit(30);
    _window.setPosition(sf::Vector2i(0, 0));
    _window.clear(sf::Color::Black);
    if (!(_font.loadFromFile("./GraphicalLib/Sfml/arial.ttf"))) {
        throw std::exception();
    }
}

std::string Arcade::Sfml::getName()
{
    return std::string("sfml");
}

Arcade::Sfml::~Sfml() {
    _window.close();
}

void Arcade::Sfml::drawPixel(Arcade::Pixel *pixel)
{
    int x = pixel->getXPos() * 15;
    int y = pixel->getYPos() * 15;
    int size = pixel->getSize() * 15;

    sf::RectangleShape rectangleShape;
    rectangleShape.setFillColor(ColorConverter(pixel->getColor()));
    rectangleShape.setSize(sf::Vector2f(size, size));
    rectangleShape.setPosition(sf::Vector2f(x, y));
    _window.draw(rectangleShape);
}

void Arcade::Sfml::drawText(Arcade::Text *text)
{
    int x = text->getXPos() * 15;
    int y = text->getYPos() * 15;
    int size = text->getSize();
    _text.setFont(_font);
    _text.setString(text->getStr());
    _text.setCharacterSize(size);
    _text.setFillColor(ColorConverter(text->getColor()));
    _text.setPosition((float)(x), (float)(y));
    if (text->getHighlight()) {
        sf::FloatRect backgroundRect = _text.getLocalBounds();
        sf::RectangleShape background(sf::Vector2f(backgroundRect.width, backgroundRect.height));
        background.setFillColor(ColorConverter(WHITE));
        background.setPosition(backgroundRect.left, backgroundRect.top);
        _window.draw(background, _text.getTransform());
        _text.setFillColor(ColorConverter(BLACK));
    }
    _window.draw(_text);
}

void Arcade::Sfml::myClear() {
    _window.clear();
}

void Arcade::Sfml::myRefresh() {
    _window.display();
}

Arcade::CommandType Arcade::Sfml::getInput() {
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            return (CLOSE_WINDOW);
        if (_event.type == sf::Event::KeyPressed) {
            for (const auto&[key, value] : keySfmlMap) {
                if (_event.key.code == key) {
                    return value;
                }
            }
        }
    }
    return (NO_EVENT);
}

sf::Color Arcade::Sfml::ColorConverter(Color color)
{
    for (const auto& [key, value] : colorSfmlMap) {
        if (color == key)
            return value;
    }
    return sf::Color::Black;
}
