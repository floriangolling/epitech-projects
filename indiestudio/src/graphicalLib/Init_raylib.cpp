/*
** EPITECH PROJECT, 2021
** jsonparser
** File description:
** jsonParser
*/

#include "../jsoncpp/json.h"
#include "IGraphic.hpp"
#include <iostream>
#include <fstream>

namespace Indie {

    void init_graphical(IGraphic *libgraphic) {
        Json::Value root;
        Json::Reader reader;
        std::string filename = "../src/graphicalLib/init.json";
        std::ifstream myFile(filename);
        static int check = 0;
        if (!myFile.is_open()) {
            throw std::runtime_error("Error : JSON File couldnt be opened (src/graphicalLib/init.json), exiting");
        }

        reader.parse(myFile, root);
        Json::Value entities = root["init_raylib"]["entities"];
        for (auto &entitie : entities) {
            const Json::Value components = entitie["components"];
            for (const auto &component : components) {
                if (component["name"].asString() == "initwindow") {
                    Vector position;
                    position.x = component["x"].asFloat();
                    position.y = component["y"].asFloat();
                    std::string wname = component["windowname"].asString();
                    int fps = component["fps"].asInt();
                    if (position.x == 0 || position.y == 0 || wname.empty() || !fps) {
                        throw std::runtime_error("Error : x, y or fps, not a valid value, exiting");
                    }
                    libgraphic->init_lib.window_x = (int) position.x;
                    libgraphic->init_lib.window_y = (int) position.y;
                    libgraphic->init_lib.window_name = wname;
                    libgraphic->init_lib.window_fps = fps;
                } else if (component["name"].asString() == "font") {
                    std::string filepath = component["filePath"].asString();
                    int size = component["size"].asInt();
                    if (size == 0 || filepath.empty()) {
                        throw std::runtime_error("Error : not a valid filepath (font), exiting");
                    }
                    libgraphic->init_lib.font = filepath;
                    libgraphic->init_lib.font_size = size;
                } else if (component["name"].asString() == "music") {
                    std::string filepath = component["filePath"].asString();
                    if (filepath.empty()) {
                        throw std::runtime_error("Error : not a valid filepath (music), exiting");
                    }
                    libgraphic->init_lib.music = filepath;
                } else if (component["name"].asString() == "sound") {
                    std::string filepath = component["filePath"].asString();
                    if (filepath.empty()) {
                        throw std::runtime_error("Error : not a valid filepath (sound), exiting");
                    }
                    libgraphic->init_lib.sound = filepath;
                }
            }
        }
        myFile.close();
    }

}