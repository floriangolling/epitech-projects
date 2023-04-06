//
// Created by jbroesch on 5/23/21.
//

#include "KeyboardEventComponent.hpp"
#include <iostream>

namespace Indie {
    KeyboardEventComponent::KeyboardEventComponent(std::string key, int state) {
        _state = state;
        _key = key;
    }

    void KeyboardEventComponent::init(IGraphic *libgraphic) {

    }

    void KeyboardEventComponent::update(double time) {
        (void)time;
    }

    void KeyboardEventComponent::setState(int state) {
        _state = state;
    }

    int KeyboardEventComponent::getState() {
        return (_state);
    }

    void KeyboardEventComponent::setKey(std::string key) {
        _key = key;
    }

    std::string KeyboardEventComponent::getKey() {
        return (_key);
    }
}