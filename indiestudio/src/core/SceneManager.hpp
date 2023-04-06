//
// Created by jbroesch on 5/20/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENEMANAGER_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENEMANAGER_H

#include "../utils/IScene.hpp"
#include <iostream>
#include <map>
#include <string>
#include <utility>

namespace Indie {

    void create_entities(IGraphic *libgraphic, const std::string &filename, Indie::Manager &_manager);
    class EventManager;
    class SceneManager {
    public:
        SceneManager();
        void addScene(std::shared_ptr<IScene>, std::string);
        IScene *getCurrentScene();
        void setCurrentScene(std::shared_ptr<IScene>);
        void switchScene(IGraphic *libgraphic, int);
        void removeScene(int, IGraphic &);
        void draw(IGraphic&);
        Ikey getEvent(IGraphic&);
        void update(double);
        std::map<std::string, unsigned int> _sceneLinks;
        void setEventManager(EventManager *);
        int _scenesNumber;
        const std::map<unsigned int, std::shared_ptr<IScene>> &getScenes() const;

    private:
        std::map<unsigned int, std::shared_ptr<IScene>> _scenes;
        std::shared_ptr<IScene> _currentScene;
        SceneManager *_sceneManager;
        EventManager *_eventManager;
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENEMANAGER_H
