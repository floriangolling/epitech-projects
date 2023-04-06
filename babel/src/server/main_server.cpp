//
// Created by jbroesch on 9/21/21.
//

#include "ServerTCP.hpp"
#include <iostream>

bool sig = false;

void print_help() {
    std::cout << "Usage: ./babel_server <port>\n";
}
void sig_handler(int var) {
    sig = true;
}
int main(int ac, char **av) {
    if (ac != 2) {
        print_help();
        return (0);
    }
    try {
        asio::io_service io;
        babel_server::Server serv(io, atoi(av[1]));
        std::signal(SIGINT, sig_handler);
        serv.run();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(84);
    }
    return 0;
}