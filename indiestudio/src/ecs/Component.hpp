//
// Created by jbroesch on 5/19/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENT_H

#include "../utils/utils.hpp"

namespace Indie {

    class Entity;
    class IGraphic;
    class Component {
        public :
            Entity *_entity;

            virtual void init(IGraphic *libgraphic) {};
            virtual void update(double time) {};
            virtual void draw(IGraphic &libGraphic);
            virtual ~Component() {};
    };

    inline void Component::draw(IGraphic &libGraphic) { (void)libGraphic; }
}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENT_H
