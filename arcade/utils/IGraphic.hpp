//
// Created by jeanningros on 3/19/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGRAPHIC_H
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGRAPHIC_H

#include <iostream>
#include "PersonnalType.hpp"
#include "Text/Text.hpp"
#include "Pixel/Pixel.hpp"

namespace Arcade {
    class IGraphic {
    public:
        virtual ~IGraphic() = default;
        virtual void drawPixel(Pixel *pixel) = 0;
        virtual void drawText(Text *text) = 0;
        virtual void myClear() = 0;
        virtual void myRefresh() = 0;
        virtual Arcade::CommandType getInput() = 0;
        virtual std::string getName() = 0;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGRAPHIC_H
