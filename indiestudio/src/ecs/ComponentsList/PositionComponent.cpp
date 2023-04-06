//
// Created by jbroesch on 5/19/21.
//

#include "PositionComponent.hpp"

namespace Indie {

    PositionComponent::PositionComponent(Vector position) {
        _position = {position.x, position.y, position.z};
        _savedY = position.y;
    }

    void PositionComponent::init(IGraphic *libgraphic) {
        _position.x = _position.x;
        _position.y = _position.y;
        _position.z = _position.z;
    }

    void PositionComponent::update(double time) {
        (void)time;
    }

    void PositionComponent::setPosition(Vector position) {
        _position.x = position.x;
        _position.y = position.y;
        _position.z = _position.z;
    }

    Vector PositionComponent::getPosition() { return _position; }

    float PositionComponent::getSavedposition() {
        return _savedY;
    }
}