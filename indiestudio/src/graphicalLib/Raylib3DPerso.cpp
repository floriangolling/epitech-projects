//
// Created by jbroesch on 6/1/21.
//

#include "Raylib3DPerso.hpp"
#include <sstream>

namespace Indie {

    Raylib3DPerso::Raylib3DPerso() {
        _speed = 2;
    }

    void Raylib3DPerso::setSpeed(float speed) {
        _speed = speed;
    }

    float Raylib3DPerso::getSpeed() const {
        return _speed;
    }

    int Raylib3DPerso::getPlayerID() const {
        return (_numberPlayer);
    }

    void Raylib3DPerso::setPlayerID(int number) {
        _numberPlayer = number;
    }

    void Raylib3DPerso::setPersoPosition(float x, float y, float z) {
        _position = Vector3{x, y, z};
    }

    std::pair<float, float> Raylib3DPerso::getPositionPair() {
        return (std::make_pair(_position.x, _position.z));
    }

    float Raylib3DPerso::getY() {
        return (_position.y);
    }

    void Raylib3DPerso::setPersoModel(char *fp, ModelSelection modelselected) {
        if (modelselected == MODEL_IDDLE)
            _modelIddle = LoadModel(fp);
        else if (modelselected == MODEL_ACTION)
            _modelAction = LoadModel(fp);
        else if (modelselected == MODEL_DEATH)
            _modelDeath = LoadModel(fp);
    }

    void Raylib3DPerso::setPersoTexture(char *fp) {
        _texture = LoadTexture(fp);
        if (_texture.id == 0) {
            std::stringstream ss;
            ss << "Error : Not a valid file" << fp << ", exiting";
            std::string file_error = ss.str();
            throw std::runtime_error(file_error);
        }
    }

    void Raylib3DPerso::setPersoMaterialTexture() {
        SetMaterialTexture(&_modelIddle.materials[0], MAP_DIFFUSE, _texture);
        SetMaterialTexture(&_modelAction.materials[0], MAP_DIFFUSE, _texture);
        SetMaterialTexture(&_modelDeath.materials[0], MAP_DIFFUSE, _texture);
    }

    Vector3 Raylib3DPerso::getPosition() {
        return _position;
    }

    Texture2D & Raylib3DPerso::getTexture() {
            return _texture;
    }

    Model &Raylib3DPerso::getModel(ModelSelection modelselected) {
        if (modelselected == MODEL_IDDLE)
            return _modelIddle;
        else if (modelselected == MODEL_ACTION)
            return _modelAction;
        else if (modelselected == MODEL_DEATH)
            return _modelDeath;
        return _modelIddle;
    }

    void Raylib3DPerso::setWinID(int ID) {
        _win_ID = ID;
    }

    int Raylib3DPerso::getWinID() {
        return _win_ID;
    }
}