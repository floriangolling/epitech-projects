//
// Created by jbroesch on 6/4/21.
//

#include "RaylibMap.hpp"
#include <sstream>
#include <filesystem>

namespace Indie {

    void RaylibMap::setMap(Vector meshPos, Vector mapPos, char *fp, short map_type, ...) {
        if (map_type == 3) {
            if (!std::filesystem::exists(fp)) {
                std::cerr << "A path for Map component does not exist !" << std::endl;
                throw std::exception();
            }
            _image = LoadImage(fp);
            _cubicmap = LoadTextureFromImage(_image);
            if (_cubicmap.id == 0) {
                std::stringstream ss;
                ss << "Error : Not a valid file" << fp << ", exiting";
                std::string file_error = ss.str();
                throw std::runtime_error(file_error);
            }
            Vector3 meshsave = {0};
            meshsave.x = meshPos.x;
            meshsave.y = meshPos.y;
            meshsave.z = meshPos.z;
            _mesh = GenMeshCubicmap(_image, meshsave);
            _model = LoadModelFromMesh(_mesh);
            _texture = LoadTexture("../assets/maps/texture_box_atlas.png");
            if (_texture.id == 0) {
                std::stringstream ss;
                ss << "Error : Not a valid file" << fp << ", exiting";
                std::string file_error = ss.str();
                throw std::runtime_error(file_error);
            }
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
            _mapPosition = Vector3{mapPos.x, mapPos.y, mapPos.z};
            return;
        }
        if (map_type == 1)
            fp = (char*)"../assets/maps/mapBox.png";
        if (!std::filesystem::exists(fp)) {
            std::cerr << "A path for Map component does not exist !" << std::endl;
            throw std::exception();
        }
        _image = LoadImage(fp);
        _cubicmap = LoadTextureFromImage(_image);
        if (_cubicmap.id == 0) {
            std::stringstream ss;
            ss << "Error : Not a valid file" << fp << ", exiting";
            std::string file_error = ss.str();
            throw std::runtime_error(file_error);
        }
        Vector3 meshsave = {0};
        meshsave.x = meshPos.x;
        meshsave.y = meshPos.y;
        meshsave.z = meshPos.z;
        _mesh = GenMeshCubicmap(_image, meshsave);
        _model = LoadModelFromMesh(_mesh);
        if (map_type == 0) {
            _texture = LoadTexture(
                    "../assets/maps/texture_indestructible_atlas.png");
            if (_texture.id == 0) {
                std::stringstream ss;
                ss << "Error : Not a valid file" << fp << ", exiting";
                std::string file_error = ss.str();
                throw std::runtime_error(file_error);
            }
        }
        else {
            _texture = LoadTexture("../assets/maps/texture_box_atlas.png");
            if (_texture.id == 0) {
                std::stringstream ss;
                ss << "Error : Not a valid file" << fp << ", exiting";
                std::string file_error = ss.str();
                throw std::runtime_error(file_error);
            }
        }
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        _mapPosition = Vector3{mapPos.x, mapPos.y, mapPos.z};
    }

    Texture2D & RaylibMap::getTexture() {
        return _texture;
    }

    void RaylibMap::setMeshPosition(Vector vector) {
        _meshPosition.x = vector.x;
        _meshPosition.y = vector.y;
        _meshPosition.z = vector.z;
    }

    void RaylibMap::setMapPosition(Vector vector) {
        _mapPosition.x = vector.x;
        _mapPosition.y = vector.y;
        _mapPosition.z = vector.z;
    }

    Model RaylibMap::getMapModel() {
        return _model;
    }

    Vector3 &RaylibMap::getMapPosition() {
        return _mapPosition;
    }

    Image &RaylibMap::getImage() {
        return _image;
    }

    Texture2D &RaylibMap::getCubicMap() {
        return _cubicmap;
    }

}