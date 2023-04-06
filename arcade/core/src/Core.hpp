//
// Created by Jean-Baptiste ROESCH on 29/03/2021.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_CORE_HPP
#define B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_CORE_HPP

#include <thread>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <filesystem>
#include "../../utils/IGraphic.hpp"
#include "../../utils/IGame.hpp"
#include "../../utils/LibLoader.hpp"
#include "../../GamesLib/Menu/IMenu.hpp"
#include <chrono>
#include <map>

typedef std::chrono::high_resolution_clock Clock;

namespace Arcade {

    class Core {
        public:
        Core(const std::string&);
        ~Core();
        void loop();
        int event();
        void display();
        void update(double elapsed);
        void load_library(const std::string&, LibType);
        bool change_name(int letter);
        void update_lib();

        private:
        LibLoader _charge_lib;
        LibType _actual_charged_game;
        short _is_highlight;
        void *_graph_Lib;
        void *_game_Lib;
        std::vector<std::vector<std::pair<std::string, std::string>>> _libsAvailable;
        Arcade::IGraphic *_libGraphic;
        Arcade::IGame *_libGame;
        std::string _playerName;
    };
}
#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_CORE_HPP
