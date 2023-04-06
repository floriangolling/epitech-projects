//
// Created by jbroesch on 6/16/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_PAUSECOMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_PAUSECOMPONENT_H

#include "../Component.hpp"
#include "../../utils/utils.hpp"

namespace Indie {

    class PauseComponent : public Component {
    public :
        PauseComponent();
        void init(IGraphic *libgraphic) override;
        void update(double time) override;
        void setIsPause(bool);
        bool getIsPause();
    private:
        bool _isPause = false;
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_PAUSECOMPONENT_H
