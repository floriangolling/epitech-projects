//
// Created by jeanningros on 3/19/21.
//

#ifndef SNAKE_ARCADE_H
#define SNAKE_ARCADE_H

#include "../../utils/IGame.hpp"
#include "../../utils/Pixel/Pixel.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

namespace Arcade {
    class Snake : public IGame {
    public:
        using Coord = std::pair<int, int>;
        Snake();
        ~Snake();
        void draw(IGraphic&) override;
        CommandType getEvent(IGraphic&) override;
        void update(double elapsed_time) override;
        void checkLine(const std::string &str);
        int checkColision(int x, int y, Arcade::Color);
        void setPlayerName(std::string &name) override;
        void spawnApple(double time);
        int isThereApple() const;
        Coord isSnakeThere() const;
        void createSnake(int x, int y);
        int touchItself();
        void createMenu();
        void moveSnake();
        enum Dir {
            LEFT,
            RIGHT,
            UP,
            DOWN
        };
    protected:
        size_t _numberBlackPixel;
        std::vector<std::string> _map;
        std::vector<Pixel *> _pixels;
        std::vector<Pixel *> _snake;
        Text *_playerName;
        std::string _name;
        Dir _direction;
        int _x;
        int _y;
        int _score;
        std::vector<Pixel *> _apples;
        Text *_scoreText;
        std::vector<Text *> _pauseMenu;
        std::vector<Pixel *> _art;
        int _inPause;
    };
}

#endif //SNAKE_ARCADE_H