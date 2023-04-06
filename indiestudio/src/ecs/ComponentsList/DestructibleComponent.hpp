//
// Created by jbroesch on 5/27/21.
//

#ifndef BOMBERMAN_DESTRUCTIBLECOMPONENT_HPP
#define BOMBERMAN_DESTRUCTIBLECOMPONENT_HPP

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"

namespace Indie {

    class DestructibleComponent : public Component {
    public:
        void update(double time) override;
        void init(IGraphic *libgraphic) override;
        void setDestruction();
    };

}


#endif //BOMBERMAN_DESTRUCTIBLECOMPONENT_HPP
