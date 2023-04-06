//
// Created by jbroesch on 5/19/21.
//

#include "Entity.hpp"
#include "../graphicalLib/IGraphic.hpp"

namespace Indie {

    ComponentID getComponentTypeID() {
        static ComponentID lastID = 0;
        return lastID++;
    }

    void Entity::draw(IGraphic &libGraphic) {
        for (auto& c : _components) c->draw(libGraphic);
    }

    void Entity::update(double time) {
        for (auto& c : _components) c->update(time);
    }

    bool Entity::isAlive() const {
        return _alive;
    }

    void Entity::destroy() {
        _alive = false;
    }
}