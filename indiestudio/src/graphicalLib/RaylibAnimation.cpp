//
// Created by jbroesch on 6/1/21.
//

#include "RaylibAnimation.hpp"

namespace Indie {

    void RaylibAnimation::setRaylibAnims(char *fp, ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            _iddleanims = LoadModelAnimations(fp, &_iddlekanimsCount);
        else if (selection == MODEL_ACTION)
            _actionanims = LoadModelAnimations(fp, &_actionanimsCount);
        else if (selection == MODEL_DEATH)
            _deathanims = LoadModelAnimations(fp, &_deathanimsCount);

    }
    int RaylibAnimation::getRaylibAnimscount(ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            return _iddlekanimsCount;
        else if (selection == MODEL_ACTION)
            return _actionanimsCount;
        else if (selection == MODEL_DEATH)
            return _deathanimsCount;
        return -1;
    }

    int RaylibAnimation::getRaylibAnimeFrameCounetr(ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            return _iddleanimFrameCounter;
        else if (selection == MODEL_ACTION)
            return _actionanimFrameCounter;
        else if (selection == MODEL_DEATH)
            return _deathanimFrameCounter;
        return -1;
    }
    void RaylibAnimation::setRaylibAnimeFrameCounetr(int add, ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            _iddleanimFrameCounter += add;
        else if (selection == MODEL_ACTION)
            _actionanimFrameCounter += add;
        else if (selection == MODEL_DEATH)
            _deathanimFrameCounter += add;
    }
    void RaylibAnimation::setResetAnimeFrameCounter(ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            _iddleanimFrameCounter = 0;
        else if (selection == MODEL_ACTION)
            _actionanimFrameCounter = 0;
        else if (selection == MODEL_DEATH)
            _deathanimFrameCounter = 0;
    }
    ModelAnimation *RaylibAnimation::getModelAnimation(ModelSelection selection) {
        if (selection == MODEL_IDDLE)
            return _iddleanims;
        else if (selection == MODEL_ACTION)
            return _actionanims;
        else if (selection == MODEL_DEATH)
            return _deathanims;
        return 0;
    }

    ModelSelection RaylibAnimation::getActualAnimationState() {
        return _actualAnimationState;
    }

    void RaylibAnimation::setActualAnimationState(ModelSelection state) {
        _actualAnimationState = state;
    }

}