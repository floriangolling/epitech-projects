//
// Created by jbroesch on 5/31/21.
//

#ifndef BOMBERMAN_RAYLIBANIMATION_HPP
#define BOMBERMAN_RAYLIBANIMATION_HPP

#include "IAnimation.hpp"

namespace Indie {

    class RaylibAnimation: public IAnimation {

    public :
        RaylibAnimation() = default;

        void setRaylibAnims(char *fp, ModelSelection) override;

        int getRaylibAnimscount(ModelSelection selection) override;

        int getRaylibAnimeFrameCounetr(ModelSelection selection) override;

        void setRaylibAnimeFrameCounetr(int add, ModelSelection) override;

        void setResetAnimeFrameCounter(ModelSelection selection) override;

        ModelAnimation *getModelAnimation(ModelSelection selection);

        ModelSelection getActualAnimationState() override;

        void setActualAnimationState(ModelSelection) override;

    protected :
        ModelAnimation *_iddleanims;
        ModelAnimation *_actionanims;
        ModelAnimation *_deathanims;
        int _iddleanimFrameCounter = 0;
        int _actionanimFrameCounter = 0;
        int _deathanimFrameCounter = 0;
        int _iddlekanimsCount = 0;
        int _actionanimsCount = 0;
        int _deathanimsCount = 0;
        ModelSelection _actualAnimationState;
    };

}

#endif //BOMBERMAN_RAYLIBANIMATION_HPP
