//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_ANIMATIONCOMPONENT_H
#define BOMBERMAN_ANIMATIONCOMPONENT_H

#include "../../graphicalLib/RaylibAnimation.hpp"
#include "../../jsoncpp/json.h"
#include "../Component.hpp"

namespace Indie {

    class AnimationComponent : public Component {
    public :
        AnimationComponent(Json::Value &values);
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        void draw(IGraphic &libGraphic) override;
        IAnimation &getAnimation();
    private :
        double _timeAnimation;
        Json::Value _values;
        IAnimation *_animation;
        typeAnimation _type;
    };
}


#endif //BOMBERMAN_ANIMATIONCOMPONENT_H
