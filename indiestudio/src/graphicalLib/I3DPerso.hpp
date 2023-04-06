//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_I3DPERSO_HPP
#define BOMBERMAN_I3DPERSO_HPP

#include "raylib.h"
#include "../utils/utils.hpp"

namespace Indie {

    class I3DPerso {
    public:
        virtual void setPersoPosition(float x, float y, float z) = 0;
        virtual void setPersoModel(char *fp, ModelSelection) = 0;
        virtual void setPersoTexture(char *fp) = 0;
        virtual void setPersoMaterialTexture() = 0;
        virtual void setPlayerID(int) = 0;
        virtual float getY() = 0;
        virtual int getPlayerID() const = 0;
        virtual float getSpeed() const = 0;
        virtual void setSpeed(float) = 0;
        virtual std::pair<float, float> getPositionPair() = 0;
        virtual void setWinID(int) = 0;
        virtual int getWinID() = 0;
    };

}

#endif //BOMBERMAN_I3DPERSO_HPP
