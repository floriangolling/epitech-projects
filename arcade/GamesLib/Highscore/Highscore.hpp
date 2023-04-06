//
// Created by jbroesch on 30/03/2021.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_MENU_HPP
#define B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_MENU_HPP

#include "../../utils/PersonnalType.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "../../utils/Text/Text.hpp"
#include "../../utils/IGame.hpp"
#include "../../utils/IGraphic.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <fstream>
#include <filesystem>
#include <map>

namespace Arcade {
    class Highscore: public IGame {
    public:
        Highscore();
        ~Highscore();
        void draw(IGraphic&) override;
        CommandType getEvent(IGraphic&) override;
        void update(double elapsed_time) override;
        void setPlayerName(std::string &name) override;

    protected:
        std::vector<Pixel> _pixels;
        std::vector<std::string> _ascii_highscore;
        std::vector<std::vector<std::string>> _high_score;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_MENU_HPP
