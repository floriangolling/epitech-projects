#include "./Pacman.hpp"
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
    return new Arcade::Pacman();
}

namespace Arcade {
    Pacman::Pacman() {
        _carac = nullptr;
        recreateGame();
        createMenu();
        _time = std::chrono::high_resolution_clock::now();
        _score = 0;
        _PrintableScore = new Text(27, 15, "Score : 0", WHITE, 22);
        _inPause = 0;
        _playerName = nullptr;
    }

    void Pacman::createMenu() {
        _pauseMenu.push_back(new Text(30, 22, "SCORE: " + std::to_string(_score), WHITE, 22));
        _pauseMenu.push_back(new Text(30, 29, "ESCAPE: go back to menu", WHITE, 22));
        _pauseMenu.push_back(new Text(30, 31, "SPACE: go back to game", WHITE, 22));

        int xPac = 15;
        int yPac = 10;
        std::vector<std::string> artPac;
        std::string lineTwo;
        std::ifstream artPacMap("./GamesLib/Pacman/art.txt");
       if (!artPacMap) {
            std::cout << "PACMAN: path for snake not found!" << std::endl;
            throw std::exception();
        }
        while (std::getline(artPacMap, lineTwo)) {
            artPac.push_back(lineTwo);
        }
        for (auto it = artPac.begin(); it != artPac.end(); it++) {
            xPac = 15;
            for (auto itStr = (*it).begin(); itStr != (*it).end(); itStr++) {
                if ((*itStr) == ' ') {
                    _art.push_back(new Pixel(xPac, yPac, Arcade::Color::BLACK, 1));
                } else if ((*itStr) == '1') {
                    _art.push_back(new Pixel(xPac, yPac, Arcade::Color::RED, 1));
                } else if ((*itStr) == 'L') {
                    _art.push_back(new Pixel(xPac, yPac, Arcade::Color::WHITE, 1));
                } else if ((*itStr) == 'P')
                    _art.push_back(new Pixel(xPac, yPac, Arcade::Color::BLACK, 1));
                else if ((*itStr) == 'X') {
                    _art.push_back(new Pixel(xPac, yPac, Arcade::Color::YELLOW, 1));
                }
                xPac++;
            }
            yPac++;
        }
        artPacMap.close();
    }

    void Pacman::deletePac() {
        while (!_ghost.empty()) {
            delete (_ghost.back());
            _ghost.pop_back();
        }
        while (!_pixels.empty()) {
            delete (_pixels.back());
            _pixels.pop_back();
        }
        if (_carac) {
            delete (_carac);
            _carac = nullptr;
        }
    }

    void Pacman::recreateGame() {
        deletePac();
        _isTheBoss = 0;
        _dir = UP;
        std::vector<std::string> map;
        std::string line;
        std::ifstream map_pacman("./GamesLib/Pacman/pacman.txt");
        int y = 17;
        int x;

        if (!map_pacman) {
            std::cout << "PACMAN: File path not found." << std::endl;
            throw std::exception();
        }
        while (std::getline(map_pacman,line)) {
            if (line[0] != 'C') {
                checkLine(line);
                map.push_back(line);
            }
        }
        map_pacman.close();
        for (auto it = map.begin(); it != map.end(); it++) {
            x = 27;
            for (auto itStr = (*it).begin(); itStr != (*it).end(); itStr++) {
                if ((*itStr) == ' ')
                    _pixels.push_back(new Pixel(x, y, Color::WHITE, 1));
                else if (*itStr == 'X')
                    _pixels.push_back(new Pixel(x, y, Color::BLUE, 1));
                else if (*itStr == 'P') {
                    _carac = new Pixel(x, y, Color::YELLOW, 1);
                    _x = x;
                    _y = y;
                } else if (*itStr == '4') {
                    _tp1.first = x;
                    _tp1.second = y;
                } else if ((*itStr) == '5') {
                    _tp2.first = x;
                    _tp2.second = y;
                } else if ((*itStr) == '1')
                    _ghost.push_back(new Ghost(x, y, Color::RED));
                else if ((*itStr) == '2')
                    _ghost.push_back(new Ghost(x, y, Color::CYAN));
                else if ((*itStr) == '3')
                    _ghost.push_back(new Ghost(x, y, Color::GREEN));
                else if ((*itStr) == 'K')
                    _pixels.push_back(new Pixel(x, y, Color::YELLOW, 1));
                x += 1;
            }
            y += 1;
        }
    }

