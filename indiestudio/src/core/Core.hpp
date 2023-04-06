//
// Created by jbroesch on 5/15/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_INDIE_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_INDIE_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <filesystem>
#include <chrono>
#include <map>
#include "../graphicalLib/graphical.hpp"
#include "../utils/IScene.hpp"
#include "../utils/utils.hpp"
#include "SceneManager.hpp"
#include "EventManager.hpp"
#include "../jsoncpp/json.h"
#include <fstream>
#include <ostream>
#include <thread>
#include <mutex>
#include "Clock.hpp"

namespace Indie {

    void init_graphical(IGraphic *libgraphic);
    void loadScenes(SceneManager *_sceneManager);

    class Core {
    public:
        Core();
        ~Core();
        void loop();
        int event(float eventTime);
        void update(double);
        void display();
    private:
        IGraphic *_libGraphic;
        SceneManager _sceneManager;
        EventManager _eventManager;
    };
}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_INDIE_H
