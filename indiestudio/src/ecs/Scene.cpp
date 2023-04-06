//
// Created by jbroesch on 5/17/21.
//

#include "Scene.hpp"

namespace Indie {
    Scene::Scene(SceneManager *sceneManager, std::string name) {
        _sceneManager = sceneManager;
    }

    Scene::~Scene() = default;

    std::string Scene::getName() const {
        return _sceneName;
    }

    void Scene::setName(std::string name) {
        _sceneName = name;
    }

    void Scene::update(double dt) {
        (void)_sceneManager;
        _manager.refresh();
        _manager.update(dt);
    }

    void Scene::draw(IGraphic& libGraphic) {
        _manager.draw(libGraphic);
    }

    Ikey Scene::getEvent(IGraphic& libGraphic) {
        if (WindowShouldClose())
            return WINDOWCLOSE;
        (void)libGraphic;
        return NO_EVENT;
    }

    void Scene::onActivate(IGraphic& libGraphic) {
        create_entities(&libGraphic, _sceneName, _manager);
    }

    void Scene::onDeactivate(IGraphic& libGraphic) {
        for (auto & it : _manager.getEntities()) {
            libGraphic.unload_assets(*(it.second));
            it.second->destroy();
        }
    }

    Manager *Scene::getManager() {
        return &_manager;
    }

}