    void Pacman::moveGhost() {
        int myRand;
        Pixel *myGhost;
        for (auto it = _ghost.begin(); it != _ghost.end(); it++) {
            if ((*it)->giveLife() == 0) {
                myGhost = (*it)->getPixel();
                while (1) {
                    myRand = rand() % 4;
                    if (myRand == 0) {          //UP
                        if (checkPosition(myGhost->getXPos(), myGhost->getYPos() - 1) == 0) {
                            myGhost->setYPos(myGhost->getYPos() - 1);
                            break;
                        }
                    } else if (myRand == 1) {   //DOWN
                        if (checkPosition(myGhost->getXPos(), myGhost->getYPos() + 1) == 0) {
                            myGhost->setYPos(myGhost->getYPos() + 1);
                            break;
                        }
                    } else if (myRand == 2) {   //LEFT
                        if (checkPosition(myGhost->getXPos() - 1, myGhost->getYPos()) == 0) {
                            if (myGhost->getXPos() - 1 != _tp1.first || myGhost->getYPos() != _tp1.second) {
                                myGhost->setXPos(myGhost->getXPos() - 1);
                                break;
                            }
                        }
                    } else if (myRand == 3) {   //RIGHT
                        if (checkPosition(myGhost->getXPos() + 1, myGhost->getYPos()) == 0) {
                            if (myGhost->getXPos() + 1 != _tp2.first || myGhost->getYPos() != _tp2.second) {
                                myGhost->setXPos(myGhost->getXPos() + 1);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    void Pacman::setPlayerName(std::string &name)
    {
        size_t start_pos = 0;
        while((start_pos = name.find('_', start_pos)) != std::string::npos) {
            name.replace(start_pos, 1, " ");
            start_pos += 1;
        }
        if (name.front() == ' ')
            name = "Anonymous";
        _name = name;
        _playerName = new Text(33, 12, "Player : " + name, WHITE, 22);
    }

    Pacman::~Pacman() {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            delete (*it);
        }
        delete (_carac);
    }

    void Pacman::isTheBoss(double time) {
        static double elapsed = 0;
        elapsed += time;
        if (elapsed > 7) {
            _isTheBoss = 0;
            elapsed = 0;
        }
    }

    void Pacman::movePac() {
        if (_dir == LEFT) {
            if (checkPosition(_x - 1, _y) == 0) {
                _carac->setXPos(_x - 1);
                _x -= 1;
            }
        } else if (_dir == RIGHT) {
            if (checkPosition(_x + 1, _y) == 0) {
                _carac->setXPos(_x + 1);
                _x += 1;
            }
        } else if (_dir == UP) {
            if (checkPosition(_x, _y - 1) == 0) {
                _carac->setYPos(_y - 1);
                _y -= 1;
            }
        } else if (_dir == DOWN) {
            if (checkPosition(_x, _y + 1) == 0) {
                _carac->setYPos(_y + 1);
                _y += 1;
            }
        }
    }

    void Pacman::teleportPac() {
        if (_x == _tp2.first && _y == _tp2.second) {
            _x = _tp1.first;
            _y = _tp1.second;
        } else if (_x == _tp1.first && _y == _tp1.second) {
            _x = _tp2.first;
            _y = _tp2.second;
        }   
    }

    void Pacman::update(double time) {
        static double elapsed = 0;
        if (_inPause == 1)
            return;
        elapsed += time / 1000;
        if (_isTheBoss == 1)
            isTheBoss(time / 1000);
        for (auto it = _ghost.begin(); it != _ghost.end(); it++)
            if ((*it)->giveLife() == 1)
                (*it)->giveTime(time / 1000);
        if (elapsed > 0.4) {
            elapsed -= 0.4;
            movePac();
            teleportPac();
            beTheBoss(_x, _y);
            whiteSquare(_x, _y);
            hasWon();
            ghostCol(_x, _y);
            moveGhost();
            ghostCol(_x, _y);
            _pauseMenu.front()->setStr("SCORE : " + std::to_string(_score));
        }
    }

    void Pacman::hasWon() {
        int won = 1;
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == WHITE)
                won = 0;
        }
        if (won == 1) {
            _score += 100;
            recreateGame();
        }
    }

    void Pacman::ghostCol(int x, int y) {
        Pixel *myGhost;
        for (auto it = _ghost.begin(); it != _ghost.end(); it++) {
            myGhost = (*it)->getPixel();
            if (x == myGhost->getXPos() && y == myGhost->getYPos()) {
                if (_isTheBoss == 1) {
                    (*it)->kill();
                    _score += 100;
                    _PrintableScore->setStr("Score : " + std::to_string(_score));
                } else {
                    save_score(std::regex_replace(_name, std::regex("^ +| +$|( ) +"), "$1"), _score, "Pacman");
                    _score = 0;
                    recreateGame();
                    _PrintableScore->setStr("Score : " + std::to_string(_score));
                    break;
                }
            }
        }
    }

    int Pacman::checkPosition(int x, int y) {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == BLUE && (*it)->getXPos() == x && (*it)->getYPos() == y)
                return (1);
        }
        return (0);
    }

    void Pacman::whiteSquare(int x, int y) {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == WHITE && (*it)->getXPos() == x && (*it)->getYPos() == y) {
                (*it)->setColor(BLACK);
                _score++;
                _PrintableScore->setStr("Score : " + std::to_string(_score));
            }
        }
    }

