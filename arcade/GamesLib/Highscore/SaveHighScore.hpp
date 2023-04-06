//
// Created by jbroesch on 11/04/2021.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_SAVEHIGHSCORE_HPP
#define B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_SAVEHIGHSCORE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <map>
#include <unistd.h>
#include <sstream>
#include <cstring>

namespace Arcade {

    std::vector<std::vector<std::string>> parse_file();

    void save_score(std::string username, int score, std::string gameName);

    bool sortbysecdesc(std::vector<std::string> a, std::vector<std::string> b);
}

#endif //B_OOP_400_STG_4_1_ARCADE_JEAN_BAPTISTE_ROESCH_SAVEHIGHSCORE_HPP
