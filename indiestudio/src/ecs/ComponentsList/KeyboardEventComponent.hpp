//
// Created by jbroesch on 5/23/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_KEYBOARDEVENTCOMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_KEYBOARDEVENTCOMPONENT_H

#include "../Component.hpp"
#include "ostream"

namespace Indie {

    class KeyboardEventComponent : public Component {
    public :
        KeyboardEventComponent(std::string, int);
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        void setState(int);
        void setKey(std::string);
        std::string getKey();
        int getState();
    private:
        int _state;
        std::string _key;
    };
}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_KEYBOARDEVENTCOMPONENT_H