    void Pacman::beTheBoss(int x, int y) {
        for (auto it = _pixels.begin(); it != _pixels.end(); it++) {
            if ((*it)->getColor() == YELLOW && (*it)->getXPos() == x && (*it)->getYPos() == y) {
                (*it)->setColor(BLACK);
                _isTheBoss = 1;
            }
        }
    }

    void Pacman::checkLine(const std::string &str) {
        std::vector<char> goodCharac = {'X', '5', '4', '3', '2', '1', ' ', 'P', '.', 'K'};
        for (auto it = str.begin(); it != str.end(); it++) {
            if (std::find(goodCharac.begin(), goodCharac.end(), (*it)) == goodCharac.end()) {
                throw std::exception();
            }
        }
    }

    void Pacman::draw(IGraphic& graphic) {
        graphic.myClear();
        if (!_inPause) {
            for (auto it = _pixels.begin(); it != _pixels.end(); it++)
                graphic.drawPixel(*it);
            for (auto it = _ghost.begin(); it != _ghost.end(); it++) {
                graphic.drawPixel((*it)->getPixel());
            }
            if (_isTheBoss == 1) {
                _carac->setColor(Color::MAGENTA);
            }
            graphic.drawPixel(_carac);
            _carac->setColor(YELLOW);
            graphic.drawText(_playerName);
            graphic.drawText(_PrintableScore);
        } else {
            for (auto it = _art.begin(); it != _art.end(); it++)
                graphic.drawPixel((*it));
            for (auto it = _pauseMenu.begin(); it != _pauseMenu.end(); it++)
                graphic.drawText((*it));        }
        graphic.myRefresh();
    }

    CommandType Pacman::getEvent(IGraphic &graph) {
        CommandType ev = graph.getInput();
        if (ev == CommandType::Z || ev == CommandType::UP) {
            if (checkPosition(_x, _y - 1) == 0)
                _dir = UP;
        } else if (ev == CommandType::Q || ev == CommandType::LEFT) {
            if (checkPosition(_x - 1, _y) == 0)
                _dir = LEFT;
        } else if (ev == CommandType::S || ev == CommandType::DOWN) {
            if (checkPosition(_x, _y + 1) == 0)
                _dir = DOWN;
        } else if (ev == CommandType::D || ev == CommandType::RIGHT) {
            if (checkPosition(_x + 1, _y) == 0)
                _dir = RIGHT;
        } else if (ev == CommandType::SPACE) {
            if (_inPause == 0)
                _inPause = 1;
            else {
                _inPause = 0;
            }
        }
        return (ev);
    }
}