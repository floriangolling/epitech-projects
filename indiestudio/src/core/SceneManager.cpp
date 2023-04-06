//
// Created by jbroesch on 5/20/21.
//

#include "SceneManager.hpp"
#include "EventManager.hpp"

namespace Indie {

    SceneManager::SceneManager() {
        _scenesNumber = 0;
    }

    void SceneManager::setCurrentScene(std::shared_ptr<IScene> scene) {
        _currentScene = scene;
    }

    void SceneManager::addScene(std::shared_ptr<IScene> scene, std::string name) {
        auto inserted = _scenes.insert(std::make_pair(_scenesNumber, scene));
        _scenesNumber += 1;
    }

    const std::map<unsigned int, std::shared_ptr<IScene>> &SceneManager::getScenes() const {
        return (_scenes);
    }

    void SceneManager::removeScene(int id, IGraphic &libgraphic) {
        auto it = _scenes.find(id);
        if (it != _scenes.end()) {
            it->second->onDeactivate(libgraphic);
            _scenes.erase(it);
        }
    }

    void SceneManager::switchScene(IGraphic *libgraphic, int id) {
        auto it = _scenes.find(id);
        if (it != _scenes.end()) {
            if(_currentScene)
                _currentScene->onDeactivate(*libgraphic);
            _currentScene = it->second;
            _currentScene->onActivate(*libgraphic);
            for (auto & _sceneLink : _sceneLinks)
                if (_sceneLink.second == id) {
                    _eventManager->setSceneEntity(_currentScene->getManager()->getEntities(), *libgraphic);
                    _eventManager->addEvents(_sceneLink.first,_eventManager->getEventJSON());
                    libgraphic->setSceneName(_sceneLink.first);
                }
        }
    }

    void SceneManager::draw(IGraphic &libgraphic) {
        if (_currentScene)
            _currentScene->draw(libgraphic);
    }

    void SceneManager::update(double time) {
        if (_currentScene)
            _currentScene->update(time);
    }

    Ikey SceneManager::getEvent(IGraphic &libgraphic) {
        if (_currentScene)
            return _currentScene->getEvent(libgraphic);
        return NO_EVENT;
    }

    IScene* SceneManager::getCurrentScene() {
        return _currentScene.get();
    }

    void SceneManager::setEventManager(EventManager *eventManager) {
        _eventManager = eventManager;
    }

}