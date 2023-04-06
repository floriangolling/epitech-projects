//
// Created by Jean-Baptiste ROESCH on 29/03/2021.
//

#include <string>
#include "Core.hpp"

void print_help()
{
    std::cout << "Usage : ./arcade ./lib/arcade_xxxxx.so" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2 || (std::string(av[1]).compare("-h") == 0)) {
        print_help();
        _Exit(84);
    }
    try {
        Arcade::Core core{std::string(av[1])};
        core.loop();
        _Exit(0);
    } catch (std::exception &e) {
        std::cout << "Oops, a problem occured !" << std::endl;
        _Exit(84);
    }
}