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
#include "../../utils/LibLoader.hpp"
#include "IMenu.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <dlfcn.h>
#include <fstream>
#include <filesystem>
#include <map>

namespace Arcade {
    class Menu: public IGame {
    public:
        Menu();
        ~Menu();
        void draw(IGraphic&) override;
        CommandType getEvent(IGraphic&) override;
        void update(double elapsed_time) override;
        void set_dispGame();
        void setPlayerName(std::string &name) override;

    protected:
        std::vector<Pixel> _pixels;
        std::vector<Text> _disp_Game;
        std::vector<std::string> _ascii_arcade;
        Text *_playerName;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_MENU_HPP
