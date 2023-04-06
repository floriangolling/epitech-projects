/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** IMenu
*/

#ifndef IMENU_HPP_
#define IMENU_HPP_

#include <vector>
#include "../../utils/Text/Text.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../utils/IGraphic.hpp"
#include "../../utils/IGame.hpp"

namespace Arcade {
    class IMenu: public IGame {
    public:
        virtual void draw(IGraphic&) = 0;
        virtual CommandType getEvent(IGraphic&) = 0;
        virtual void update(double elapsed_time) = 0;
        virtual void set_dispGame() = 0;
        virtual std::string getNameLib(std::string &) = 0;
        virtual void setPlayerName(std::string& player) = 0;
    };
}

#endif /* !IMENU_HPP_ */
