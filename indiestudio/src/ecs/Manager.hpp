//
// Created by jbroesch on 5/19/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MANAGER_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MANAGER_H

#include "Entity.hpp"
#include <map>

namespace Indie {

    class Manager {
    public :
        Manager();
        void update(double time);
        void draw(IGraphic &libGraphic);
        void refresh();
        std::shared_ptr<Entity> addEntity(std::string);
        std::map<std::string, std::shared_ptr<Entity>> &getEntities();
    private:
        std::map<std::string, std::shared_ptr<Entity>> _entities;
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_MANAGER_H
