//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_ACAMERA_H
#define BOMBERMAN_ACAMERA_H

#include "ICamera.hpp"
#include "raylib.h"

namespace Indie {

    class RaylibCamera : public ICamera {
    public:
        RaylibCamera() = default;
        void setRaylibCameraPosition(float x, float y, float z);
        void setRaylibCameraTarget(float x, float y, float z);
        void setRaylibCameraUp(float x, float y, float z);
        void setRaylibCameraFovy(float fovy);
        void setRaylibCameraMode();
        Camera &getCamera();
    private:
        Camera _camera = { 0 };
    };

}

#endif //BOMBERMAN_ACAMERA_H
