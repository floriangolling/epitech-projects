//
// Created by jbroesch on 5/23/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MOUSEEVENTCOMPONENT_CUH
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MOUSEEVENTCOMPONENT_CUH

#include "../Component.hpp"

namespace Indie {

    class MouseEventComponent : public Component {
    public :
        MouseEventComponent() = default;
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
    private :
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MOUSEEVENTCOMPONENT_CUH
