//
// Created by jbroesch on 5/27/21.
//

#include "BonusComponent.hpp"

namespace Indie {

    BonusComponent::BonusComponent(BonusComponent::TypeBonus type, float x, float y) {
        _x = x;
        _z = y;
        _type = type;
        _isUsed = false;
    }

    void BonusComponent::init(IGraphic *libgraphic) {
        (void)libgraphic;
    }

    void BonusComponent::setIsUsed() {
        _isUsed = true;
    }

    bool BonusComponent::getIsUsed() {
        return (_isUsed);
    }

    BonusComponent::TypeBonus BonusComponent::getType() {
        return (_type);
    }

    std::pair<float, float> BonusComponent::getPos() {
        return (std::make_pair(_x, _z));
    }

    void BonusComponent::update(double time) {
        (void)time;
    }

    void BonusComponent::draw(IGraphic &libgraphic) {
        libgraphic.myDraw(this);
    }
}