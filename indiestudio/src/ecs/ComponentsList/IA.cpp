//
// Created by jeanningros on 5/31/21.
//

#include "./IA.hpp"
#include <cstdlib>
#include <math.h>
#include "StatsComponent.hpp"
#include "BombComponent.hpp"

namespace Indie {

    IA::IA(std::array<std::string, 13> map, std::pair<float, float> posPlayer, std::pair<float, float> posTarget, int id) {
        _posPlayer = std::make_pair(posPlayer.first, posPlayer.second);
        _posTarget = std::make_pair(posTarget.first, posTarget.second);
        _posBombPlayer = std::make_pair(0, 0);
        _safeMode = false;
        _timing = 0;
        _myRange = 1;
        _mvtDirection = NONEIA;
        _posAdd = 0;
        _id = id;
        _speed = 0.15;
        _plantBomb = false;
        _travelWall = false;
        for (int y = 0; y < map.size(); y++) {
            _myMap[y] = map[y];
        }
    }

    void IA::setPlantBomb(bool i) {
        _plantBomb = i;
    }

    void IA::update(double time) {
        (void)time;
    }

    void IA::init(IGraphic *libgraphic) {
        (void)libgraphic;
    }

    void IA::moveToDirection(IGraphic &libgraphic, Component *compo, float time) {
        if (_posAdd + (compo->_entity->getComponent<StatsComponent>().getSpeed() * time) > 1) {
            float newSpeed = 1.0 - _posAdd;
            _posAdd += newSpeed;
            if (_mvtDirection == DOWNIA) {
                _posPlayer.second += newSpeed;
                libgraphic.rotateAngle(0, 0, 0, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == UPIA) {
                _posPlayer.second -= newSpeed;
                libgraphic.rotateAngle(0, 0, 180, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == LEFTIA) {
                _posPlayer.first -= newSpeed;
                libgraphic.rotateAngle(0, 0, 90, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == RIGHTIA) {
                _posPlayer.first += newSpeed;
                libgraphic.rotateAngle(0, 0, -90, &compo->_entity->getComponent<Perso3DComponent>());
            }
        } else if (_posAdd + (compo->_entity->getComponent<StatsComponent>().getSpeed() * time) <= 1) {
            _posAdd += (compo->_entity->getComponent<StatsComponent>().getSpeed() * time);
            if (_mvtDirection == DOWNIA) {
                _posPlayer.second += (compo->_entity->getComponent<StatsComponent>().getSpeed() * time);
                libgraphic.rotateAngle(0, 0, 0, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == UPIA) {
                _posPlayer.second -= (compo->_entity->getComponent<StatsComponent>().getSpeed() * time);
                libgraphic.rotateAngle(0, 0, 180, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == LEFTIA) {
                _posPlayer.first -= (compo->_entity->getComponent<StatsComponent>().getSpeed() * time);
                libgraphic.rotateAngle(0, 0, 90, &compo->_entity->getComponent<Perso3DComponent>());
            } else if (_mvtDirection == RIGHTIA) {
                _posPlayer.first += (compo->_entity->getComponent<StatsComponent>().getSpeed() * time);
                libgraphic.rotateAngle(0, 0, -90, &compo->_entity->getComponent<Perso3DComponent>());
            }
        }
        if (_posAdd == 1) {
            _posAdd = 0;
            _mvtDirection = NONEIA;
        }
        libgraphic.changeAnimation(MODEL_ACTION, &compo->_entity->getComponent<Perso3DComponent>());
        libgraphic.setXYZEntity(_posPlayer.first, 0, _posPlayer.second, compo);
    }

    void IA::moveToTarget(std::array<std::string, 13> map, IGraphic &libgraphic, Component *compo, float time) {
        if (_mvtDirection != NONEIA) {
            moveToDirection(libgraphic, compo, time);
            return;
        }
        _myRange = compo->_entity->getComponent<StatsComponent>().getRange();
        updateMap(map);

        int xDist = _posTarget.first - round(_posPlayer.first);
        int yDist = _posTarget.second - round(_posPlayer.second);
        if (isSafe() || moveIfBombOnLine() || moveToTargetSpecialCase()) {
            libgraphic.changeAnimation(MODEL_IDDLE, &compo->_entity->getComponent<Perso3DComponent>());
            return;
        } else if (xDist > yDist && xDist > 0) {
            if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA, true)) {
                _mvtDirection = RIGHTIA;
                if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 2] == 'B')
                    _plantBomb = true;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA) && yDist > 0) {
                _mvtDirection = DOWNIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA) && yDist < 0) {
                _mvtDirection = UPIA;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
            }
        } else if (xDist <= yDist && yDist > 0) {
            if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA, true)) {
                _mvtDirection = DOWNIA;
                if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) + 2][round(_posPlayer.first)] == 'B') {
                    _plantBomb = true;
                }
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA) && xDist > 0) {
                _mvtDirection = RIGHTIA;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA) && xDist < 0) {
                _mvtDirection = LEFTIA;
            } else if (!_travelWall && !_safeMode && map[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
            }
        } else if (xDist > yDist && yDist <= 0) {
            if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA, true)) {
                _mvtDirection = UPIA;
                if (!_travelWall && !_safeMode && map[round(_posPlayer.second) - 2][round(_posPlayer.first)] == 'B') {
                    _plantBomb = true;
                }
            } else if (!_travelWall && !_safeMode && map[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA) && xDist < 0) {
                _mvtDirection = LEFTIA;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA) && xDist > 0) {
                _mvtDirection = RIGHTIA;
            } else if (!_travelWall && !_safeMode && map[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
            }
        } else if (xDist <= yDist && xDist < 0) {
            if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA, true)) {
                _mvtDirection = LEFTIA;
                if (!_travelWall && !_safeMode && map[round(_posPlayer.second)][round(_posPlayer.first) - 2] == 'B') {
                    _plantBomb = true;
                }
            } else if (!_travelWall && !_safeMode && map[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') {
                    _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA) && yDist < 0) {
                _mvtDirection = UPIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA) && yDist > 0) {
                _mvtDirection = DOWNIA;
            } else if (!_travelWall && !_safeMode && map[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') {
                _plantBomb = true;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
            }
        }
    }

    bool IA::moveIfBombOnLine() {
        std::vector<std::pair<int, int>> pairPosBombEnemy = getPosBombEnemyOnLine();
        if (!(pairPosBombEnemy = getPosBombEnemyOnLine()).empty()) {
            for (auto & itPosBomb : pairPosBombEnemy) {
                int xDist = itPosBomb.first - (int) round(_posPlayer.first);
                int yDist = itPosBomb.second - (int) round(_posPlayer.second);
                if (yDist == 0) {
                    if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                        _mvtDirection = UPIA;
                        return true;
                    } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                        _mvtDirection = DOWNIA;
                        return true;
                    } else if (xDist > 0 && !checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second))) {
                        _mvtDirection = LEFTIA;
                        return true;
                    } else if (xDist < 0 && !checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second))) {
                        _mvtDirection = RIGHTIA;
                        return true;
                    }
                } else if (xDist == 0) {
                    if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                        _mvtDirection = LEFTIA;
                        return true;
                    } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                        _mvtDirection = RIGHTIA;
                        return true;
                    } else if (yDist > 0 && !checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1)) {
                        _mvtDirection = UPIA;
                        return true;
                    } else if (yDist < 0 && !checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1)) {
                        _mvtDirection = DOWNIA;
                        return true;
                    }
                }
            }
        }
        return false;
    };

    bool IA::moveToTargetSpecialCase() {
        int xDist = _posTarget.first - round(_posPlayer.first);
        int yDist = _posTarget.second - round(_posPlayer.second);
        if (yDist == -1) {
            if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA, true) && xDist > 0) {
                _mvtDirection = RIGHTIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA, true) && xDist < 0) {
                _mvtDirection = LEFTIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
                return true;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
                return true;
            }
        } if (yDist == 1) {
            if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA, true) && xDist > 0) {
                _mvtDirection = RIGHTIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA, true) && xDist < 0) {
                _mvtDirection = LEFTIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
                return true;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B') {
                _plantBomb = true;
                return true;
            }
        } else if (xDist == -1) {
            if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA, true) && yDist > 0) {
                _mvtDirection = DOWNIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA, true) && yDist < 0) {
                _mvtDirection = UPIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
                return true;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') {
                _plantBomb = true;
                return true;
            }
        } else if (xDist == 1) {
            if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA, true) && yDist > 0) {
                _mvtDirection = DOWNIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA, true) && yDist < 0) {
                _mvtDirection = UPIA;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
                return true;
            } else if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B') {
                _plantBomb = true;
                return true;
            }
        } else if (yDist == 0) {
            if (xDist < 0 && !checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
                if (!_travelWall && !_safeMode && xDist < 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 2] == 'B')
                    _plantBomb = true;
                return true;
            } else if (xDist > 0 && !checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
                if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 2] == 'B')
                    _plantBomb = true;
                return true;
            } else if (!_travelWall && !_safeMode && ((_myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B' && xDist > 0) || (_myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B' && xDist < 0))) {
                _plantBomb = true;
                return true;
            } else if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B'))) {
                _plantBomb = true;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
                if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B')))
                    _plantBomb = true;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
                if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'B')))
                    _plantBomb = true;
                return true;
            }
        } else if (xDist == 0) {
            if (yDist < 0 && !checkBarrier(round(_posPlayer.first), round(_posPlayer.second) - 1, UPIA)) {
                _mvtDirection = UPIA;
                if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) - 2][round(_posPlayer.first)] == 'B') {
                    _plantBomb = true;
                }
                return true;
            } else if (yDist > 0 && !checkBarrier(round(_posPlayer.first), round(_posPlayer.second) + 1, DOWNIA)) {
                _mvtDirection = DOWNIA;
                if (!_travelWall && !_safeMode && _myMap[round(_posPlayer.second) + 2][round(_posPlayer.first)] == 'B')
                    _plantBomb = true;
                return true;
            } else if (!_travelWall && !_safeMode && (_myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B' && yDist > 0 || _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B' && yDist < 0)) {
                _plantBomb = true;
                return true;
            } else if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B'))) {
                _plantBomb = true;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) + 1, round(_posPlayer.second), RIGHTIA)) {
                _mvtDirection = RIGHTIA;
                if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B')))
                    _plantBomb = true;
                return true;
            } else if (!checkBarrier(round(_posPlayer.first) - 1, round(_posPlayer.second), LEFTIA)) {
                _mvtDirection = LEFTIA;
                if (!_travelWall && !_safeMode && ((xDist < 0 && _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'B') || (xDist > 0 && _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'B')))
                    _plantBomb = true;
                return true;
            }
        }
        return false;
    }

    void IA::updateMap(std::array<std::string, 13> map) {
        for (int y = 0; y < map.size(); y++) {
            for (int x = 0; x < map[y].size(); x++) {
                if (_myMap[y][x] == 'B' && map[y][x] == ' ' || _myMap[y][x] == 'X' && map[y][x] == ' ' || _myMap[y][x] == 'S' && map[y][x] == ' ') {
                    _myMap[y][x] = ' ';
                } else if (_myMap[y][x] == ' ' && map[y][x] == 'X' || _myMap[y][x] == 'O' && map[y][x] == 'X') {
                    _myMap[y][x] = 'X';
                } else if (map[y][x] == 'S') {
                    _myMap[y][x] = 'S';
                }
            }
        }
    }

    void IA::addSavePos() {
        if (_travelWall)
            return;
        if (_myMap[round(_posPlayer.second)][round(_posPlayer.first)] == ' ')
            _myMap[round(_posPlayer.second)][round(_posPlayer.first)] = 'O';
        if (_myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == ' ')
            _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] = 'O';
        if (_myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == ' ')
            _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] = 'O';
        if (_myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == ' ')
            _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] = 'O';
        if (_myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == ' ')
            _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] = 'O';
    }

    void IA::findSafePos() {
        int distTotal;
        int nbCase;
        bool find = false;
        for (int i = 0; i < _myMap.size(); i++) {
            for (int y = 0; y < _myMap[i].size(); y++) {
                if (find) {
                    distTotal = abs(_posBombPlayer.first - y) + abs(_posBombPlayer.second - i);
                    if ((_myMap[i][y] == 'S' || _myMap[i][y] == 'O') && i != _posBombPlayer.second && y != _posBombPlayer.first && ((_posBombPlayer.second - i < 0 && abs(distTotal) < abs(nbCase)) || (_posBombPlayer.second - i >= 0 && abs(distTotal) <= abs(nbCase)))) {
                        _posTarget.first = y;
                        _posTarget.second = i;
                        nbCase = abs(_posBombPlayer.first - y) + abs(_posBombPlayer.second - i);
                    }
                }
                if (!find && (_myMap[i][y] == 'S' || _myMap[i][y] == 'O') && i != _posBombPlayer.second && y != _posBombPlayer.first ) {
                    find = true;
                    _posTarget.first = y;
                    _posTarget.second = i;
                    nbCase = abs(_posBombPlayer.first - y) + abs(_posBombPlayer.second - i);
                }
            }
        }
    }


    bool IA::isSafe() {
        if (_safeMode && round(_posPlayer.first) == _posTarget.first && round(_posPlayer.second) == _posTarget.second)
            return true;
        return false;
    }

    bool IA::checkBarrier(int x, int y, Direction direction, bool next) {
        if (_myMap[y][x] == '#')
            return true;
        if ((_myMap[y][x] == 'B' || _myMap[y][x] == 'X') && !_travelWall)
            return true;
        if (_plantBomb && round(_posPlayer.first) == _posBombPlayer.first && round(_posPlayer.second) == _posBombPlayer.second) {
            if (checkBarrierAround(round(_posPlayer.first), round(_posPlayer.second), direction)) {
                return true;
            }
        }
        if (next && !_travelWall) {
            if (checkBarrierAround(x, y, direction) && _safeMode) {
                return true;
            }
        }
        if ((direction == UPIA || direction == DOWNIA)) {
            if (checkBombOnLine(x, y, HORIZONTALIA)) {
                return true;
            }
        } else if ((direction == LEFTIA || direction == RIGHTIA)) {
            if (checkBombOnLine(x, y, VERTICALIA)) {
                return true;
            }
        }
        return false;
    }

    bool IA::checkBombOnLine(int x, int y, Direction direction) {
        if (direction == HORIZONTALIA) {
            for (int i = 0; i < _myMap[y].size(); i++) {
                if (_myMap[y][i] == 'X' && (int)round(_posPlayer.first) < i && (_myMap[y][i - 1] == ' ' || _myMap[y][i - 1] == 'O'))
                    return true;
                else if (_myMap[y][i] == 'X' && (int)round(_posPlayer.first) > i && (_myMap[y][i + 1] == ' ' || _myMap[y][i + 1] == 'O'))
                    return true;
            }
        } else if (direction == VERTICALIA) {
            for (int j = 0; j < _myMap.size(); j++) {
                if (_myMap[j][x] == 'X' && (int)round(_posPlayer.second) < j && (_myMap[j - 1][x] == ' ' || _myMap[j - 1][x] == 'O'))
                    return true;
                else if (_myMap[j][x] == 'X' && (int)round(_posPlayer.second) > j && (_myMap[j + 1][x] == ' ' || _myMap[j + 1][x] == 'O'))
                    return true;
            }
        }
        return false;
    }

    bool IA::checkBarrierAround(int x, int y, Direction direction) {
        if (direction == UPIA) {
            if ((_myMap[y - 1][x] == '#' || _myMap[y - 1][x] == 'B' || _myMap[y - 1][x] == 'X') &&
                (_myMap[y][x + 1] == '#' || _myMap[y][x + 1] == 'B' || _myMap[y][x + 1] == 'X') &&
                (_myMap[y][x - 1] == '#' || _myMap[y][x - 1] == 'B' || _myMap[y][x - 1] == 'X')) {
                return true;
            }
        } else if (direction == DOWNIA) {
            if ((_myMap[y + 1][x] == '#' || _myMap[y + 1][x] == 'B' || _myMap[y + 1][x] == 'X') &&
                (_myMap[y][x + 1] == '#' || _myMap[y][x + 1] == 'B' || _myMap[y][x + 1] == 'X') &&
                (_myMap[y][x - 1] == '#' || _myMap[y][x - 1] == 'B' || _myMap[y][x - 1] == 'X')) {
                return true;
            }
        } else if (direction == LEFTIA) {
            if ((_myMap[y - 1][x] == '#' || _myMap[y - 1][x] == 'B' || _myMap[y - 1][x] == 'X') &&
                (_myMap[y][x - 1] == '#' || _myMap[y][x - 1] == 'B' || _myMap[y][x - 1] == 'X') &&
                (_myMap[y + 1][x] == '#' || _myMap[y + 1][x] == 'B' || _myMap[y + 1][x] == 'X')) {
                return true;
            }
        } else if (direction == RIGHTIA) {
            if ((_myMap[y - 1][x] == '#' || _myMap[y - 1][x] == 'B' || _myMap[y - 1][x] == 'X') &&
                (_myMap[y][x + 1] == '#' || _myMap[y][x + 1] == 'B' || _myMap[y][x + 1] == 'X') &&
                (_myMap[y + 1][x] == '#' || _myMap[y + 1][x] == 'B' || _myMap[y + 1][x] == 'X')) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::pair<int, int>> IA::getPosBombEnemyOnLine() {
        std::vector<std::pair<int, int>> vectorPosBomb;

        for (int y = 0; y < _myMap.size(); y++) {
            for (int x = 0; x < _myMap.size(); x++) {
                if (_myMap[y][x] == 'X')
                    vectorPosBomb.push_back(std::make_pair(x, y));
            }
        }
        return vectorPosBomb;
    }

    int IA::getType() {
        return (_id);
    }

    std::pair<float, float> IA::plantBombe(std::array<std::string, 13> &map) {
        _plantBomb = false;
        map[round(_posPlayer.second)][round(_posPlayer.first)] = 'X';
        _myMap[round(_posPlayer.second)][round(_posPlayer.first)] = 'X';
        _posBombPlayer.first = round(_posPlayer.first);
        _posBombPlayer.second = round(_posPlayer.second);
        _safeMode = true;
        _timing = time(0);
        findSafePos();
        return (std::make_pair(round(_posPlayer.first), round(_posPlayer.second)));
    }

    void IA::setPosBombPlayer(std::pair<int, int> _pos) {
        _posBombPlayer.first = _pos.first;
        _posBombPlayer.second = _pos.second;
    }

    void IA::bombExplode(Component *compo) {
        _posBombPlayer = compo->_entity->getComponent<BombComponent>().getPosition();
        _myMap[_posBombPlayer.second][_posBombPlayer.first] = 'O';
        if (_myMap[_posBombPlayer.second + 1][_posBombPlayer.first] == 'B') {
            _myMap[_posBombPlayer.second + 1][_posBombPlayer.first] = 'O';
        }
        if (_myMap[_posBombPlayer.second - 1][_posBombPlayer.first] == 'B') {
            _myMap[_posBombPlayer.second - 1][_posBombPlayer.first] = 'O';
        }
        if (_myMap[_posBombPlayer.second][_posBombPlayer.first + 1] == 'B') {
            _myMap[_posBombPlayer.second][_posBombPlayer.first + 1] = 'O';
        }
        if (_myMap[_posBombPlayer.second][_posBombPlayer.first - 1] == 'B') {
            _myMap[_posBombPlayer.second][_posBombPlayer.first - 1] = 'O';
        }
        _safeMode = false;
        _posBombPlayer = std::make_pair(0, 0);
    }

    void IA::setSafeMode(bool i) {
        _safeMode = i;
    }

    void IA::takeBonus(std::array<std::string, 13> &map) {

        if (map[round(_posPlayer.second)][round(_posPlayer.first)] == 'S') {
            map[round(_posPlayer.second)][round(_posPlayer.first)] = ' ';
            _myMap[round(_posPlayer.second)][round(_posPlayer.first)] = ' ';
        }
    }

    bool IA::plantBombeNearEnemies(std::vector<std::pair<float, float>> posEnemies) {
        if (_safeMode || _myMap[round(_posPlayer.second)][round(_posPlayer.first)] == 'B')
            return false;
        for (auto & posEnemie : posEnemies) {
            float xDist = abs(posEnemie.first - _posPlayer.first);
            float yDist = abs(posEnemie.second - _posPlayer.second);
            if ((yDist <= 1 && xDist <= ((float)_myRange + 0.25)) || (xDist <= 1 && yDist <= (float)_myRange + 0.25)) {
                _plantBomb = true;
                return true;
            }
        }

        return false;

    }

    void IA::setPosTarget(std::vector<std::pair<float, float>> posEnemies) {
        int distTotal = 0;
        int nbCase = 0;
        bool find = false;

        for (int i = 0; i < _myMap.size(); i++) {
            for (int y = 0; y < _myMap[i].size(); y++) {
                if (find) {
                    distTotal = abs(_posTarget.first - y) + abs(_posTarget.second - i);
                    if (_myMap[i][y] == 'S' && distTotal < nbCase) {
                        _posTarget.first = y;
                        _posTarget.second = i;
                        nbCase = abs(_posTarget.first - y) + abs(_posTarget.second - i);
                    }
                } if (!find && _myMap[i][y] == 'S') {
                    find = true;
                    _posTarget.first = y;
                    _posTarget.second = i;
                    nbCase = abs(_posTarget.first - y) + abs( _posTarget.second - i);
                }
            }
        }
        for (auto &it: posEnemies) {
            if (find) {
                distTotal = abs(_posTarget.first - (int)round(it.first)) + abs(_posTarget.second - (int)round(it.second));
                if (distTotal < nbCase) {
                    _posTarget.first = round(it.first);
                    _posTarget.second = round(it.second);
                    nbCase = abs(_posTarget.first - (int)round(it.first)) + abs(_posTarget.second - (int)round(it.second));
                }
            } if (!find) {
                find = true;
                _posTarget.first = round(it.first);
                _posTarget.second = round(it.second);
                nbCase = abs(_posTarget.first - _posPlayer.first) + abs( _posTarget.second - _posPlayer.second);
            }
        }
    }

    std::vector<float> IA::getPosPlayer() const {
        std::vector<float> vect{_posPlayer.first, _posPlayer.second};
        return vect;
    }

    std::vector<int> IA::getPosTarget() const {
        std::vector<int> vect{_posTarget.first, _posTarget.second};
        return vect;
    }

    bool IA::getSafeMode() const {
        return _safeMode;
    }

    time_t IA::getTimingBombe() const {
        return _timing;
    }

    bool IA::getPlantBomb() const {
        return _plantBomb;
    }

    Direction IA::getDirection() const {
        return _mvtDirection;
    }

    void IA::setPosIA(float x, float z) {
        _posPlayer.first = round(x);
        _posPlayer.second = round(z);
        if (round(_posPlayer.first) <= 0)
            _posPlayer.first = 1.0;
        if (round(_posPlayer.second) <= 0)
            _posPlayer.second = 1.0; 
        if (round(_posPlayer.second) >= 12)
            _posPlayer.second = 11.0;
        if (round(_posPlayer.first) >= 14)
            _posPlayer.first = 13.0;
        if (_myMap[round(_posPlayer.second)][round(_posPlayer.first)] == '#' || _myMap[round(_posPlayer.second)][round(_posPlayer.first)] == 'B') {
            if (_myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == 'O' || _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first)] == ' ')
                _posPlayer.second += 1;
            else if (_myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == 'O' || _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first)] == ' ')
                _posPlayer.second -= 1;
            else if (_myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == 'O' || _myMap[round(_posPlayer.second)][round(_posPlayer.first) + 1] == ' ')
                _posPlayer.first += 1;
            else if (_myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == 'O' || _myMap[round(_posPlayer.second)][round(_posPlayer.first) - 1] == ' ')
                _posPlayer.first -= 1;
            else if (_myMap[round(_posPlayer.second) + 1][round(_posPlayer.first) + 1] == 'O' || _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first) + 1] == ' ') {
                _posPlayer.first += 1;
                _posPlayer.second += 1;
            } else if (_myMap[round(_posPlayer.second) - 1][round(_posPlayer.first) - 1] == 'O' || _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first) - 1] == ' ') {
                _posPlayer.first -= 1;
                _posPlayer.second -= 1;
            } else if (_myMap[round(_posPlayer.second) - 1][round(_posPlayer.first) + 1] == 'O' || _myMap[round(_posPlayer.second) - 1][round(_posPlayer.first) + 1] == ' ') {
                _posPlayer.first += 1;
                _posPlayer.second -= 1;
            } else if (_myMap[round(_posPlayer.second) + 1][round(_posPlayer.first) - 1] == 'O' || _myMap[round(_posPlayer.second) + 1][round(_posPlayer.first) - 1] == ' ') {
                _posPlayer.first -= 1;
                _posPlayer.second += 1;
            }
        }
        _mvtDirection = NONEIA;
    }

    void IA::setTravelWall(bool boolean) {
        if (boolean) {
            _safeMode = false;
        } else {
            _posAdd = 0;
        }
        _travelWall = boolean;
    }
}