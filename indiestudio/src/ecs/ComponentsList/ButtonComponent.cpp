//
// Created by jbroesch on 5/21/21.
//

#include "ButtonComponent.hpp"
#include "../Manager.hpp"

namespace Indie {

    ButtonComponent::ButtonComponent(int number) {
        _buttonNumber = number;
    }

    void ButtonComponent::init(IGraphic *libgraphic) {
        _state = BUT_NO_EVENT;
    }

    ButtonState ButtonComponent::getState() { return _state; }

    void ButtonComponent::setState(ButtonState state) { _state = state; }

    void ButtonComponent::update(double time) {
        (void)time;
    }

    void ButtonComponent::setButtonNumber(int number) {
        _buttonNumber = number;
    }

    int ButtonComponent::getButtonNumber() const {
        return _buttonNumber;
    }

}