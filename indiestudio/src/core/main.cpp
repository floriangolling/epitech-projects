//
// Created by jbroesch on 5/15/21.
//

#include "Core.hpp"
#include "../jsoncpp/json.h"
#include <iostream>
#include <fstream>

void print_help()
{
    std::cout << "Usage : ./bomberman" << std::endl;
}

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "-h")) {
        print_help();
        exit(0);
    }
    try {
        Indie::Core core;
        core.loop();
        exit(0);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(84);
    }
}