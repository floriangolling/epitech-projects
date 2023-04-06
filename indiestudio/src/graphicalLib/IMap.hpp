//
// Created by jbroesch on 6/4/21.
//

#ifndef BOMBERMAN_IMAP_HPP
#define BOMBERMAN_IMAP_HPP

#include "raylib.h"
#include "../utils/utils.hpp"

namespace Indie {

    class IMap {
    public:
        virtual void setMap(Vector meshPos, Vector mapPos, char *fp, short map_type, ...) = 0;
    };

}

#endif //BOMBERMAN_IMAP_HPP
