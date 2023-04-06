//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_IANIMATION_HPP
#define BOMBERMAN_IANIMATION_HPP

#include "raylib.h"
#include "../utils/utils.hpp"

namespace Indie {

    class IAnimation {
        public :
        virtual void setRaylibAnims(char *fp, ModelSelection) = 0;
        virtual int getRaylibAnimscount(ModelSelection selection) = 0;
        virtual int getRaylibAnimeFrameCounetr(ModelSelection selection) = 0;
        virtual void setRaylibAnimeFrameCounetr(int add, ModelSelection) = 0;
        virtual void setResetAnimeFrameCounter(ModelSelection selection) = 0;
        virtual ModelSelection getActualAnimationState() = 0;
        virtual void setActualAnimationState(ModelSelection) = 0;
    };

}
#endif //BOMBERMAN_IANIMATION_HPP
