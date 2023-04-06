//
// Created by jbroesch on 5/21/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_BUTTONCOMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_BUTTONCOMPONENT_H

#include "../Component.hpp"
#include "../../utils/utils.hpp"

namespace Indie {

    class ButtonComponent : public Component {
    public :
        explicit ButtonComponent(int);
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        ButtonState getState();
        void setState(ButtonState);
        void setButtonNumber(int);
        int getButtonNumber() const;
    private :
        ButtonState _state;
        int _buttonNumber;
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_BUTTONCOMPONENT_H
