//
// Created by jbroesch on 5/31/21.
//

#include "AnimationComponent.hpp"
#include "../../graphicalLib/IGraphic.hpp"
#include <filesystem>
#include <exception>

namespace Indie {

    AnimationComponent::AnimationComponent(Json::Value &values) {
        _values = values;
        _timeAnimation = 0;
    }

    void AnimationComponent::init(IGraphic *libgraphic) {
        _animation = libgraphic->create_animation();
        std::string wpath = _values["iddleanimationpath"].asString();
        std::string apath = _values["actionanimationpath"].asString();
        std::string dpath = _values["deathanimationpath"].asString();
        if (!std::filesystem::exists(wpath) || !std::filesystem::exists(apath) || !std::filesystem::exists(dpath)) {
            std::cerr << "A path for animation component does not exist !" << std::endl;
            throw std::exception();
        }
        ModelSelection actualAnimation = (ModelSelection)_values["actualanimation"].asInt();
        _type = (typeAnimation)_values["type"].asInt();
        _animation->setRaylibAnims(const_cast<char *>(wpath.c_str()), MODEL_IDDLE);
        _animation->setRaylibAnims(const_cast<char *>(apath.c_str()), MODEL_ACTION);
        _animation->setRaylibAnims(const_cast<char *>(dpath.c_str()), MODEL_DEATH);
        _animation->setActualAnimationState(actualAnimation);
    }

    void AnimationComponent::update(double time) {
        _timeAnimation += time;
        while (_type == MENUANIMATION && _timeAnimation >= 0.033) {
            _timeAnimation -= 0.033;
            this->getAnimation().setRaylibAnimeFrameCounetr(1, MODEL_IDDLE);
        }
        while (_type == SELECTORANIMATION && _timeAnimation >= 0.025) {
            _timeAnimation -= 0.025;
            this->getAnimation().setRaylibAnimeFrameCounetr(1, MODEL_IDDLE);
        }
        while (_type == GAMEANIMATION && _timeAnimation >= 0.025) {
            _timeAnimation -= 0.025;
            this->getAnimation().setRaylibAnimeFrameCounetr(1, MODEL_ACTION);
            this->getAnimation().setRaylibAnimeFrameCounetr(1, MODEL_IDDLE);
            this->getAnimation().setRaylibAnimeFrameCounetr(1, MODEL_DEATH);
        }
    }

    void AnimationComponent::draw(IGraphic &libGraphic) {}

    IAnimation &AnimationComponent::getAnimation() {
        return *_animation;
    }

}