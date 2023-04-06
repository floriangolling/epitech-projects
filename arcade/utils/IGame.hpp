//
// Created by jeanningros on 3/19/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGAME_H
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGAME_H

#include "PersonnalType.hpp"
#include "IGraphic.hpp"

namespace Arcade {
    class IGame {
    public:
        virtual ~IGame() = default;
        virtual void draw(IGraphic&) = 0;
        virtual CommandType getEvent(IGraphic&) = 0;
        virtual void update(double timeElapsed) = 0;
        virtual void setPlayerName(std::string& player) = 0;
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_IGAME_H
