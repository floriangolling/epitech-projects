//
// Created by jeanningros on 3/19/21.
//

#ifndef PACMAN_ARCADE_GAME_H
#define PACMAN_ARCADE_GAME_H

#include "../../utils/IGame.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include "Ghost.hpp"
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

namespace Arcade {
    class Pacman : public IGame {
    public:
        Pacman();
        ~Pacman();
        void recreateGame();
        void draw(IGraphic&) override;
        CommandType getEvent(IGraphic&) override;
        void update(double elapsed_time) override;
        void checkLine(const std::string &str);
        int checkPosition(int x, int y);
        void setPlayerName(std::string &name) override;
        void whiteSquare(int x, int y);
        void moveGhost();
        void isTheBoss(double time);
        void beTheBoss(int x, int y);
        void ghostCol(int x, int y);
        void hasWon();
        void createMenu();
        void movePac();
        void teleportPac();
        void deletePac();
        enum dir {
            LEFT,
            RIGHT,
            UP,
            DOWN
        };
    protected:
        std::vector<std::string> _map;
        std::vector<Pixel *> _pixels;
        Pixel *_carac;
        std::chrono::high_resolution_clock::time_point _time;
        std::chrono::high_resolution_clock::time_point _timeDisplay;
        dir _dir;
        int _x;
        int _y;
        std::pair<int, int> _tp1;
        std::pair<int, int> _tp2;
        Text *_playerName;;
        int _score;
        Text *_PrintableScore;
        int _isTheBoss;
        std::vector<Ghost *> _ghost;
        std::vector<Text *> _pauseMenu;
        std::vector<Pixel *> _art;
        int _inPause;
        std::string _name;
    };
}

#endif //PACMAN_ARCADE_GAME_H