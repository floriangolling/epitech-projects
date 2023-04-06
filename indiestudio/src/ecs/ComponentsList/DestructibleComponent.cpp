//
// Created by jbroesch on 5/27/21.
//

#include "DestructibleComponent.hpp"

namespace Indie {

    void DestructibleComponent::init(IGraphic *libgraphic) {}

    void DestructibleComponent::update(double time) {
        (void)time;
    }

    void DestructibleComponent::setDestruction() { this->_entity->destroy(); }

}