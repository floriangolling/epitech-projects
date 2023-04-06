//
// Created by jbroesch on 6/13/21.
//

#include "SceneManager.hpp"
#include "../ecs/Scene.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;

namespace Indie {

    void loadScenes(SceneManager *_sceneManager) {
        std::string path = "../jsonScenes";
        std::string fileName;
        std::string ext(".json");
        size_t size = 0;

        for (const auto & entry : fs::directory_iterator(path)) {
            fs::path p = entry.path();
            fileName = p.string();
            fileName.erase(0, 14);
            if (fileName != ext && fileName.size() > ext.size() && fileName.substr(fileName.size() - ext.size()) == ".json" ) {
                fileName = fileName.substr(0, fileName.size() - ext.size());
                errorHandlingOnJsonFiles(fileName);
                std::shared_ptr<Scene> newScene = std::make_shared<Scene>(_sceneManager, fileName);
                newScene->setName(fileName);
                _sceneManager->addScene(newScene, fileName);
                _sceneManager->_sceneLinks[fileName] = size;
                size++;
            }
        }
    }

    void errorHandlingOnJsonFiles(std::string filename) {
        std::string fn = filename;
        Json::Reader reader;
        Json::Value root;
        Json::Value entities;

        std::ifstream file("../jsonScenes/" + filename + ".json");

        if (!file.is_open()) {
            std::cerr << filename << "couldn't be opened" << std::endl;
            exit (84);
        }
        if (filename == "save")
            fn = "game";
        reader.parse(file, root);
        entities = root[fn]["entities"]; 
        for (auto it : entities ) {
            if (!it.isMember("name") || it["name"] == "") {
                std::cerr << "An entity in : " << filename << " has no name member or is empty" << std::endl;
                exit (84);
            } else {
                if (!it.isMember("components")) {
                    std::cerr << "an entity need a component array, even empty: in file :" << filename << std::endl;
                }
                Json::Value components = it["components"];
                for (auto compo : components) {
                    if (compo.isMember("name") && compo["name"] == "positionComponent") {
                        if (!compo.isMember("x") || !compo.isMember("y")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a position Component need and x and y attribute to be set" << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "textureComponent") {
                        if (!compo.isMember("filePath") ||  compo["filePath"] == "") {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a texture component needs a filePath attribute" << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "buttonComponent") {
                        if (!compo.isMember("state")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a button Component needs a state attribute (0,1)" << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "scaleComponent") {
                        if (!compo.isMember("size")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a scale Component needs a size set (ex: 1 for no scaling by default)" << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "textComponent") {
                        if (!compo.isMember("size") || !compo.isMember("x") || !compo.isMember("y") || !compo.isMember("data")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a text Component needs 4 attributes to be set : data | x | y | size " << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "cameraComponent") {
                        if (!compo.isMember("positionX") || !compo.isMember("positionY") || !compo.isMember("positionZ") || !compo.isMember("targetX") || !compo.isMember("targetY") || !compo.isMember("targetZ") || !compo.isMember("upX") || !compo.isMember("upY") || !compo.isMember("upZ") || !compo.isMember("fovy")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a text Component needs 10 attributes to be set : positionX | positionY | positionZ | targetX | targetY | targetZ | upX | upY | upZ | fovy" << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "PersoComponent") {
                        if (!compo.isMember("positionX") || !compo.isMember("positionY") || !compo.isMember("positionZ") || !compo.isMember("iddlemodelpath") || !compo.isMember("actionmodelpath") || !compo.isMember("deathmodelpath") || !compo.isMember("texturepath") || !compo.isMember("id")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a Perso Component needs 8 attributes to be set : positionX | positionY | positionZ | iddlemodelpath | actionmodelpath | deathmodelpath | texturepath | id " << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "AnimationComponent") {
                        if (!compo.isMember("iddleanimationpath") || !compo.isMember("actionanimationpath") || !compo.isMember("deathanimationpath") || !compo.isMember("type")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a animation Component needs 4 attributes to be set : iddleanimationpath | actionanimationpath | deathanimationpath | type " << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "StatsComponent") {
                        if (!compo.isMember("maxBombs") || !compo.isMember("actualBombs") || !compo.isMember("range") || !compo.isMember("speed")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a Stat Component needs 4 attributes to be set : maxBombs | actualsBombs | speed | range " << std::endl;
                            exit (84);
                        }
                    }
                    if (compo.isMember("name") && compo["name"] == "MapComponent") {
                        if (!compo.isMember("positionMeshX") || !compo.isMember("positionMeshY") || !compo.isMember("positionMeshZ") || !compo.isMember("positionMapX") || !compo.isMember("positionMapY") || !compo.isMember("positionMapZ") || !compo.isMember("maptype")) {
                            std::cerr << "Error in entitie : " << it["name"] << std::endl; 
                            std::cerr << "Error in : " << filename << " a Map Component needs 7 attributes to be set : positionMeshX | positionMeshY | positionMeshZ | positionMapX | positionMapY | positionMapZ | maptype" << std::endl;
                            exit (84);
                        }
                    }
                }
            }
        }
    }
}