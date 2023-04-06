//
// Created by jbroesch on 5/27/21.
//

#ifndef STATS_COMPONENTS_HH
#define STATS_COMPONENTS_HH

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include "../../jsoncpp/json.h"

namespace Indie {

    class StatsComponent : public Component {
    public:
        StatsComponent(Json::Value &values);
        void update(double time) override;
        int getActualBombs();
        int getMaxBombs();
        void init(IGraphic *libgraphic) override;
        void draw(IGraphic &libGraphic) override;
        void setDestruction();
        bool putBomb();
        void addSpeed(float);
        void addNumberMaxBomb();
        void addRange(int);
        float getSpeed();
        int getRange();
        void setCanThrough(bool);
        bool getCanThrough();
        std::pair <float ,float> getLastPos();
        void setLastPos(float, float);
        bool getReset();
        void setReset(bool);
        void setRelease(bool);
        bool getRelease();
    protected:
        bool _reset;
        Json::Value _values;
        bool _canThrough;
        std::pair <float ,float> _lastPos;
        std::vector<double> _bombs;
        int _maxBombs;
        int _actualBombs;
        float _speed;
        int _range;
        float _t;
        bool _release = true;

    };
}

#endif