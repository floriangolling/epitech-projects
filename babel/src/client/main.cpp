#include "./Core/core.hpp"

int main(int ac, char **av) {
    try {
        Core *core = new Core();
        core->init(ac, av);
        return (core->display());
    } catch (...) {
        return (84);
    }
}