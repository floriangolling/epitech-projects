//
// Created by jbroesch on 6/4/21.
//

#ifndef BOMBERMAN_MAPCOMPONENT_HPP
#define BOMBERMAN_MAPCOMPONENT_HPP

#include "../../graphicalLib/RaylibMap.hpp"
#include "../../jsoncpp/json.h"
#include "../Component.hpp"

namespace Indie {

    class MapComponent : public Component {
    public :
        MapComponent(Json::Value &values);
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        void draw(IGraphic &libGraphic) override;
        IMap &getMap();
        void resetMap(Vector, Vector, char*);
        std::array<std::string, 13> &getMyMapArray();
        int getType();
        void setMap(std::array<std::string, 13>);
    private :
        Json::Value _values;
        IMap *_map;
        std::array<std::string, 13> _myMapArray;
        int _type;
    };

}

#endif //BOMBERMAN_MAPCOMPONENT_HPP
