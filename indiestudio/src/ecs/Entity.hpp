//
// Created by jbroesch on 5/19/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ENTITY_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ENTITY_H

#include "Component.hpp"
#include <cstddef>
#include <iostream>
#include <array>
#include <bitset>
#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>

namespace Indie {

    class IGraphic;
    typedef std::size_t ComponentID;
    ComponentID getComponentTypeID();
    template <typename T> ComponentID getComponentTypeID() noexcept {
        static ComponentID typeID = getComponentTypeID();
        return typeID;
    }
    constexpr std::size_t maxComponents = 32;

    using ComponentBitset = std::bitset<maxComponents>;
    using ComponentArray = std::array<std::shared_ptr<Component>, maxComponents>;
    class Entity {
        private:
            bool _alive = true;
            std::vector<std::shared_ptr<Component>> _components;
            ComponentArray componentArray;
            ComponentBitset componentBitset;
        public:
            void update(double time);
            void draw(IGraphic &libGraphic);
            bool isAlive() const;
            void destroy();

            template <typename T> bool hasComponent() const {
                return componentBitset[getComponentTypeID<T>()];
            }

            template <typename T, typename... TArgs>
            std::shared_ptr<T> AddComponent(IGraphic *libgraphic, TArgs&&... mArgs) {
                std::shared_ptr<T> c = std::make_shared<T>(std::forward<TArgs>(mArgs)...);
                c->_entity = this;
                _components.emplace_back(c);

                componentArray[getComponentTypeID<T>()] = c;
                componentBitset[getComponentTypeID<T>()] = true;

                c->init(libgraphic);
                return c;
            }

            template <typename T> T &getComponent() const {
                std::shared_ptr<Component> ptr = componentArray[getComponentTypeID<T>()];
                return *(T *)(ptr.get());
            }
    };

}


#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ENTITY_H
