//
// Created by jbroesch on 5/19/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_TEXTURECOMPONENT_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_TEXTURECOMPONENT_H

#include "../Component.hpp"
#include "PositionComponent.hpp"
#include "../../graphicalLib/RaylibTexture.hpp"

namespace Indie {

    class TextureComponent : public Component {
    public:
        explicit TextureComponent(const char *fp=nullptr);
        ~TextureComponent() override = default;
        void init(IGraphic *libgraphic) override;
        ITexture &getTexture();
        void update(double time) override;
        void draw(IGraphic &libGraphic) override;
    private:
        Vector _position;
        const char *_fp;
        ITexture *_texture;
    };

}

#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_TEXTURECOMPONENT_H
