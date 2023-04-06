//
// Created by jbroesch on 5/27/21.
//

#include "StatsComponent.hpp"

namespace Indie {

    StatsComponent::StatsComponent(Json::Value &values) {
        _values = values;
        _speed = 0;
        _range = 1;
        _reset = false;
    }

    void StatsComponent::init(IGraphic *libgraphic) {
        _maxBombs = _values["maxBombs"].asInt();
        _actualBombs = _values["actualBombs"].asInt();
        _range = _values["range"].asInt();
        _speed = _values["speed"].asFloat();
        _actualBombs = 1;
        _maxBombs = 1;
        _canThrough = false;
        _t = 0;
    }

    void StatsComponent::setCanThrough(bool i) {
        _canThrough = i;
    }

    int StatsComponent::getMaxBombs() {
        return (_maxBombs);
    }

    int StatsComponent::getActualBombs() {
        return (_actualBombs);
    }

    bool StatsComponent::getCanThrough() {
        return (_canThrough);
    }

    void StatsComponent::addNumberMaxBomb() {
        _maxBombs++;
        _actualBombs++;
    }

    void StatsComponent::addRange(int range) {
        _range += 1;
    }

    std::pair <float ,float> StatsComponent::getLastPos() {
        return (_lastPos);
    }

    void StatsComponent::setLastPos(float x, float y) {
        _lastPos.first = x;
        _lastPos.second = y;
    }

    void StatsComponent::addSpeed(float speed) {
        _speed += speed;
    }

    int StatsComponent::getRange() {
        return (_range);
    }

    float StatsComponent::getSpeed() {
        return (_speed);
    }

    bool StatsComponent::putBomb() {
        if (_actualBombs > 0) {
            _actualBombs--;
            _bombs.push_back(0);
            return (true);
        } else
            return (false);
    }

    bool StatsComponent::getReset() {
        return _reset;
    }

    void StatsComponent::setReset(bool i) {
        _reset = i;
    }

    void StatsComponent::update(double time) {
        if (_canThrough == true) {
            _t += time;
        }
        if (_t > 3) {
            _canThrough = false;
            _t = 0;
            _reset = true;
        }
        for (auto it = _bombs.begin(); it != _bombs.end(); it++) {
            (*it) += time;
        }
        while (_bombs.size() > 0 && _bombs.front() >= 3) {
            _bombs.erase(_bombs.begin());
            _actualBombs++;
        }
    }

    void StatsComponent::draw(IGraphic &libgraphic) {
        (void)libgraphic;
    }

    	bool StatsComponent::getRelease() {
        return _release;
    }

    void StatsComponent::setRelease(bool release) {
        _release = release;
    }
    
}