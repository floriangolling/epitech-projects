//
// Created by jbroesch on 6/16/21.
//

#include "PauseComponent.hpp"
#include "../Manager.hpp"

namespace Indie {

    PauseComponent::PauseComponent() {
        
    }

    void PauseComponent::init(IGraphic *libgraphic) {
    }

    void PauseComponent::update(double time) {
        (void)time;
    }

    void PauseComponent::setIsPause(bool set) {
        _isPause = set;
    }

    bool PauseComponent::getIsPause() {
        return _isPause;
    }

}