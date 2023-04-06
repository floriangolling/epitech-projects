//
// Created by jbroesch on 6/1/21.
//

#include "RaylibCamera.hpp"

namespace Indie {

    void RaylibCamera::setRaylibCameraPosition(float x, float y, float z) {
        _camera.position = Vector3{x, y, z};
    }
    void RaylibCamera::setRaylibCameraTarget(float x, float y, float z) {
        _camera.target = Vector3{x, y, z};
    }
    void RaylibCamera::setRaylibCameraUp(float x, float y, float z) {
        _camera.up = Vector3{x, y, z};
    }
    void RaylibCamera::setRaylibCameraFovy(float fovy) {
        _camera.fovy = fovy;
    }
    void RaylibCamera::setRaylibCameraMode(){
        _camera.projection = CAMERA_PERSPECTIVE;
    }

    Camera &RaylibCamera::getCamera() {
        return _camera;
    }

}