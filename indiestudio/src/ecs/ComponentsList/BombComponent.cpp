//
// Created by jbroesch on 5/27/21.
//

#include "BombComponent.hpp"

namespace Indie {

    BombComponent::BombComponent(float x, float z, int id, int range, float t) {
        _range = range;
        _x = x;
        _z = z;
        _time = t;
        _shouldExplose = false;
        _isExplosing = false;
        _hasExploded = false;
        _id = id;
        _isThroughVector.clear();
    }

    void BombComponent::pushIsThrough(int id, bool bo) {
        _isThroughVector.push_back(std::make_pair(id, bo));
    }

    std::vector<std::pair<int, bool>> &BombComponent::getIsThrough() {
        return (_isThroughVector);
    }

    int BombComponent::getRange() {
        return (_range);
    }

    void BombComponent::init(IGraphic *libgraphic) {
    }

    std::vector<std::pair<float, float>> &BombComponent::getVector() {
        return (_vectorExplo);
    }

    void BombComponent::setVector(std::vector<std::pair<float, float>> vec) {
        _vectorExplo = vec;
    }

    int BombComponent::getId() {
        return (_id);
    }

    void BombComponent::update(double time) {
        _time += time;
        if (_time >= 3 && _shouldExplose == false)
            _shouldExplose = true;
        if (_time >= 3.2 && _shouldExplose == true && _isExplosing == false)
            _isExplosing = true;
    }

    void BombComponent::setHasExploded(bool i) {
        _hasExploded = i;
    }

    bool BombComponent::gethasExploded() {
        return (_hasExploded);
    }
    void BombComponent::setDestruction() { this->_entity->destroy(); }

    float BombComponent::getTime() {
        return (_time);
    }

    void BombComponent::setPosition(float x, float z) {
        _x = x;
        _z = z;
    }

    bool BombComponent::getExplose() {
        return (_shouldExplose);
    }

    bool BombComponent::getIsExplosing() {
        return (_isExplosing);
    }

    std::pair<float, float> BombComponent::getPosition() {
        return (std::pair<float,float>(_x, _z));
    }

    void BombComponent::draw(IGraphic &libgraphic) {
        libgraphic.myDraw(this);
    }
}