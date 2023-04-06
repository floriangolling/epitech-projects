#include "./Snake.hpp"
#include "../Highscore/SaveHighScore.hpp"
#include <iostream>
#include <unistd.h>

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::GAME;
}

extern "C" Arcade::IGame *getLib()
{
    return new Arcade::Snake();
}

namespace Arcade {
    Snake::Snake() {
        _numberBlackPixel = 0;
        std::vector<std::string> map;
        std::string line;
        std::ifstream mapSnake("./GamesLib/Snake/snake.txt");
        int y = 20;
        int x = 20;

        if (!mapSnake) {
            std::cout << "SNAKE: path for snake not found!" << std::endl;
            throw std::exception();
        }
        while (std::getline(mapSnake,line)) {
            checkLine(line);
            map.push_back(line);
        }
        for (auto it = map.begin(); it != map.end(); it++) {
            x = 20;
            for (auto itStr = (*it).begin(); itStr != (*it).end(); itStr++) {
                if ((*itStr) == ' ') {
                    _pixels.push_back(new Pixel(x, y, Arcade::Color::BLACK, 1));
                    _numberBlackPixel++;
                } else if ((*itStr) == 'X') {
                    _pixels.push_back(new Pixel(x, y, Arcade::Color::BLUE, 1));
                } else if ((*itStr) == 'P') {
                    _x = x;
                    _y = y;
                    createSnake(x, y);
                }
                x++;
            }
            y++;
        }
        _direction = UP;
        createMenu();
        _inPause = 0;
    }

    void Snake::createMenu() {
        _scoreText = new Text(20, 18, "Score : 0", WHITE, 22);
        _pauseMenu.push_back(new Text(30, 22, "SCORE : " + std::to_string(_score), WHITE, 22));
        _pauseMenu.push_back(new Text(30, 29, "ESCAPE : go back to menu", WHITE, 22));
        _pauseMenu.push_back(new Text(30, 31, "SPACE : go back to game", WHITE, 22));

        int xSnake = 15;
        int ySnake = 10;
        std::vector<std::string> artSnake;
        std::string lineTwo;
        std::ifstream artSnakeMap("./GamesLib/Snake/art.txt");
       if (!artSnakeMap) {
            std::cout << "SNAKE: path for snake not found!" << std::endl;
            throw std::exception();
        }
        while (std::getline(artSnakeMap, lineTwo)) {
            artSnake.push_back(lineTwo);
        }
        for (auto it = artSnake.begin(); it != artSnake.end(); it++) {
            xSnake = 15;
            for (auto itStr = (*it).begin(); itStr != (*it).end(); itStr++) {
                if ((*itStr) == ' ') {
                    _art.push_back(new Pixel(xSnake, ySnake, Arcade::Color::BLACK, 1));
                } else if ((*itStr) == 'X') {
                    _art.push_back(new Pixel(xSnake, ySnake, Arcade::Color::GREEN, 1));
                } else if ((*itStr) == 'L') {
                    _art.push_back(new Pixel(xSnake, ySnake, Arcade::Color::WHITE, 1));
                } else if ((*itStr) == 'S')
                    _art.push_back(new Pixel(xSnake, ySnake, Arcade::Color::RED, 1));
                xSnake++;
            }
            ySnake++;
        }
        artSnakeMap.close();
    }

