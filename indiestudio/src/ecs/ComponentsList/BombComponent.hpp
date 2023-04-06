//
// Created by jbroesch on 5/27/21.
//

#ifndef BOMBERMAN_BOMB_COMPONENT_HPP
#define BOMBERMAN_BOMB_COMPONENT_HPP

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../../graphicalLib/IGraphic.hpp"

namespace Indie {

    class BombComponent : public Component {
    public:
        BombComponent(float, float, int, int, float);
        void update(double time) override;
        void init(IGraphic *libgraphic) override;
        void setDestruction();
        std::pair<float, float> getPosition();
        void setPosition(float, float);
        void draw(IGraphic &libGraphic) override;
        bool getExplose();
        void setHasExploded(bool);
        bool gethasExploded();
        bool getIsExplosing();
        float getTime();
        int getId();
        int getRange();
        void setVector(std::vector<std::pair<float, float>>);
        std::vector<std::pair<float, float>> &getVector();
        std::vector<std::pair<int, bool>> &getIsThrough(void);
        void pushIsThrough(int, bool);
    protected:
        int _range;
        bool _isExplosing;
        float _x;
        float _z;
        int _id;
        double _time;
        bool _shouldExplose;
        bool _hasExploded;
        std::vector<std::pair<int, bool>> _isThroughVector;
        std::vector<std::pair<float, float>> _vectorExplo;
    };
}


#endif //BOMBERMAN_BOMB_COMPONENT_HPP
