//
// Created by jbroesch on 5/21/21.
//

#include <fstream>
#include <ostream>
#include <filesystem>
#include "EventManager.hpp"
#include "../ecs/Component.cpp"
#include "../ecs/ComponentsList/MouseEventComponent.hpp"
#include "../ecs/ComponentsList/KeyboardEventComponent.hpp"
#include "../ecs/ComponentsList/RectangleComponent.hpp"
#include "../ecs/ComponentsList/ButtonComponent.hpp"
#include "../ecs/ComponentsList/TextComponent.hpp"
#include "../ecs/ComponentsList/Perso3DComponent.hpp"
#include "../ecs/ComponentsList/BonusComponent.hpp"
#include "../ecs/ComponentsList/AnimationComponent.hpp"
#include "../ecs/ComponentsList/MapComponent.hpp"
#include "../ecs/ComponentsList/IA.hpp"
#include "../ecs/ComponentsList/BombComponent.hpp"
#include "../ecs/ComponentsList/StatsComponent.hpp"
#include "../ecs/ComponentsList/PauseComponent.hpp"
#include "../utils/GenerateImages.hpp"
#include <thread>
#include <chrono>

namespace fs = std::filesystem;

namespace Indie {


    EventManager::EventManager() = default;

    void EventManager::setClock() {
        _clock = new Clock();
    }

    Clock &EventManager::getClock() {
        return (*_clock);
    }

