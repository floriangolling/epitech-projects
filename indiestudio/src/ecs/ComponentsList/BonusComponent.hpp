//
// Created by jbroesch on 5/27/21.
//

#ifndef BOMBERMAN_BONUS_HPP
#define BOMBERMAN_BONUS_HPP

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include "../../utils/utils.hpp"

namespace Indie {

    class BonusComponent : public Component {
    public:
        enum TypeBonus {
            RANGE = 2,
            SPEED,
            WALLCUBE,
            DOUBLE
        };
        BonusComponent(TypeBonus, float, float);
        void setIsUsed();
        bool getIsUsed();
        void update(double time) override;
        void init(IGraphic *libgraphic) override;
        void draw(IGraphic &libGraphic) override;
        std::pair<float, float> getPos();
        TypeBonus getType();
    protected:
        BonusComponent::TypeBonus _type;
        bool _gotCatch;
        float _x;
        float _z;
        bool _isUsed;
    };
}


#endif //BOMBERMAN_BOMB_COMPONENT_HPP
