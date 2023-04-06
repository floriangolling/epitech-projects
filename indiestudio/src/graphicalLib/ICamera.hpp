//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_ICAMERA_HPP
#define BOMBERMAN_ICAMERA_HPP

namespace Indie {

    class ICamera {
    public:
        ICamera() = default;
        virtual void setRaylibCameraPosition(float x, float y, float z) = 0;
        virtual void setRaylibCameraTarget(float x, float y, float z) = 0;
        virtual void setRaylibCameraUp(float x, float y, float z) = 0;
        virtual void setRaylibCameraFovy(float fovy) = 0;
        virtual void setRaylibCameraMode() = 0;
    };

}

#endif //BOMBERMAN_ICAMERA_HPP