    void EventManager::setSceneEntity(std::map<std::string, std::shared_ptr<Entity>> &entities, IGraphic &libGraphic) {
        _entities = &entities;
        int i = 0;
        for (auto & _entitie : *_entities) {
            if (_entitie.second->hasComponent<MouseEventComponent>() && _entitie.second->hasComponent<RectangleComponent>()
                    && _entitie.second->hasComponent<ButtonComponent>() && _entitie.second->getComponent<ButtonComponent>().getButtonNumber() == 1) {
                    _entitie.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                    break;
            }
        }
        if (_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save")
            _isInGame = true;
        else if (_sceneManager->getCurrentScene()->getName() == "mainMenu")
            _isInGame = false;
        if (_sceneManager->getCurrentScene()->getName() == "mainMenu")
            setBombSelection(libGraphic);
    }

    void EventManager::setBombSelection(IGraphic &libGraphic) {
        Vector saved = libGraphic.getSavedBombSelection();
        if (saved.x > 0 && saved.y > 0) {
            for (auto & _entitie : *_entities) {
                if (_entitie.second->hasComponent<MouseEventComponent>() && _entitie.second->hasComponent<RectangleComponent>()
                    && _entitie.second->hasComponent<ButtonComponent>() && _entitie.second->getComponent<PositionComponent>().getPosition().y >  (saved.y - 40)
                    && _entitie.second->getComponent<PositionComponent>().getPosition().y <  (saved.y + 40)) {
                    for (auto & _entitie : *_entities) {
                        if (_entitie.second->hasComponent<MouseEventComponent>() && _entitie.second->hasComponent<RectangleComponent>()
                            && _entitie.second->hasComponent<ButtonComponent>() && _entitie.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                            _entitie.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        }
                    }
                    _entitie.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                    return;
                }
            }
        }
    }

    bool EventManager::getInGameState() {
        return _isInGame;
    }

    void EventManager::setKeysAtStart(void) {
        //First player keys;
        _savedKeys["leftOneButton"] = Q;
        _savedKeys["rightOneButton"] = D;
        _savedKeys["mupOneButton"] = Z;
        _savedKeys["downOneButton"] = S;
        _savedKeys["dropOneButton"] = E;
        //Second player keys;
        _savedKeys["leftTwoButton"] = F;
        _savedKeys["rightTwoButton"] = H;
        _savedKeys["mupTwoButton"] = T;
        _savedKeys["downTwoButton"] = G;
        _savedKeys["dropTwoButton"] = Y;
        //etc..
        _savedKeys["leftThreeButton"] = J;
        _savedKeys["rightThreeButton"] = L;
        _savedKeys["mupThreeButton"] = I;
        _savedKeys["downThreeButton"] = K;
        _savedKeys["dropThreeButton"] = O;

        _savedKeys["leftFourButton"] = KEYLEFT;
        _savedKeys["rightFourButton"] = KEYRIGHT;
        _savedKeys["mupFourButton"] = KEYUP;
        _savedKeys["downFourButton"] = KEYDOWN;
        _savedKeys["dropFourButton"] = SPACE;

        _playerStates.push_back(HUMAN);
        _playerStates.push_back(COMPUTER);
        _playerStates.push_back(COMPUTER);
        _playerStates.push_back(COMPUTER);

        _alivePlayers.push_back(ALIVE);
        _alivePlayers.push_back(ALIVE);
        _alivePlayers.push_back(ALIVE);
        _alivePlayers.push_back(ALIVE);
        _scrollValue = 0;
    }

    bool EventManager::isThisKeyBindedAlready(Ikey key) const {
        for (auto it = _savedKeys.begin(); it != _savedKeys.end(); it++) {
            if ((*it).second == key) {
                return (true);
            }
        }
        return (false);
    }

    void EventManager::makeIAMove(IGraphic &libgraphic, float time) {
        static int bombnumber = -1;
        MapComponent *map = nullptr;
        for (auto &e : *_entities) {
            if (e.second->hasComponent<MapComponent>() && e.second->getComponent<MapComponent>().getType() == 0) {
                map = &e.second->getComponent<MapComponent>();
                break;
            }
        }
        if (map == nullptr) {
            return;
        }
        for (auto &e : *_entities) {
            if (e.second->hasComponent<IA>()) {
                Component *compo = nullptr;
                for (auto &k : *_entities) {
                    if (k.second->hasComponent<Perso3DComponent>() && k.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID() == e.second->getComponent<IA>().getType()) {
                        compo = &k.second->getComponent<Perso3DComponent>();
                        break;
                    }
                }
                if (compo == nullptr) {
                    return;
                }
                if (_alivePlayers[compo->_entity->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()] == DEAD)
                    continue;
                e.second->getComponent<IA>().takeBonus(map->getMyMapArray());
                e.second->getComponent<IA>().addSavePos();
                e.second->getComponent<IA>().moveToTarget(map->getMyMapArray(), libgraphic, compo, time);
                if (e.second->getComponent<IA>().getPlantBomb() && e.second->getComponent<IA>().getDirection() == NONEIA) {
                    std::pair<float, float> pos = e.second->getComponent<IA>().plantBombe(map->getMyMapArray());
                    std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("c" + std::to_string(bombnumber--));
                    entity->AddComponent<BombComponent>(&libgraphic, round(pos.first), round(pos.second), compo->_entity->getComponent<Perso3DComponent>().get3DPerso().getPlayerID(), compo->_entity->getComponent<StatsComponent>().getRange(), 0);
                    for (auto &m : *_entities) {
                        if (m.second->hasComponent<Perso3DComponent>()) {
                            if (libgraphic.isPlayerIn(&entity->getComponent<BombComponent>(), &m.second->getComponent<Perso3DComponent>())) {
                                entity->getComponent<BombComponent>().pushIsThrough(m.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID(), true);
                            }
                        }
                    }
                }
                std::vector<std::pair<float, float>> vector;
                for (auto &second : *_entities) {
                    if (second.second->hasComponent<Perso3DComponent>() && second.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID() != e.second->getComponent<IA>().getType() && _alivePlayers[second.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()] != DEAD) {
                        vector.push_back(std::make_pair(libgraphic.moveXYZEntity(0, 0, 0, &second.second->getComponent<Perso3DComponent>()).first, libgraphic.moveXYZEntity(0, 0, 0, &second.second->getComponent<Perso3DComponent>()).second));
                    }
                }
                e.second->getComponent<IA>().plantBombeNearEnemies(vector);
                if (e.second->getComponent<IA>().getSafeMode() == false) {
                    e.second->getComponent<IA>().setPosTarget(vector);
                }
            }
        }
    }

    void EventManager::makeCharacterMove(IGraphic& libGraphic, int i, const std::string number, float time) {
        static int numberBomb = 0;
        int count_human = 0;
        int padID = 0;
        int countHuman = 0;
        static bool released = true;
        std::map<int, int> mapID;
        for (auto& e : this->_playerStates) {
            if (e == HUMAN) {
                mapID[countHuman] = padID;
                padID += 1;
            }
            else
                mapID[countHuman] = -1;
            countHuman += 1;
        }
        for (auto &e : *_entities) {
            std::pair<float, float> pos;
            bool isRunning = false;
            float oldX = 0;
            float oldZ = 0;
            int loop = 0;
            bool left = false;
            bool right = false;
            bool up = false;
            bool down = false;
            float x = 0;
            float z = 0;

            if (libGraphic.getIsPaused())
                return;
            if (e.second->hasComponent<Perso3DComponent>() && e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID() != i)
                continue;
            else if (e.second->hasComponent<Perso3DComponent>())
                pos = libGraphic.moveXYZEntity(0, 0, 0, &e.second->getComponent<Perso3DComponent>());
            if ((libGraphic.isMyKeyDown(_savedKeys["down" + number + "Button"])) ||
                    libGraphic.checkGamepadButton(mapID[i], 3) || (libGraphic.checkAxisButton(mapID[i], 1, 0.50, 1))) {
                if (e.second->hasComponent<Perso3DComponent>()) {
                    libGraphic.rotateAngle(0, 0, 0, &e.second->getComponent<Perso3DComponent>());
                    z += 1 * time;
                    oldZ -= 1 * time;
                    isRunning = true;
                    down = true;
                }
            }
            if ((libGraphic.isMyKeyDown(_savedKeys["mup" + number + "Button"])) ||
                    libGraphic.checkGamepadButton(mapID[i], 1) || (libGraphic.checkAxisButton(mapID[i], 1, -0.50, 0))) {
                if (e.second->hasComponent<Perso3DComponent>()) {
                    z += -1 * time;
                    libGraphic.rotateAngle(0, 0, 180, &e.second->getComponent<Perso3DComponent>());
                    oldZ += 1 * time;
                    isRunning = true;
                    up = true;
                }
            }
            if ((libGraphic.isMyKeyDown(_savedKeys["right" + number + "Button"])) ||
                    libGraphic.checkGamepadButton(mapID[i], 2) || (libGraphic.checkAxisButton(mapID[i], 0, 0.50, 1))) {
                if (e.second->hasComponent<Perso3DComponent>()) {
                    x += 1 * time;
                    libGraphic.rotateAngle(0, 0, -90, &e.second->getComponent<Perso3DComponent>());
                    isRunning = true;
                    oldX -= 1 * time;
                    right = true;
                }
            }
            if ((libGraphic.isMyKeyDown(_savedKeys["left" + number + "Button"])) ||
                    libGraphic.checkGamepadButton(mapID[i], 4) || (libGraphic.checkAxisButton(mapID[i], 0, -0.50, 0))) {
                if (e.second->hasComponent<Perso3DComponent>()) {
                    x += -1 * time;
                    libGraphic.rotateAngle(0, 0, 90, &e.second->getComponent<Perso3DComponent>());
                    oldX += 1 * time;
                    isRunning = true;
                    left = true;
                }
            }
            if (isRunning) {
                if (x != 0 && z != 0) {
                    x /= 2;
                    z /= 2;
                }
                pos = libGraphic.moveXYZEntity(x, 0, z, &e.second->getComponent<Perso3DComponent>());
            }
            for (auto &eTwo: *_entities) {
                if (eTwo.second->hasComponent<MapComponent>() && e.second->hasComponent<Perso3DComponent>())  {
                    if (libGraphic.checkPlayerColi(&eTwo.second->getComponent<MapComponent>(), &e.second->getComponent<Perso3DComponent>(), 0, 0))
                        loop++;
                }
                if (eTwo.second->hasComponent<BombComponent>() && e.second->hasComponent<Perso3DComponent>()) {
                    if (libGraphic.checkPlayerColiBomb(&eTwo.second->getComponent<BombComponent>(), &e.second->getComponent<Perso3DComponent>()))
                        loop++;
                }
            }
            if (isRunning && e.second->hasComponent<Perso3DComponent>()) {
                if (up && right)
                    libGraphic.rotateAngle(0, 0, -135, &e.second->getComponent<Perso3DComponent>());
                if (up && left)
                    libGraphic.rotateAngle(0, 0, 135, &e.second->getComponent<Perso3DComponent>());
                if (down && right)
                    libGraphic.rotateAngle(0, 0, -45, &e.second->getComponent<Perso3DComponent>());
                if (down && left)
                    libGraphic.rotateAngle(0, 0, 45, &e.second->getComponent<Perso3DComponent>());
            }
            if (loop != 0 && e.second->hasComponent<Perso3DComponent>()) {
                pos = libGraphic.moveXYZEntity(oldX, 0, oldZ, &e.second->getComponent<Perso3DComponent>());
            }
            if ((libGraphic.isMyKeyDown(_savedKeys["drop" + number + "Button"])) || libGraphic.isBombButtonPressed(mapID[i], GAMEPAD7)) {
                if (_exitPause)
                    return;
                if (e.second->hasComponent<Perso3DComponent>()) {
                    if (isRunning)
                        libGraphic.changeAnimation(MODEL_ACTION, &e.second->getComponent<Perso3DComponent>());
                    if (e.second->getComponent<StatsComponent>().getRelease()) {
                        e.second->getComponent<StatsComponent>().setRelease(false);
                        if (e.second->getComponent<StatsComponent>().putBomb()) {
                            std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("c" + std::to_string(numberBomb++));
                            entity->AddComponent<BombComponent>(&libGraphic, round(pos.first), round(pos.second), e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID(), e.second->getComponent<StatsComponent>().getRange(), 0);
                            for (auto& m : *_entities) {
                                if (m.second->hasComponent<Perso3DComponent>()) {
                                    if (libGraphic.isPlayerIn(&entity->getComponent<BombComponent>(), &m.second->getComponent<Perso3DComponent>())) {
                                        entity->getComponent<BombComponent>().pushIsThrough(m.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID(), true);
                                    }
                                }
                            }
                            MapComponent* map = nullptr;
                            for (auto& k : *_entities) {
                                if (k.second->hasComponent<MapComponent>() &&
                                    k.second->getComponent<MapComponent>().getType() == 0) {
                                    map = &k.second->getComponent<MapComponent>();
                                    break;
                                }
                            }
                            if (map == nullptr)
                                return;
                            map->getMyMapArray()[round(pos.second)][round(pos.first)] = 'X';
                        }
                        return;
                    }
                    e.second->getComponent<StatsComponent>().setRelease(false);
                    return;
                }
            }
            if (isRunning && e.second->hasComponent<AnimationComponent>())
                libGraphic.changeAnimation(MODEL_ACTION, &e.second->getComponent<Perso3DComponent>());
            else if (!isRunning && e.second->hasComponent<AnimationComponent>())
                libGraphic.changeAnimation(MODEL_IDDLE, &e.second->getComponent<Perso3DComponent>());
        }
        std::string saved_char;
        if (i == 0)
            saved_char = "character4";
        else if (i == 1)
            saved_char = "character3";
        else if (i == 2)
            saved_char = "character1";
        else if (i == 3)
            saved_char = "character2";
        for (auto &e : *_entities) {
            if (e.first == saved_char) {
                e.second->getComponent<StatsComponent>().setRelease(true);
                break;
            }
        }
        _exitPause = false;
    }

    void EventManager::addBonus(IGraphic &libgraphic, float x, float y) {
        static int bonusNumber = 0;
        int random = rand() % 4;
        std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("cc" + std::to_string(bonusNumber));
        bonusNumber++;
        if (random == 0)
            entity->AddComponent<BonusComponent>(&libgraphic, BonusComponent::DOUBLE, x, y);
        else if (random == 1)
            entity->AddComponent<BonusComponent>(&libgraphic, BonusComponent::RANGE, x, y);
        else if (random == 2)
            entity->AddComponent<BonusComponent>(&libgraphic, BonusComponent::SPEED, x, y);
        else
            entity->AddComponent<BonusComponent>(&libgraphic, BonusComponent::WALLCUBE, x, y);
        return;
    }

    void EventManager::makeBombExplode(IGraphic &libgraphic, Component *compo) {
        int random = 0;
        for (auto &e: *_entities) {
            if (e.second->hasComponent<IA>() && compo->_entity->getComponent<BombComponent>().getId() == e.second->getComponent<IA>().getType()) {
                    std::vector<std::pair<float, float>> vector;
                    for (auto &second : *_entities) {
                        if (second.second->hasComponent<Perso3DComponent>() && second.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID() != e.second->getComponent<IA>().getType() && _alivePlayers[second.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()] != DEAD) {
                            vector.push_back(std::make_pair(libgraphic.moveXYZEntity(0, 0, 0, &second.second->getComponent<Perso3DComponent>()).first, libgraphic.moveXYZEntity(0, 0, 0, &second.second->getComponent<Perso3DComponent>()).second));
                        }
                    }
                    e.second->getComponent<IA>().bombExplode(compo);
                    if (!e.second->getComponent<IA>().getSafeMode())
                        e.second->getComponent<IA>().setPosTarget(vector);
            }
        }
        Component *mapp = nullptr;
        for (auto &e : *_entities) {
            if (e.second->hasComponent<MapComponent>() && e.second->getComponent<MapComponent>().getType() == 0)
                mapp = &e.second->getComponent<MapComponent>();
        }
        if (mapp == nullptr)
            return;
        std::vector<std::pair<float, float>> pos;
        auto &e = compo->_entity->getComponent<BombComponent>();
        int x = e.getPosition().second;
        int y = e.getPosition().first;

        x = (x == 0) ? 1 : x;
        x = (x == 12) ? 11 : x;
        y = (y == 0) ? 1 : y;
        y = (y == 14) ? 13 : y;
        pos.push_back({(float)y, (float)x});
        std::pair<float, float> position_tmp;
        for (int i = 1; i <= compo->_entity->getComponent<BombComponent>().getRange(); ++i) {
            if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] == ' ' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] == 'X' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] == 'S') {
                position_tmp.first = y;
                position_tmp.second = x + i;
                for (auto &e: *_entities) {
                    if (e.second->hasComponent<BonusComponent>() && e.second->getComponent<BonusComponent>().getPos().first == position_tmp.second && e.second->getComponent<BonusComponent>().getPos().second == position_tmp.first)
                        e.second->destroy();
                }
                pos.push_back(position_tmp);
                continue;
            }
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] == '#')
                break;
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] == 'B') {
                mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] = ' ';
                position_tmp.first = y;
                position_tmp.second = x + i;
                pos.push_back(position_tmp);
                random = rand() % 4;
                if (random == 1) {
                    mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x + i][y] = 'S';
                    addBonus(libgraphic, x + i, y);
                }
                break;
            }
        }
        for (int i = 1; i <= compo->_entity->getComponent<BombComponent>().getRange(); ++i) {
            if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] == ' ' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] == 'X' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] == 'S') {
                position_tmp.first = y;
                position_tmp.second = x - i;
                for (auto &e: *_entities) {
                    if (e.second->hasComponent<BonusComponent>() && e.second->getComponent<BonusComponent>().getPos().first == position_tmp.second && e.second->getComponent<BonusComponent>().getPos().second == position_tmp.first)
                        e.second->destroy();
                }
                pos.push_back(position_tmp);
                continue;
            }
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] == '#')
                break;
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] == 'B') {
                mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] = ' ';
                position_tmp.first = y;
                position_tmp.second = x - i;
                pos.push_back(position_tmp);
                random = rand() % 4;
                if (random == 1) {
                    mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x - i][y] = 'S';
                    addBonus(libgraphic, x - i, y);
                }
                break;
            }
        }
        for (int i = 1; i <= compo->_entity->getComponent<BombComponent>().getRange(); ++i) {
            if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] == ' ' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] == 'X' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] == 'S') {
                position_tmp.first = y + i;
                position_tmp.second = x;
                for (auto &e: *_entities) {
                    if (e.second->hasComponent<BonusComponent>() && e.second->getComponent<BonusComponent>().getPos().first == position_tmp.second && e.second->getComponent<BonusComponent>().getPos().second == position_tmp.first)
                        e.second->destroy();
                }
                pos.push_back(position_tmp);
                continue;
            }
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] == '#')
                break;
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] == 'B') {
                mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] = ' ';
                position_tmp.first = y + i;
                position_tmp.second = x;
                pos.push_back(position_tmp);
                random = rand() % 4;
                if (random == 1) {
                    mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y + i] = 'S';
                    addBonus(libgraphic, x, y + i);
                }
                break;
            }
        }
        for (int i = 1; i <= compo->_entity->getComponent<BombComponent>().getRange(); ++i) {
            if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] == ' ' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] == 'X' || mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] == 'S') {
                position_tmp.first = y - i;
                position_tmp.second = x;
                for (auto &e: *_entities) {
                    if (e.second->hasComponent<BonusComponent>() && e.second->getComponent<BonusComponent>().getPos().first == position_tmp.second && e.second->getComponent<BonusComponent>().getPos().second == position_tmp.first)
                        e.second->destroy();
                }
                pos.push_back(position_tmp);
                continue;
            }
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] == '#')
                break;
            else if (mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] == 'B') {
                mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] = ' ';
                position_tmp.first = y - i;
                position_tmp.second = x;
                pos.push_back(position_tmp);
                random = rand() % 4;
                if (random == 1) {
                    mapp->_entity->getComponent<MapComponent>().getMyMapArray()[x][y - i] = 'S';
                    addBonus(libgraphic, x, y - i);
                }
                break;
            }
        }
        updateMap(mapp->_entity->getComponent<MapComponent>().getMyMapArray());
        e.setVector(pos);
        mapp->_entity->getComponent<MapComponent>().resetMap({1, 1, 1}, {0, 0, 0}, (char*)"");
        e.setHasExploded(true);
        for (auto &e : *_entities) {
            if (e.second->hasComponent<Perso3DComponent>()) {
                libgraphic.changeDeathAnimation((Component *)&e.second->getComponent<Perso3DComponent>(), pos, _alivePlayers, e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID(), _winOrder);
            }
        }
    }

    bool SelectionEventsGamepadMainMenu(SceneManager *_sceneManager, IGraphic &libGraphic, int input, std::map<std::string, std::shared_ptr<Entity>> *_entities) {
        static bool released = true;
        int number = 0;
        Vector saved = { 0 };
        if (input == 1) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        number = _entiti.second->getComponent<ButtonComponent>().getButtonNumber();
                        if (number == 1)
                            number = 2;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number - 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        if (input == 3) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        number = _entiti.second->getComponent<ButtonComponent>().getButtonNumber();
                        if (number == 5)
                            number = 4;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number + 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        released = true;
        return false;
    }

    bool SelectionEventsGamepadCharacterSelection(SceneManager* _sceneManager, IGraphic& libGraphic, int input, std::map<std::string, std::shared_ptr<Entity>>* _entities) {
        static bool released = true;
        int number = 0;
        Vector saved = { 0 };
        for (auto& e : *_entities) {
            if (e.second->hasComponent<MouseEventComponent>() && e.second->hasComponent<RectangleComponent>()
                && e.second->hasComponent<ButtonComponent>() && e.second->getComponent<ButtonComponent>().getState() == BUT_HOVER)
                number = e.second->getComponent<ButtonComponent>().getButtonNumber();
        }
        if (input == GAMEPAD4 && (number == 3 || number == 4)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number - 2) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        if (input == GAMEPAD2 && (number == 1 || number == 2)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number + 2) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        if (input == GAMEPAD1 && (number == 2 || number == 4)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        if (number == 1)
                            number = 2;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number - 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        if (input == GAMEPAD3 && (number == 1 || number == 3)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        if (number == 4)
                            number = 3;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number + 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        released = true;
        return false;
    }

    bool SelectionEventsGamepadPauseMenu(SceneManager* _sceneManager, IGraphic& libGraphic, int input, std::map<std::string, std::shared_ptr<Entity>>* _entities) {
        static bool released = true;
        int number = 0;
        Vector saved = { 0 };
        if (input == 1) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        number = _entiti.second->getComponent<ButtonComponent>().getButtonNumber();
                        if (number == 1)
                            number = 2;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number - 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        if (input == 3) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                        number = _entiti.second->getComponent<ButtonComponent>().getButtonNumber();
                        if (number == 4)
                            number = 3;
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == number + 1) {
                    if (released) {
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                        saved = _entiti.second->getComponent<PositionComponent>().getPosition();
                        break;
                    }
                }
            }
            if (released)
                libGraphic.moveBombSelection(saved);
            released = false;
            return true;
        }
        released = true;
        return false;
    }

    bool EventManager::gamepadEvents(IGraphic &libGraphic, float time) {
        int input = libGraphic.getGamepadInput();
        static bool released = true;
        static bool releasedPause = true;
        static bool enterInGame = false;

        if (_sceneManager->getCurrentScene()->getName() == "mainMenu" && SelectionEventsGamepadMainMenu(_sceneManager, libGraphic, input, _entities))
            return NO_EVENT;
        if (_sceneManager->getCurrentScene()->getName() == "characterSelectorMenu" && SelectionEventsGamepadCharacterSelection(_sceneManager, libGraphic, input, _entities))
            return NO_EVENT;
        if ((_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save") && libGraphic.getIsPaused() && SelectionEventsGamepadPauseMenu(_sceneManager, libGraphic, input, _entities))
            return NO_EVENT;
        if (_sceneManager->getCurrentScene()->getName() == "mainMenu" && input == GAMEPAD7) {
            if (released) {
                released = false;
                for (auto& _entiti : *_entities) {
                    if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                        && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                        if (_entiti.first == "playButton") {
                            for (int i = 0; i < 4; i++)
                                if (0 == i)
                                    _playerStates[i] = HUMAN;
                                else
                                    _playerStates[i] = COMPUTER;
                        }
                        if (detectEvent(_entiti, libGraphic))
                            return (true);
                    }
                }
            }
            released = false;
            return NO_EVENT;
        }
        if (_sceneManager->getCurrentScene()->getName() == "characterSelectorMenu" && (input == GAMEPAD9 || input == GAMEPAD11)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (released) {
                        released = false;
                        if (detectEvent(_entiti, libGraphic))
                            return (true);
                    }
                }
            }
            released = false;
            return NO_EVENT;
        }
        if (_sceneManager->getCurrentScene()->getName() == "characterSelectorMenu" && libGraphic.getGamepadAxisCharacterSelector(0, 5)) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getButtonNumber() == 5) {
                    if (detectEvent(_entiti, libGraphic)) {
                        enterInGame = true;
                        return (true);
                    }
                }
            }
        }
        if ((_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save" ) && libGraphic.getIsPaused() && input == GAMEPAD7) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER) {
                    if (releasedPause) {
                        releasedPause = false;
                        if (_entiti.first == "mainmenuButton" || _entiti.first == "playButton") {
                            libGraphic.setPause(false);
                            _exitPause = true;
                            for (auto& _entiti : *_entities) {
                                if (_entiti.second->hasComponent<PauseComponent>()) {
                                    _entiti.second->getComponent<PauseComponent>().setIsPause(false);
                                }
                            }
                        }
                        if (_entiti.second->getComponent<ButtonComponent>().getButtonNumber() != 1 && detectEvent(_entiti, libGraphic))
                            return (true);
                    }
                }
            }
            releasedPause = false;
            return NO_EVENT;
        }
        if (_sceneManager->getCurrentScene()->getName() == "winMenu" && input == GAMEPAD7) {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<MouseEventComponent>()) {
                    if (released) {
                        released = false;
                        if (detectEvent(_entiti, libGraphic)) {
                            return (true);
                        }
                    }
                }
            }
             return (true);
        }
        if (input == GAMEPAD6 && !_isInGame) {
            if (_sceneManager->getCurrentScene()->getName() == "characterSelectorMenu")
                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
            else if (_sceneManager->getCurrentScene()->getName() == "settingsMenu")
                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
            else if (_sceneManager->getCurrentScene()->getName() == "howToPlay")
                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
            else if (_sceneManager->getCurrentScene()->getName() == "loadMenu")
                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
        }
        if ((input == GAMEPAD15) && (_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save") && enterInGame == false) {
            if (releasedPause) {
                releasedPause = false;
                if (libGraphic.getIsPaused()) {
                    libGraphic.setPause(false);
                    _exitPause = true;
                }
                else if (!libGraphic.getIsPaused())
                    libGraphic.setPause(true);
                for (auto& _entiti : *_entities) {
                    if (_entiti.second->hasComponent<PauseComponent>()) {
                        if (libGraphic.getIsPaused())
                            _entiti.second->getComponent<PauseComponent>().setIsPause(true);
                        else if (!libGraphic.getIsPaused())
                            _entiti.second->getComponent<PauseComponent>().setIsPause(false);
                    }
                }
            }
            releasedPause = false;
            return NO_EVENT;
        }
        enterInGame = false;
        releasedPause = true;
        released = true;
        return (false);
    }

    Ikey EventManager::keyboardEvents(IGraphic& libGraphic, float time) {
        static bool releasedPause = true;
        Ikey input = libGraphic.getInput();

        if (_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save") {
            for (auto &e: *_entities) {
                if (e.second->hasComponent<StatsComponent>()) {
                    if (e.second->getComponent<StatsComponent>().getReset()) {
                        std::pair<float, float> pos = e.second->getComponent<StatsComponent>().getLastPos();
                        e.second->getComponent<StatsComponent>().setReset(false);
                        libGraphic.setXYZEntity(pos.first, 0, pos.second, &e.second->getComponent<StatsComponent>());
                        for (auto &p :*_entities) {
                            if (p.second->hasComponent<IA>()) {
                                if (p.second->getComponent<IA>().getType() == e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()) {
                                    p.second->getComponent<IA>().setTravelWall(false);
                                    p.second->getComponent<IA>().setPosIA(pos.first, pos.second);
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 4 && (_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "howToPlay" || _sceneManager->getCurrentScene()->getName() == "save"); i++) {
            if (i == 0 && _playerStates[i] == HUMAN && _alivePlayers[i] != DEAD)
                makeCharacterMove(libGraphic, i, "One", time);
            else if (i == 1 && _playerStates[i] == HUMAN && _alivePlayers[i] != DEAD)
                makeCharacterMove(libGraphic, i, "Two", time);
            else if (i == 2 && _playerStates[i] == HUMAN && _alivePlayers[i] != DEAD)
                makeCharacterMove(libGraphic, i, "Three", time);
            else if (i == 3 && _playerStates[i] == HUMAN && _alivePlayers[i] != DEAD)
                makeCharacterMove(libGraphic, i, "Four", time);
        }
        if ((input == P) && (_sceneManager->getCurrentScene()->getName() == "game" || _sceneManager->getCurrentScene()->getName() == "save")) {
            if (releasedPause) {
                releasedPause = false;
                if (libGraphic.getIsPaused()) {
                    libGraphic.setPause(false);
                    _exitPause = true;
                }
                else if (!libGraphic.getIsPaused())
                    libGraphic.setPause(true);
                for (auto& _entiti : *_entities) {
                    if (_entiti.second->hasComponent<PauseComponent>()) {
                        if (libGraphic.getIsPaused())
                            _entiti.second->getComponent<PauseComponent>().setIsPause(true);
                        else if (!libGraphic.getIsPaused())
                            _entiti.second->getComponent<PauseComponent>().setIsPause(false);
                    }
                }
                releasedPause = false;
                return NO_EVENT;
            }
        }
        if (input == WINDOWCLOSE)
            libGraphic.setClose(true);
        makeIAMove(libGraphic, time);
        for (auto & _entitie : *_entities) {
            if (_entitie.second->hasComponent<BonusComponent>()) {
                for (auto &k : *_entities) {
                    if (k.second->hasComponent<Perso3DComponent>()) {
                        if (libGraphic.BonusHitbox(&k.second->getComponent<Perso3DComponent>(), std::make_pair(_entitie.second->getComponent<BonusComponent>().getPos().second, _entitie.second->getComponent<BonusComponent>().getPos().first))) {
                            if (_entitie.second->getComponent<BonusComponent>().getIsUsed() == false) {
                                _entitie.second->getComponent<BonusComponent>().setIsUsed();
                                if (_entitie.second->getComponent<BonusComponent>().getType() == BonusComponent::DOUBLE) {
                                    k.second->getComponent<StatsComponent>().addNumberMaxBomb();
                                } else if (_entitie.second->getComponent<BonusComponent>().getType() == BonusComponent::RANGE) {
                                    k.second->getComponent<StatsComponent>().addRange(1);
                                } else if (_entitie.second->getComponent<BonusComponent>().getType() == BonusComponent::SPEED) {
                                    k.second->getComponent<StatsComponent>().addSpeed(0.1);
                                } else if (_entitie.second->getComponent<BonusComponent>().getType() == BonusComponent::WALLCUBE) {
                                    std::pair<float, float> pos = libGraphic.moveXYZEntity(0, 0, 0, &k.second->getComponent<Perso3DComponent>());
                                    for (auto &p :*_entities) {
                                        if (p.second->hasComponent<IA>()) {
                                            if (p.second->getComponent<IA>().getType() == k.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()) {
                                                p.second->getComponent<IA>().setTravelWall(true);
                                            }
                                        }
                                    }
                                    k.second->getComponent<StatsComponent>().setLastPos(pos.first, pos.second);
                                    k.second->getComponent<StatsComponent>().setCanThrough(true);
                                }
                            }
                            _entitie.second->destroy();
                            MapComponent *map = nullptr;
                            for (auto &c : *_entities) {
                                if (c.second->hasComponent<MapComponent>() && c.second->getComponent<MapComponent>().getType() == 0) {
                                    map = &c.second->getComponent<MapComponent>();
                                    break;
                                }
                            }
                            if (map == nullptr)
                                break;
                            else {
                                map->getMyMapArray()[_entitie.second->getComponent<BonusComponent>().getPos().first][_entitie.second->getComponent<BonusComponent>().getPos().second] = ' ';
                            }
                        }
                    }
                }
            }
            if (_entitie.second->hasComponent<BombComponent>() && _entitie.second->getComponent<BombComponent>().getExplose() && _entitie.second->getComponent<BombComponent>().gethasExploded() == false) {
                makeBombExplode(libGraphic, (Component *)&_entitie.second->getComponent<BombComponent>());
#if ! defined(__APPLE__)
                libGraphic.makeSoundExplosion();
#endif
            }
            if (_entitie.second->hasComponent<BombComponent>() && _entitie.second->getComponent<BombComponent>().getExplose() && _entitie.second->getComponent<BombComponent>().getIsExplosing()) {
                MapComponent *map = nullptr;
                for (auto &k : *_entities) {
                    if (k.second->hasComponent<MapComponent>() && k.second->getComponent<MapComponent>().getType() == 0) {
                        map = &k.second->getComponent<MapComponent>();
                        break;
                    }
                }
                map->getMyMapArray()[round(_entitie.second->getComponent<BombComponent>().getPosition().second)][round(_entitie.second->getComponent<BombComponent>().getPosition().first)] = ' ';
                _entitie.second->destroy();
            }
            if (_entitie.second->hasComponent<KeyboardEventComponent>()) {
                if (input != NO_EVENT && libGraphic.getInputAsString(input) != "P") {
                    if (_entitie.second->getComponent<Indie::KeyboardEventComponent>().getState() == 1) {
                        auto &e = _entitie.second->getComponent<Indie::KeyboardEventComponent>();
                        if (input != WINDOWCLOSE && input != UNKNOWN) {
                            if (isThisKeyBindedAlready(input)) {
                                e.setState(0);
                                continue;
                            }
                            _entitie.second->getComponent<Indie::TextComponent>().setText((char *)libGraphic.getInputAsString(input).c_str());
                            _savedKeys[_entitie.first] = input;
                        }
                        e.setState(0);
                    }
                }
            }
        }
        bool isThereBomb = false;
        bool isThereIA = false;
        for (auto &e: *_entities) {
            if (e.second->hasComponent<BombComponent>())
                isThereBomb = true;
            if (e.second->hasComponent<IA>())
                isThereIA = true;
        }
        releasedPause = true;
        return NO_EVENT;
    }

    void EventManager::setSceneManager(SceneManager *sceneManager) {
        _sceneManager = sceneManager;
    }

    void EventManager::setMusic(float music, IGraphic& graph) {
        graph.setMusicVolume(music);
        for (auto & _entitie : *_entities) {
            if (_entitie.first == "musicBarValue") {
                auto &e = _entitie.second->getComponent<TextComponent>();
                e.setText((char*)std::to_string(graph.getMusicVolume()).c_str());
                return;
            }
        }
    }

    void EventManager::setSound(float sound, IGraphic& graph) {
        graph.setSoundVolume(sound);
        for (auto & _entitie : *_entities) {
            if (_entitie.first == "soundBarValue") {
                auto &e = _entitie.second->getComponent<TextComponent>();
                e.setText((char*)std::to_string(graph.getSoundVolume()).c_str());
                return;
            }
        }
    }

    bool EventManager::detectEvent(std::pair<const std::string, std::shared_ptr<Entity>> &entity, IGraphic &libGraphic) {

        Json::Value myEvents;
        if (_sceneManager->getCurrentScene()->getName() == "save")
            myEvents = _jsonEvents[_sceneManager->getCurrentScene()->getName()]["game"]["entities"];
        else
            myEvents = _jsonEvents[_sceneManager->getCurrentScene()->getName()][_sceneManager->getCurrentScene()->getName()]["entities"];
        for (int index = 0; index < myEvents.size(); index++) {
            Json::Value Events = myEvents[index]["events"];
            if (myEvents[index]["name"] == entity.first) {
                for (int indexTwo = 0; indexTwo < myEvents.size(); indexTwo++) {
                    if (Events[indexTwo]["name"] == "save") {
                        saveTheGame(libGraphic);
                    }
                    if (Events[indexTwo]["name"] == "music") {
                        setMusic(Events[indexTwo]["value"].asInt(), libGraphic);
                    }
                    if (Events[indexTwo]["name"] == "sound") {
                        setSound(Events[indexTwo]["value"].asInt(), libGraphic);
                    }
                    if (Events[indexTwo]["name"] == "switchScene") {
                        if (_sceneManager->getCurrentScene()->getName() == "mainMenu" && Events[indexTwo]["id"] == "settingsMenu") {
                            libGraphic.menuToSettings();
                        }
                        _scrollValue = 0;
                        if (Events[indexTwo]["id"] == "howToPlay") {
                            _playerStates[0] = HUMAN;
                            _alivePlayers[0] = ALIVE;
                        }
                        if (Events[indexTwo]["id"] == "save") {
                            std::ifstream fileOne("../jsonScenes/save.json");
                            std::ifstream fileTwo("../save/savemap.txt");

                            if (!fileOne.is_open() || !fileTwo.is_open()) {
                                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
                                return (true);
                            }
                            fileOne.close();
                            fileTwo.close();
                        }
                        _sceneManager->switchScene(&libGraphic, (int)_sceneManager->_sceneLinks[Events[indexTwo]["id"].asString()]);
                        if (_sceneManager->getCurrentScene()->getName() == "settingsMenu") {
                            for (auto &t: *_entities) {
                                for (auto it = _savedKeys.begin(); it != _savedKeys.end(); it++) {
                                    if (std::strcmp((*it).first.c_str(), t.first.c_str()) == 0) {
                                        if (t.second->hasComponent<TextComponent>() ){
                                            t.second->getComponent<TextComponent>().setText((char*)libGraphic.getInputAsString((*it).second).c_str());
                                        }
                                    } else if (t.first == "musicBarValue") {
                                        t.second->getComponent<TextComponent>().setText(((char*)std::to_string(libGraphic.getMusicVolume()).c_str()));
                                    } else if (t.first == "soundBarValue") {
                                        t.second->getComponent<TextComponent>().setText(((char*)std::to_string(libGraphic.getSoundVolume()).c_str()));
                                    }
                                }
                            }
                        }
                        _jsonEvents[_sceneManager->getCurrentScene()->getName()][_sceneManager->getCurrentScene()->getName()]["entities"];
                        if (_sceneManager->getCurrentScene()->getName().find("game") != std::string::npos || _sceneManager->getCurrentScene()->getName().find("save") != std::string::npos) {
                            Json::Value root;
                            Json::Reader *reader = new Json::Reader();
                            std::ifstream myFile("../jsonScenes/save.json");
                            if (!myFile.is_open()) {
                                _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
                                return (true);
                            }
                            if (_sceneManager->getCurrentScene()->getName() == "save")
                                reader->parse(myFile, root);
                            Component *mapp = nullptr;
                            for (auto &e : *_entities) {
                                if (e.second->hasComponent<MapComponent>() && e.second->getComponent<MapComponent>().getType() == 0 && _sceneManager->getCurrentScene()->getName() == "save") {
                                    std::array<std::string, 13> mymap;
                                    std::ifstream file("../save/savemap.txt");
                                    if (!file.is_open()) {
                                        _sceneManager->switchScene(&libGraphic, _sceneManager->_sceneLinks["mainMenu"]);
                                        return (true);
                                    }
                                    std::string line;
                                    int index = 0;
                                    while (getline(file, line)) {
                                        if (line.size() > 5) {
                                            mymap[index] = line;
                                            index++;
                                        }
                                    }
                                    file.close();
                                    e.second->getComponent<MapComponent>().setMap(mymap);
                                    updateMap(mymap);
                                    mapp = &e.second->getComponent<MapComponent>();
                                    mapp->_entity->getComponent<MapComponent>().resetMap({1, 1, 1}, {0, 0, 0}, (char*)"");
                                } else if (e.second->hasComponent<MapComponent>() && e.second->getComponent<MapComponent>().getType() == 0)
                                    mapp = &e.second->getComponent<MapComponent>();
                            }
                            if (_sceneManager->getCurrentScene()->getName() == "save") {
                                for (int i = 0; i < root["IAPlayers"].size(); i++) {
                                    _playerStates[root["IAPlayers"][i].asInt()] = COMPUTER;
                                }
                            }
                            for (int i = 0; i < 4 && _sceneManager->getCurrentScene()->getName() == "game"; i++) {
                                if (_playerStates[i] == COMPUTER) {
                                    std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("IA" + std::to_string(i));
                                    if (i == 0)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(1.0f, 11.0f), std::make_pair(5.0f, 5.0f), i);
                                    if (i == 1)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(13.0f, 11.0f), std::make_pair(5.0f, 5.0f), i);
                                    if (i == 2)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(13.0f, 1.0f) ,std::make_pair(5.0f, 5.0f), i);
                                    if (i == 3)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(1.0f, 1.0f) ,std::make_pair(5.0f, 5.0f), i);
                                }
                            }
                            for (int i = 0; i < 4 && _sceneManager->getCurrentScene()->getName() == "save"; i++) {
                                if (_playerStates[i] == COMPUTER) {
                                    std::pair<float, float> IApos;
                                    for (int k = 0; k < root["game"]["entities"].size(); k++) {
                                        for (int x = 0; x < root["game"]["entities"][k]["components"].size(); x++) {
                                            if (root["game"]["entities"][k]["components"][x]["name"] == "PersoComponent" && i == root["game"]["entities"][k]["components"][x]["id"].asInt()) {
                                                IApos.first = round(root["game"]["entities"][k]["components"][x]["positionX"].asFloat());
                                                IApos.second = round(root["game"]["entities"][k]["components"][x]["positionZ"].asFloat());
                                            }
                                        }
                                    }
                                    std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("IA" + std::to_string(i));
                                    if (i == 0)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(IApos.first, IApos.second), std::make_pair(5.0f, 5.0f), i);
                                    if (i == 1)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(IApos.first, IApos.second), std::make_pair(5.0f, 5.0f), i);
                                    if (i == 2)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(IApos.first, IApos.second) ,std::make_pair(5.0f, 5.0f), i);
                                    if (i == 3)
                                        entity->AddComponent<IA>(&libGraphic, mapp->_entity->getComponent<MapComponent>().getMyMapArray(), std::make_pair(IApos.first, IApos.second) ,std::make_pair(5.0f, 5.0f), i);
                                }
                            }
                            if (_sceneManager->getCurrentScene()->getName() == "game") {
                                _alivePlayers[0] = ALIVE;
                                _alivePlayers[1] = ALIVE;
                                _alivePlayers[2] = ALIVE;
                                _alivePlayers[3] = ALIVE;
                            }
                            if (_sceneManager->getCurrentScene()->getName() == "save") {
                                _alivePlayers[0] = ALIVE;
                                _alivePlayers[1] = ALIVE;
                                _alivePlayers[2] = ALIVE;
                                _alivePlayers[3] = ALIVE;
                                int i = 0;
                                for (auto it : root["bombs"]) {
                                    i++;
                                    std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("cccc" + std::to_string(i++));
                                    entity->AddComponent<BombComponent>(&libGraphic, it["x"].asFloat(), it["z"].asFloat(), it["id"].asInt(), it["range"].asInt(), it["time"].asFloat());
                                }
                                for (auto it : root["bonus"]) {
                                    i++;
                                    std::shared_ptr<Entity> entity = _sceneManager->getCurrentScene()->getManager()->addEntity("cccccc" + std::to_string(i++));
                                    entity->AddComponent<BonusComponent>(&libGraphic, (BonusComponent::TypeBonus)it["type"].asInt(), it["x"].asFloat(), it["z"].asFloat());
                                }
                                _winOrder.clear();
                                for (int i = 0; i < root["deadPlayers"].size(); i++) {
                                    _alivePlayers[root["deadPlayers"][i].asInt()] = DEAD;
                                    _winOrder.push_back(root["deadPlayers"][i].asInt());
                                }
                                for (auto &e: *_entities) {
                                    if (e.second->hasComponent<BombComponent>()) {
                                        for (auto &k : *_entities) {
                                            if (k.second->hasComponent<IA>() && k.second->getComponent<IA>().getType() == e.second->getComponent<BombComponent>().getId()) {
                                                k.second->getComponent<IA>().setPosBombPlayer(std::make_pair(e.second->getComponent<BombComponent>().getPosition().first, e.second->getComponent<BombComponent>().getPosition().second));
                                                k.second->getComponent<IA>().setPlantBomb(false);
                                                k.second->getComponent<IA>().setSafeMode(true);
                                                k.second->getComponent<IA>().addSavePos();
                                                k.second->getComponent<IA>().findSafePos();
                                            }
                                        }
                                    }
                                    if (e.second->hasComponent<Perso3DComponent>()) {
                                        if (_alivePlayers[e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()] == DEAD)
                                            libGraphic.setPersoToSky(&e.second->getComponent<Perso3DComponent>());
                                    }
                                }
                            } else {
                                _winOrder.clear();
                            }
                        }
                        for (auto & e : *_entities) {
                            if (e.second->hasComponent<TextureComponent>() && (e.first == "choosePlayerOneButton" || e.first == "choosePlayerTwoButton" || e.first == "choosePlayerThreeButton" || e.first == "choosePlayerFourButton")) {
                                auto &compo = e.second->getComponent<TextureComponent>().getTexture();
                                if (e.first.find("One") != std::string::npos) {
                                    if (_playerStates[1] == HUMAN)
                                        compo.setTexture("../assets/img_player_1.png");
                                    else
                                        compo.setTexture("../assets/img_ai_2.png");
                                }
                                if (e.first.find("Two") != std::string::npos) {
                                    if (_playerStates[3] == HUMAN)
                                        compo.setTexture("../assets/img_player_1.png");
                                    else
                                        compo.setTexture("../assets/img_ai_2.png");
                                }
                                if (e.first.find("Three") != std::string::npos) {
                                    if (_playerStates[0] == HUMAN)
                                        compo.setTexture("../assets/img_player_1.png");
                                    else
                                        compo.setTexture("../assets/img_ai_2.png");
                                }
                                if (e.first.find("Four") != std::string::npos) {
                                    if (_playerStates[2] == HUMAN)
                                        compo.setTexture("../assets/img_player_1.png");
                                    else
                                        compo.setTexture("../assets/img_ai_2.png");
                                }
                            }
                        }
                        this->getClock().reset();
                        return (true);
                    }
                    if (Events[indexTwo]["name"] == "quit") {
                        libGraphic.setClose(true);
                    }
                    if (Events[indexTwo]["name"] == "changeButton") {
                        auto &compo = entity.second->getComponent<Indie::KeyboardEventComponent>();
                        compo.setState(1);
                    }
                    if (Events[indexTwo]["name"] == "choosePlayer") {
                        auto &compo = entity.second->getComponent<TextureComponent>().getTexture();
                        for (int i = 0; i < 4; i++) {
                            if (i == Events[indexTwo]["numPlayer"].asInt()) {
                                if (_playerStates[i] == HUMAN) {
                                    _playerStates[i] = COMPUTER;
                                    compo.setTexture(&Events[indexTwo]["filepathIA"].asString()[0]);
                                } else {
                                    _playerStates[i] = HUMAN;
                                    compo.setTexture(&Events[indexTwo]["filepathPlayer"].asString()[0]);
                                }
                            }
                        }
                    }
                    if (Events[indexTwo]["name"] == "changeScale") {
                        libGraphic.closeMyWindow();
                        libGraphic.setScale(Events[indexTwo]["size"].asFloat());
                        libGraphic.openMyWindow(Events[indexTwo]["size"].asFloat());
                        libGraphic.recreateLibrary();
                        _sceneManager->switchScene(&libGraphic, (int)_sceneManager->_sceneLinks[Events[indexTwo]["id"].asString()]);
                        if (_sceneManager->getCurrentScene()->getName() == "settingsMenu") {
                            for (auto &t: *_entities) {
                                for (auto it = _savedKeys.begin(); it != _savedKeys.end(); it++) {
                                    if (std::strcmp((*it).first.c_str(), t.first.c_str()) == 0) {
                                        if (t.second->hasComponent<TextComponent>() ){
                                            t.second->getComponent<TextComponent>().setText((char*)libGraphic.getInputAsString((*it).second).c_str());
                                        }
                                    }
                                }
                            }
                        }
                        for (auto & _entitie : *_entities) {
                            if (_entitie.second->hasComponent<RectangleComponent>()) {
                                auto &e = _entitie.second->getComponent<RectangleComponent>();
                                e.setScale(Events[indexTwo]["size"].asFloat());
                                e.setRectangleHeight(e.getRectangleHeight() * Events[indexTwo]["size"].asFloat());
                                e.setRectangleWidth(e.getRectangleWidth() * Events[indexTwo]["size"].asFloat());
                            }
                            if (_entitie.second->hasComponent<TextComponent>()) {
                                auto &e = _entitie.second->getComponent<TextComponent>();
                                e.setScale(Events[indexTwo]["size"].asFloat());
                            }
                        }
                        return (true);
                    }
                }
            }
        }
        return (false);
    }

    void EventManager::saveTheGame(IGraphic &libgraphic) {
        std::ofstream ofs;
        Json::Value root;
        Json::Reader reader;
        Json::StreamWriterBuilder builder;

        // Set Builder settings.

        builder["indentation"] = "    ";
        builder["commentStyle"] = "None";
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

        // open Pattern

        std::ifstream pattern("./../jsonScenes/pattern.json");
        if (!pattern.is_open()) {
            std::cerr << "pattern couldnt be opened" << std::endl;
            _sceneManager->switchScene(&libgraphic, _sceneManager->_sceneLinks["mainMenu"]);
            return;
        }

        reader.parse(pattern, root);

        // open new save;

        ofs.open("./../jsonScenes/save.json", std::ios::out | std::ios::trunc);
        if (!ofs.is_open()) {
            std::cerr << "save couldnt be opened" << std::endl;
            _sceneManager->switchScene(&libgraphic, _sceneManager->_sceneLinks["mainMenu"]);
            return;
        }

        // Start checking for new values;   ////////////////////////////////////


        // Check for deadPlayers;
        Json::Value deadPlayers = Json::arrayValue;
        for (int i = 0; i < 4; i++) {
            if (_alivePlayers[i] == DEAD)
                deadPlayers.append(i);
        }
        root["deadPlayers"] = deadPlayers;

        // Check for ID IA;

        Json::Value IAPlayers = Json::arrayValue;
        for (int i = 0; i < 4; i++) {
            if (_playerStates[i] != HUMAN) {
                IAPlayers.append(i);
            }
        }
        root["IAPlayers"] = IAPlayers;

        /*
        *   Change StatsValues;
        */
        Json::Value Bombs = Json::arrayValue;
        Json::Value Bonus = Json::arrayValue;
        for (auto &e : *_entities) {
            if (e.second->hasComponent<Perso3DComponent>() && e.second->hasComponent<StatsComponent>()) {
                for (int i = 0; i < root["game"]["entities"].size(); i++) {
                    for (int x = 0; x < root["game"]["entities"][i]["components"].size(); x++) {
                        if (root["game"]["entities"][i]["components"][x]["name"] == "PersoComponent" && root["game"]["entities"][i]["components"][x]["id"] == e.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()) {
                            std::pair<float, float> pos = libgraphic.moveXYZEntity(0, 0, 0, &e.second->getComponent<Perso3DComponent>());
                            root["game"]["entities"][i]["components"][x]["positionX"] = pos.first;
                            root["game"]["entities"][i]["components"][x]["positionY"] = 0.4;
                            root["game"]["entities"][i]["components"][x]["positionZ"] = pos.second;
                            for (int s = 0; s < root["game"]["entities"][i]["components"].size(); s++) {
                                if (root["game"]["entities"][i]["components"][s]["name"] == "StatsComponent") {
                                    root["game"]["entities"][i]["components"][s]["maxBombs"] = e.second->getComponent<StatsComponent>().getMaxBombs();
                                    root["game"]["entities"][i]["components"][s]["actualBombs"] = e.second->getComponent<StatsComponent>().getActualBombs();
                                    root["game"]["entities"][i]["components"][s]["speed"] = e.second->getComponent<StatsComponent>().getSpeed();
                                    root["game"]["entities"][i]["components"][s]["range"] = e.second->getComponent<StatsComponent>().getRange();
                                }
                            }
                        }
                    }
                }
            }
            if (e.second->hasComponent<BombComponent>()) {
                BombComponent b = e.second->getComponent<BombComponent>();
                Json::Value Bomb = Json::objectValue;
                Bomb["x"] = b.getPosition().first;
                Bomb["z"] = b.getPosition().second;
                Bomb["range"] = b.getRange();
                Bomb["id"] = b.getId();
                Bomb["time"] = b.getTime();
                Bombs.append(Bomb);
            }
            if (e.second->hasComponent<BonusComponent>()) {
                BonusComponent b = e.second->getComponent<BonusComponent>();
                Json::Value bonus = Json::objectValue;
                bonus["x"] = b.getPos().first;
                bonus["z"] = b.getPos().second;
                bonus["type"] = b.getType();
                Bonus.append(bonus);
            }
            if (e.second->hasComponent<MapComponent>() && e.second->getComponent<MapComponent>().getType() == 0) {
                std::ifstream filetxt("../save/savemap.txt", std::ifstream::out | std::ifstream::trunc);
                std::string content = "";

                if (!filetxt.is_open()) {
                    std::cerr << "error opening txt map" << std::endl;
                    exit (84);
                }
                for (int i = 0; i < e.second->getComponent<MapComponent>().getMyMapArray().size(); i++) {
                    content += e.second->getComponent<MapComponent>().getMyMapArray()[i] + "\n";
                }
                filetxt.close();
                std::ofstream filetowrite("../save/savemap.txt");
                filetowrite << content;
            }
        }
        root["bonus"] = Bonus;
        root["bombs"] = Bombs;
        writer->write(root, &ofs);
        pattern.close();
        ofs.close();
        return;
    }

    void EventManager::detectScroll(std::pair<const std::string, std::shared_ptr<Entity>> &entity, IGraphic &libGraphic) {
        Json::Value myEvents = _jsonEvents[_sceneManager->getCurrentScene()->getName()][_sceneManager->getCurrentScene()->getName()]["entities"];
        float scroll = 0;

        if (_scrollValue > 0) {
            scroll = 60;
        } else if (_scrollValue < 0) {
            scroll = -60;
        }
        for (int index = 0; index < myEvents.size(); index++) {
            Json::Value Events = myEvents[index]["events"];
            if (myEvents[index]["name"] == entity.first) {
                for (int indexTwo = 0; indexTwo < myEvents.size(); indexTwo++) {
                    if (Events[indexTwo]["name"] == "scrallable")  {
                        auto &pos = entity.second->getComponent<Indie::PositionComponent>();
                        Vector vec;
                        vec.x = pos.getPosition().x;
                        if ((pos.getPosition().y + scroll) > pos.getSavedposition()) {
                            if (entity.second->hasComponent<TextComponent>()) {
                                auto &rec = entity.second->getComponent<RectangleComponent>();
                                vec.y = pos.getSavedposition() - rec.getRectangleHeight();
                            } else
                                vec.y = pos.getSavedposition();
                            pos.setPosition(vec);
                            continue;
                        }
                        if (_sceneManager->getCurrentScene()->getName() == "settingsMenu") {
                            if ((pos.getPosition().y + scroll) - pos.getSavedposition() < -2200) {
                                _scrollValue = 0;
                               break;
                            }
                        }
                        if (_sceneManager->getCurrentScene()->getName() == "howToPlay") {
                            if ((pos.getPosition().y + scroll) - pos.getSavedposition() < -1000) {
                                _scrollValue = 0;
                               break;
                            }
                        }
                        vec.y = pos.getPosition().y + scroll;
                        pos.setPosition(vec);
                    }
                }
            }
        }
    }

    bool EventManager::mouseEvents(IGraphic& libGraphic, float time) {
        (void)time;
        _scrollValue += libGraphic.getWheel() * 6;
        if (_winOrder.size() >= 3 && _sceneManager->getCurrentScene()->getName() != "winMenu") {
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<Perso3DComponent>()) {
                    if (detectEvent(_entiti, libGraphic)) {
                        return (true);
                    }
                }
            }
            return (true);
        }
        if (_winOrder.size() >= 3 && _sceneManager->getCurrentScene()->getName() == "winMenu") {
            int i = 1;
            for (auto it = _winOrder.crbegin() ; it != _winOrder.crend(); ++it) {
                for (auto& _entiti : *_entities) {
                    if (_entiti.second->hasComponent<Perso3DComponent>()) {
                        if (*it == _entiti.second->getComponent<Perso3DComponent>().get3DPerso().getPlayerID()) {
                            _entiti.second->getComponent<Perso3DComponent>().get3DPerso().setWinID(i);
                        i += 1;
                        }
                    }
                }
            }
            for (auto& _entiti : *_entities) {
                if (_entiti.second->hasComponent<Perso3DComponent>() && _entiti.second->getComponent<Perso3DComponent>().get3DPerso().getWinID() == 0) {
                        _entiti.second->getComponent<Perso3DComponent>().get3DPerso().setWinID(0);
                        break;
                }
            }
            _winOrder.clear();
            return (true);
        }
        if (_scrollValue > 0)
            _scrollValue--;
        else if (_scrollValue < 0)
            _scrollValue++;
        for (auto & _entitie : *_entities) {
            if (_scrollValue != 0) {
                detectScroll(_entitie, libGraphic);
            }
            if (_entitie.second->hasComponent<MouseEventComponent>() && _entitie.second->hasComponent<RectangleComponent>()
                    && _entitie.second->hasComponent<ButtonComponent>() && _sceneManager->getCurrentScene()->getName() != "game" ||
                        _entitie.second->hasComponent<MouseEventComponent>() &&
                        _entitie.second->hasComponent<RectangleComponent>() && _entitie.second->hasComponent<ButtonComponent>() &&
                    (_sceneManager->getCurrentScene()->getName() == "game" && libGraphic.getIsPaused())
                ||
                _entitie.second->hasComponent<MouseEventComponent>() &&
                    _entitie.second->hasComponent<RectangleComponent>() && _entitie.second->hasComponent<ButtonComponent>() &&
                    (_sceneManager->getCurrentScene()->getName() == "save" && libGraphic.getIsPaused())) {
                if (libGraphic.checkMouseCollision(_entitie.second->getComponent<RectangleComponent>().getRectangle())) {
                    for (auto & _entiti : *_entities) {
                        if (_entiti.second->hasComponent<MouseEventComponent>() && _entiti.second->hasComponent<RectangleComponent>()
                    && _entiti.second->hasComponent<ButtonComponent>() && _entiti.second->getComponent<ButtonComponent>().getState() == BUT_HOVER)
                        _entiti.second->getComponent<ButtonComponent>().setState(BUT_NO_EVENT);
                    }
                    _entitie.second->getComponent<ButtonComponent>().setState(BUT_HOVER);
                    if (IsMouseButtonPressed(0)) {
                        if (_entitie.second->getComponent<ButtonComponent>().getButtonNumber() == 1 || _entitie.second->getComponent<ButtonComponent>().getButtonNumber() == 3) {
                            for (auto& _entiti : *_entities) {
                                libGraphic.setPause(false);
                                if (_entiti.second->hasComponent<PauseComponent>()) {
                                    if (!libGraphic.getIsPaused())
                                        _entiti.second->getComponent<PauseComponent>().setIsPause(false);
                                }
                            }
                        }
                        _entitie.second->getComponent<ButtonComponent>().setState(BUT_CLICK);
                        if(detectEvent(_entitie, libGraphic))
                            return (true);
                    }
                }
            }
        }
        return (false);
    }

    void EventManager::addEvents(const std::string &filename, std::map<std::string, Json::Value> &myMap)
    {
        Json::Value root;
        Json::Reader reader;
        std::ifstream myFile;
        myFile.open(("../jsonScenes/" + filename + ".json"));
        if (!myFile.is_open()) {
            std::cout << "JSON File couldnt be opened" << std::endl;
            exit (84);
        }
        reader.parse(myFile, root);
        myMap[filename] = root;
    }

    Ikey EventManager::isWindowUp(IGraphic &libGraphic) {
        if (libGraphic.isWindowClosed())
            return WINDOWCLOSE;
        return NO_EVENT;
    }

    void EventManager::setEventJSON(std::map<std::string, Json::Value> myMap) {
        _jsonEvents = myMap;
    }

    std::map<std::string, Json::Value> &EventManager::getEventJSON() {
        return (_jsonEvents);
    }
}