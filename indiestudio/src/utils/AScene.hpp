//
// Created by jbroesch on 5/17/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ASCENE_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ASCENE_HPP

#include "IScene.hpp"
#include "../ecs/Entity.hpp"
#include "utils.hpp"
#include "vector"

namespace Indie {
    class AScene : public IScene {
    public :
        virtual ~AScene() {};
        virtual void onActivate(IGraphic& libGraphic) = 0;
        virtual Manager *getManager() = 0;
        virtual void onDeactivate(IGraphic& libGraphic) = 0;
        virtual void draw(IGraphic&) = 0;
        virtual Ikey getEvent(IGraphic&) = 0;
        virtual void update(double) = 0;
        virtual void setName(std::string) = 0;
        virtual std::string getName() const = 0;
    };
}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ASCENE_HPP
