//
// Created by jeanningros on 3/23/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_PIXEL_HPP
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_PIXEL_HPP

#include "../PersonnalType.hpp"

namespace Arcade {
    class Pixel {
    public:
        Pixel(int xPos, int yPos, Color color = WHITE, int size = 1);
        virtual ~Pixel();

        int getXPos() const;
        void setXPos(int xPos);
        int getYPos() const;
        void setYPos(int yPos);
        int getSize() const;
        void setSize(int size);
        Color getColor() const;
        void setColor(Color color);
        int getFactor() const;
        void setFactor(int);

    private:
        int _xPos;
        int _yPos;
        Color _color;
        int _size;
        int _factor;
    };
}


#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_PIXEL_HPP
