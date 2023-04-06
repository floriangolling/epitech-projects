//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_PERSO3DCOMPONENT_H
#define BOMBERMAN_PERSO3DCOMPONENT_H

#include "../../graphicalLib/Raylib3DPerso.hpp"
#include "../../jsoncpp/json.h"
#include "../Component.hpp"

namespace Indie {

    class Perso3DComponent : public Component {
        public :
            Perso3DComponent(Json::Value &values);
            void init(IGraphic *libgraphic) override;
            void update(double time) override;
            void draw(IGraphic &libGraphic) override;
            I3DPerso &get3DPerso();
            void reset3DPerso(Vector3 vector, char *mfp, char *tfp);
            void setAlive(bool);
            bool getAlive();
        private :
        Json::Value _values;
        I3DPerso *_perso;
        bool _alive;
        float _time;
    };

}

#endif //BOMBERMAN_PERSO3DCOMPONENT_H
