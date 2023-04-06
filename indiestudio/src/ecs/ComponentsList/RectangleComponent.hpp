//
// Created by jbroesch on 5/21/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_RECTANGLECOMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_RECTANGLECOMPONENT_H

#include "../Component.hpp"

namespace Indie {

    class RectangleComponent : public Component {
    public :
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        Vector getRectanglePosition();
        void setRectanglePosition(Vector);
        float getRectangleHeight() const;
        void setRectangleHeight(float);
        float getRectangleWidth() const;
        void setRectangleWidth(float);
        Rect getRectangle();
        void setScale(float);

    private :
        Rect _rectangle;
        Vector _position;
        float _width;
        float _height;
        float _scale;
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_RECTANGLECOMPONENT_H
