//
// Created by jeanningros on 3/22/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_TEXT_HPP
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_TEXT_HPP

#include <iostream>
#include <algorithm>
#include "../PersonnalType.hpp"


namespace Arcade {
    class Text {
    public:
        Text(int xPos, int yPos, const std::string &str, Color color = WHITE, int size = 1);
        virtual ~Text();

        bool getHighlight() const;
        void setHighlight(bool highlight);
        int getXPos() const;
        void setXPos(int xPos);
        int getYPos() const;
        void setYPos(int yPos);
        int getSize() const;
        void setSize(int size);
        const std::string &getStr() const;
        void setStr(const std::string &str);
        Color getColor() const;
        void setColor(Color color);

    private:
        bool _highlight;
        int _xPos;
        int _yPos;
        int _size;
        std::string _str;
        Color _color;
    };
}


#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_TEXT_HPP
