//
// Created by jbroesch on 5/19/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENTS_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENTS_H

#include "../Manager.hpp"
#include "../Entity.hpp"
#include "../Component.hpp"

namespace Indie {

    class PositionComponent : public Component {
    public:
        explicit PositionComponent(Vector);
        void update(double time) override;
        void init(IGraphic *libgraphic) override;
        Vector getPosition();
        void setPosition(Vector);
        float getSavedposition();
    private:
        Vector _position;
        float _savedY;
    };

}
#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_COMPONENTS_H
