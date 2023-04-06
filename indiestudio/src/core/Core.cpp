//
// Created by jbroesch on 5/15/21.
//

#include "../ecs/Scene.hpp"
#include "Core.hpp"
#include <thread>
#include <chrono>

Indie::Core::Core() {
    _libGraphic = new Raylib();
    if (!_libGraphic)
        throw std::runtime_error("Error : _libGraphic is not initialized, exiting");
    _eventManager.setKeysAtStart();
    init_graphical(_libGraphic);
    _libGraphic->init_window();
    _libGraphic->createSpriteLibrarie();
    loadScenes(&_sceneManager);
    _sceneManager.setEventManager(&_eventManager);
    _eventManager.setSceneManager(&_sceneManager);
    _libGraphic->displayIntro();
    _sceneManager.switchScene(_libGraphic, (int)_sceneManager._sceneLinks["mainMenu"]);
    _eventManager.setClock();
}

void Indie::Core::loop() {
    float EventTime = 0;

    while (!(event(EventTime))) {
        EventTime = 0;
        if ((1000 / 30) > (_eventManager.getClock().getElapsedTimeSinceLastReset() * 1000)) {
            long x = (1000 / 30) - (_eventManager.getClock().getElapsedTimeSinceLastReset() * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(x));
        }
        update(_eventManager.getClock().getElapsedTimeSinceLastReset());
        display();
        EventTime = _eventManager.getClock().getElapsedTimeSinceLastReset();
        _eventManager.getClock().reset();
#if ! defined(__APPLE__)
        _libGraphic->updateMusic();
#endif
    }
    _sceneManager.getCurrentScene()->onDeactivate(*_libGraphic);
    _libGraphic->closeMyWindow();
}

int Indie::Core::event(float eventTime) {
    if (_sceneManager._scenesNumber > 0) {
        if (_eventManager.mouseEvents(*_libGraphic, eventTime)) {
            return (0);
        }
        _eventManager.keyboardEvents(*_libGraphic, eventTime);
        _eventManager.gamepadEvents(*_libGraphic, eventTime);
        Ikey ev = Indie::EventManager::isWindowUp(*_libGraphic);
        if (ev == WINDOWCLOSE)
            return 1;
    }
    return 0;
}

void Indie::Core::display() {
    if (_sceneManager._scenesNumber > 0) {
        _libGraphic->myClear();
        _libGraphic->beginDrawing();
        _sceneManager.draw(*_libGraphic);
        _libGraphic->endDrawing();
    }
}

void Indie::Core::update(double time) {
    _sceneManager.update(time);
}

Indie::Core::~Core() {
    if (_libGraphic)
        delete(_libGraphic);
}