/*
** EPITECH PROJECT, 2021
** jsonparser
** File description:
** jsonParser
*/

#include "./AScene.hpp"
#include "../ecs/ComponentsList/PositionComponent.hpp"
#include "../ecs/ComponentsList/TextureComponent.hpp"
#include "../ecs/ComponentsList/ButtonComponent.hpp"
#include "../ecs/ComponentsList/RectangleComponent.hpp"
#include "../ecs/ComponentsList/MouseEventComponent.hpp"
#include "../ecs/ComponentsList/StatsComponent.hpp"
#include "../ecs/ComponentsList/KeyboardEventComponent.hpp"
#include "../ecs/ComponentsList/CameraComponent.hpp"
#include "../ecs/ComponentsList/TextComponent.hpp"
#include "../ecs/ComponentsList/Perso3DComponent.hpp"
#include "../ecs/ComponentsList/AnimationComponent.hpp"
#include "../ecs/ComponentsList/MapComponent.hpp"
#include "../ecs/ComponentsList/PauseComponent.hpp"
#include "../graphicalLib/IGraphic.hpp"
#include "../core/SceneManager.hpp"
#include "../jsoncpp/json.h"
#include <iostream>
#include <fstream>

void Indie::create_entities(IGraphic *libgraphic, const std::string &filename, Indie::Manager &_manager) {
    Json::Value root;
    Json::Reader reader;
    std::ifstream myFile("../jsonScenes/" + filename + ".json");
    static int check = 0;
    if (!myFile.is_open()) {
        std::cout << "JSON File couldnt be opened" << std::endl;
        exit (84);
    }
    _manager.getEntities().clear();
    reader.parse(myFile, root);
    Json::Value entities;
    if (filename == "save")
        entities = root["game"]["entities"];
    else
        entities = root[filename]["entities"];
    for (auto & entitie : entities) {
        std::shared_ptr<Entity> entity = _manager.addEntity(entitie["name"].asString());
        const Json::Value components = entitie["components"];
        check = 0;
        for (const auto & component : components) {
            if (component["name"].asString() == "positionComponent") {
                Vector position;
                position.x = component["x"].asFloat();
                position.y = component["y"].asFloat();
                entity->AddComponent<Indie::PositionComponent>(libgraphic, position);
                check++;
            }
            else if (component["name"].asString() == "textureComponent") {
                if (check == 1) {
                    std::string path =
                            "../" + component["filePath"].asString();
                    entity->AddComponent<Indie::TextureComponent>(libgraphic, path.c_str());
                    check ++;
                } else {
                    std::cout << "JSON File is not format properly, please try again" << std::endl;
                    entity->destroy();
                    continue;
                }
            }
            else if (component["name"].asString() == "rectangleComponent") {
                if (check == 2) {
                    entity->AddComponent<Indie::RectangleComponent>(libgraphic);
                    check++;
                } else {
                    std::cout << "JSON File is not format properly, please try again" << std::endl;
                    entity->destroy();
                    continue;
                }
            }
            else if (component["name"].asString() == "buttonComponent") {
                int number = component["number"].asInt();
                entity->AddComponent<Indie::ButtonComponent>(libgraphic, number);
            }
            else if (component["name"].asString() == "mouseEventComponent") {
                entity->AddComponent<Indie::MouseEventComponent>(libgraphic);
            }
            else if (component["name"].asString() == "textComponent") {
                std::string data = component["data"].asString();
                Vector position;
                position.x = component["x"].asFloat();
                position.y = component["y"].asFloat();
                int size = component["size"].asInt();
                entity->AddComponent<Indie::TextComponent>(libgraphic, data.c_str(), position, size);
            }
            else if (component["name"].asString() == "KeyboardEventComponent") {
                entity->AddComponent<Indie::KeyboardEventComponent>(libgraphic, component["key"].asString(), component["state"].asInt());
            }
            else if (component["name"].asString() == "cameraComponent") {
                Json::Value camera = component;
                entity->AddComponent<Indie::CameraComponent>(libgraphic, camera);
            }
            else if (component["name"].asString() == "PersoComponent") {
                Json::Value perso = component;
                entity->AddComponent<Indie::Perso3DComponent>(libgraphic, perso);
            }
            else if (component["name"].asString() == "AnimationComponent") {
                Json::Value animation = component;
                entity->AddComponent<Indie::AnimationComponent>(libgraphic, animation);
            }
            else if (component["name"].asString() == "MapComponent") {
                Json::Value map = component;
                entity->AddComponent<Indie::MapComponent>(libgraphic, map);
            }
            else if (component["name"].asString() == "StatsComponent") {
                Json::Value stats = component;
                entity->AddComponent<StatsComponent>(libgraphic, stats);
            }
            else if (component["name"].asString() == "PauseComponent") {
                entity->AddComponent<PauseComponent>(libgraphic);
            }
        }
    }
    myFile.close();
}