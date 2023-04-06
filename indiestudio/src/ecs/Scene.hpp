//
// Created by jbroesch on 5/26/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENE_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENE_H

#include "Manager.hpp"
#include "../core/SceneManager.hpp"
#include "../utils/AScene.hpp"

namespace Indie {

    class Scene : public AScene {
    public :
        explicit Scene(SceneManager*, std::string);
        ~Scene() override;
        void onActivate(IGraphic& libGraphic) override;
        void onDeactivate(IGraphic& libGraphic) override;
        void draw(IGraphic&) override;
        Ikey getEvent(IGraphic&) override;
        void update(double) override;
        Manager *getManager() override;
        std::string getName() const override;
        void setName(std::string) override;
    private :
        std::string _sceneName;
        Manager _manager;
        SceneManager *_sceneManager;
    };
    void errorHandlingOnJsonFiles(std::string filename);
}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_SCENE_H
