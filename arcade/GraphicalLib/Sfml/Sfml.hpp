/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Created by dmitry,
*/

#ifndef ARCADE_SFML_HPP
#define ARCADE_SFML_HPP

#include "../../utils/IGraphic.hpp"
#include "../../utils/PersonnalType.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../utils/Text/Text.hpp"
#include <stdexcept>
#include <math.h>
#include <memory>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Arcade {

    std::map<Color, sf::Color> colorSfmlMap{
            {BLACK, sf::Color::Black},
            {WHITE, sf::Color::White},
            {RED, sf::Color::Red},
            {GREEN, sf::Color::Green},
            {BLUE, sf::Color::Blue},
            {YELLOW, sf::Color::Yellow},
            {MAGENTA, sf::Color::Magenta},
            {CYAN, sf::Color::Cyan},
            {TRANSPARENT, sf::Color::Transparent}
    };

    std::map<int, CommandType> keySfmlMap{
            {sf::Keyboard::A,      A},
            {sf::Keyboard::B,      B},
            {sf::Keyboard::C,      C},
            {sf::Keyboard::D,      D},
            {sf::Keyboard::E,      E},
            {sf::Keyboard::F,      F},
            {sf::Keyboard::G,      G},
            {sf::Keyboard::H,      H},
            {sf::Keyboard::I,      I},
            {sf::Keyboard::J,      J},
            {sf::Keyboard::K,      K},
            {sf::Keyboard::L,      L},
            {sf::Keyboard::M,      M},
            {sf::Keyboard::N,      N},
            {sf::Keyboard::O,      O},
            {sf::Keyboard::P,      P},
            {sf::Keyboard::Q,      Q},
            {sf::Keyboard::R,      R},
            {sf::Keyboard::S,      S},
            {sf::Keyboard::T,      T},
            {sf::Keyboard::U,      U},
            {sf::Keyboard::V,      V},
            {sf::Keyboard::W,      W},
            {sf::Keyboard::X,      X},
            {sf::Keyboard::Y,      Y},
            {sf::Keyboard::Z,      Z},
            {sf::Keyboard::Num0,   NUM0},
            {sf::Keyboard::Num1,   NUM1},
            {sf::Keyboard::Num2,   NUM2},
            {sf::Keyboard::Num3,   NUM3},
            {sf::Keyboard::Num4,   NUM4},
            {sf::Keyboard::Num5,   NUM5},
            {sf::Keyboard::Num6,   NUM6},
            {sf::Keyboard::Num7,   NUM7},
            {sf::Keyboard::Num8,   NUM8},
            {sf::Keyboard::Num9,   NUM9},
            {sf::Keyboard::Left,   LEFT},
            {sf::Keyboard::Right,  RIGHT},
            {sf::Keyboard::Up,     UP},
            {sf::Keyboard::Down,   DOWN},
            {sf::Keyboard::Enter,  ENTER},
            {sf::Keyboard::Space,  SPACE},
            {sf::Keyboard::BackSpace, BACKSPACE},
            {sf::Keyboard::Escape, ESC},
            {sf::Keyboard::F1,     F1},
            {sf::Keyboard::F2,     F2},
            {sf::Keyboard::F3,     F3},
            {sf::Keyboard::F4,     F4},
            {sf::Keyboard::F5,     F5},
            {sf::Keyboard::F6,     F6},
    };

    class Sfml: public IGraphic {
    public:
        Sfml();
        virtual ~Sfml();
        void drawPixel(Pixel *pixel);
        void drawText(Text *text);
        void myClear();
        void myRefresh();
        CommandType getInput();
        sf::Color ColorConverter(Color);
        std::string getName();

    private:
        sf::RenderWindow _window;
        sf::View _view;
        sf::Event _event;
        sf::Text _text;
        sf::Font _font;
    };
}

#endif //ARCADE_SFML_HPP
