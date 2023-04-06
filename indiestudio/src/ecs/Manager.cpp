//
// Created by jbroesch on 5/19/21.
//

#include "Manager.hpp"
#include "Component.hpp"
#include <utility>
#include <string>
#include "./ComponentsList/PauseComponent.hpp"
namespace Indie {

    Manager::Manager() = default;

    void Manager::draw(IGraphic &libGraphic) {
        for (auto &e : _entities) e.second->draw(libGraphic);
    }

    void Manager::update(double time) {
        for (auto &e : _entities) {
            if (e.second->hasComponent<PauseComponent>() && e.second->getComponent<PauseComponent>().getIsPause() == true)
                return;
        }
        for (auto &e : _entities) e.second->update(time);
    }

    void Manager::refresh() {
        for (auto it = _entities.begin(); it != _entities.end(); it++) {
            if (!(it->second->isAlive())) {
                _entities.erase(it);
                it = _entities.begin();
            }
        }
    }

    std::shared_ptr<Entity> Manager::addEntity(std::string name) {
        auto e = std::make_shared<Entity>();
        _entities[name] = e;
        return e;
    }

    std::map<std::string, std::shared_ptr<Entity>> &Manager::getEntities() {
        return _entities;
    }

}