    void Snake::createSnake(int x, int y) {

        while (!_snake.empty()) {
            delete (_snake.back());
            _snake.pop_back();
        }

        _snake.push_back(new Pixel(x, y, Arcade::Color::GREEN, 1));
        _snake.push_back(new Pixel(x, y + 1, Arcade::Color::GREEN, 1));
        _snake.push_back(new Pixel(x, y + 2, Arcade::Color::GREEN, 1));
        _snake.push_back(new Pixel(x, y + 3, Arcade::Color::GREEN, 1));
        _score = 0;
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == RED)
                (*it)->setColor(BLACK);
        }
    }

    Snake::~Snake() {

    }

    void Snake::checkLine(const std::string &str) {
        std::vector<char> goodCharac = {'X', ' ', 'P'};
        for (auto it = str.begin(); it != str.end(); it++) {
            if (std::find(goodCharac.begin(), goodCharac.end(), (*it)) == goodCharac.end()) {
                throw std::exception();
            }
        }
    }

    void Snake::draw(IGraphic& graphic) {
        graphic.myClear();
        if (_inPause == 0) {
            for (auto it = _pixels.begin(); it != _pixels.end(); it++)
                if ((*it)->getColor() == BLUE || (*it)->getColor() == RED) {
                    graphic.drawPixel((*it));
                }
            for (auto it = _snake.begin(); it != _snake.end(); it++)
                graphic.drawPixel((*it));
            graphic.drawText(_playerName);
            graphic.drawText(_scoreText);
        } else {
            for (auto it = _art.begin(); it != _art.end(); it++)
                graphic.drawPixel((*it));
            for (auto it = _pauseMenu.begin(); it != _pauseMenu.end(); it++)
                graphic.drawText((*it));
        }
        graphic.myRefresh();
    }

    void Snake::setPlayerName(std::string &name)
    {
        size_t start_pos = 0;
        while((start_pos = name.find('_', start_pos)) != std::string::npos) {
            name.replace(start_pos, 1, " ");
            start_pos += 1;
        }
        if (name.front() == ' ')
            name = "Anonymous";
        _name = name;
        _playerName = new Text(34, 16, "Player : " + name, WHITE, 22);
    }

    int Snake::isThereApple() const {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == Color::RED)
                return (1);
        }
        return (0);
    }

    Snake::Coord Snake::isSnakeThere() const {
        int x = 0;
        int y = 0;
        while (1) {
            x = rand() % 36 + 40;
            y = rand() % 21 + 20;
            for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
                if (x == (*it)->getXPos() && y == (*it)->getYPos() && (*it)->getColor() == BLACK) {
                    for (auto itTwo = _snake.begin(); itTwo != _snake.end(); itTwo++) {
                        if ((*itTwo)->getXPos() != x && (*itTwo)->getYPos() != y)
                            return (std::pair<int,int>(x, y));
                    }
                }
            }
        }
    }

    void Snake::spawnApple(double time) {
        static double elapsed = 0;
        elapsed += time;
        if (elapsed > 5) {
            elapsed -= 5;
            Snake::Coord cod = isSnakeThere();
            for (auto it = _pixels.begin(); it != _pixels.end(); it++)
                if ((*it)->getXPos() == cod.first && (*it)->getYPos() == cod.second)
                    (*it)->setColor(RED);
            return;

        }
        if (isThereApple() == 0) {
            Snake::Coord cod = isSnakeThere();
            for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
                if ((*it)->getXPos() == cod.first && (*it)->getYPos() == cod.second) {
                    (*it)->setColor(Color::RED);
                    break;
                }
            }
            elapsed = 0;
            return;
        }
    }

    int Snake::touchItself() {
        for (size_t i = 0; i < _snake.size() - 1; i++) {
            for (size_t j = 0; j < _snake.size() - 1; j++) {
                if (_snake[i]->getXPos() == _snake[j]->getXPos() && _snake[i]->getYPos() == _snake[j]->getYPos() && i != j)
                    return (1);
            }
        }
        return (0);
    }

    void Snake::moveSnake() {
        if (_direction == Dir::UP) {
            _snake.front()->setYPos(_snake.front()->getYPos() - 1);
        } else if (_direction == Dir::DOWN) {
            _snake.front()->setYPos(_snake.front()->getYPos() + 1);
        } else if (_direction == Dir::RIGHT) {
            _snake.front()->setXPos(_snake.front()->getXPos() + 1);
        } else {
            _snake.front()->setXPos(_snake.front()->getXPos() - 1);
        }
    }

    void Snake::update(double timeElapsed) {
        static double elapsed = 0;
        if (_inPause == 1)
            return;
        spawnApple(timeElapsed / 1000);
        elapsed += timeElapsed / 1000;
        if (elapsed > 0.4) {
            elapsed -= 0.4;
            int xBack = _snake.back()->getXPos();
            int yBack = _snake.back()->getYPos();
            int x = _snake.front()->getXPos();
            int y = _snake.front()->getYPos();
            int x2;
            int y2;
            int firstMove = 0;
            for (auto it = _snake.begin(); it != _snake.end(); it++) {
                if (firstMove == 0) {
                    firstMove++;
                    continue;
                } else {
                    x2 = (*it)->getXPos();
                    y2 = (*it)->getYPos();
                    (*it)->setXPos(x);
                    (*it)->setYPos(y);
                    x = x2;
                    y = y2;
                }
            }
            moveSnake();
            for (auto it = _snake.begin(); it != _snake.end(); it++) {
                if (checkColision((*it)->getXPos(), (*it)->getYPos(), Color::BLUE) == 1) {
                    save_score(std::regex_replace(_name, std::regex("^ +| +$|( ) +"), "$1"), _score, "Snake");
                    _direction = Dir::UP;
                    createSnake(_x, _y);
                }
            }
            for (auto it = _snake.begin(); it != _snake.end(); it++) {
                if (checkColision((*it)->getXPos(), (*it)->getYPos(), RED) == 1) {
                    _snake.push_back(new Pixel(xBack, yBack, GREEN, 1));
                    _score += 1;
                    if (_snake.size() == _numberBlackPixel) {
                        createSnake(_x, _y);
                        _direction = Dir::UP;
                        _score = 1000;
                    }
                    break;
                }
            }
            if (touchItself() == 1) {
                _direction = Dir::UP;
                save_score(std::regex_replace(_name, std::regex("^ +| +$|( ) +"), "$1"), _score, "Snake");
                createSnake(_x, _y);
            }
            _scoreText->setStr("Score : " + std::to_string(_score));
            _pauseMenu.front()->setStr("SCORE : " + std::to_string(_score));
        }
    }

    int Snake::checkColision(int x, int y, Arcade::Color color) {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getXPos() == x && (*it)->getYPos() == y && color == (*it)->getColor()) {
                if (color == RED)
                    (*it)->setColor(BLACK);
                return (1);
            }
        }
        return (0);
    }

    CommandType Snake::getEvent(IGraphic &graph) {
        CommandType ev = graph.getInput();
        if ((ev == CommandType::Z || ev == CommandType::UP) && _direction != Dir::DOWN) {
            _direction = UP;
        } else if ((ev == CommandType::Q || ev == CommandType::LEFT) && _direction != Dir::RIGHT) {
            _direction = LEFT;
        } else if ((ev == CommandType::S || ev == CommandType::DOWN) && _direction != Dir::UP) {
            _direction = DOWN;
        } else if ((ev == CommandType::D || ev == CommandType::RIGHT) && _direction != Dir::LEFT) {
            _direction = RIGHT;
        } else if (ev == CommandType::SPACE) {
            if (_inPause == 1) {
                _inPause = 0;
            } else {
                _inPause = 1;
            }
        }
        return (ev);
    }
}