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
    class Howtoplay: public IGame {
    public:
        Howtoplay();
        ~Howtoplay();
        void draw(IGraphic&) override;
        CommandType getEvent(IGraphic&) override;
        void update(double elapsed_time) override;
        void setPlayerName(std::string &name) override;
        std::string getNameGraphical(std::string &fp);
        void set_dispGraphical();

    protected:
        std::vector<Pixel> _pixels;
        std::vector<Text> _disp_info;
        std::vector<std::string> _ascii_howto;
        std::vector<std::string> _dispGraphical;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_MENU_HPP
