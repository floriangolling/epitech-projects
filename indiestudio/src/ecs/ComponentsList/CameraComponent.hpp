//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_CAMERACOMPONENT_H
#define BOMBERMAN_CAMERACOMPONENT_H

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../../jsoncpp/json.h"
#include "../../graphicalLib/RaylibCamera.hpp"

namespace Indie {

    class CameraComponent : public Component {
        public:
            explicit CameraComponent(Json::Value &values);
            void update(double time) override;
            void init(IGraphic *libgraphic) override;
            ICamera &getCamera();
        private:
            Json::Value _values;
            ICamera *_camera;
    };

}


#endif //BOMBERMAN_CAMERACOMPONENT_H
