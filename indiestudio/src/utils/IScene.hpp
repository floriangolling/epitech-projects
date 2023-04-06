//
// Created by jbroesch on 5/17/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ISCENE_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ISCENE_HPP

#include "utils.hpp"
#include "../graphicalLib/IGraphic.hpp"
#include "../ecs/Manager.hpp"

namespace Indie {
    class IScene {
    public :
        virtual ~IScene() = default;
        virtual void onActivate(IGraphic& libGraphic) = 0;
        virtual Manager *getManager() = 0;
        virtual void onDeactivate(IGraphic&) = 0;
        virtual void draw(IGraphic&) = 0;
        virtual Ikey getEvent(IGraphic&) = 0;
        virtual void update(double) = 0;
        virtual void setName(std::string) = 0;
        virtual std::string getName() const = 0;
    };
}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ISCENE_HPP
