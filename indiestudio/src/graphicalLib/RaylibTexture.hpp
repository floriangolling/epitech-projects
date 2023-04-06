//
// Created by jbroesch on 5/25/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ATEXTURE_HPP
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ATEXTURE_HPP

#include "ITexture.hpp"
#include "../utils/utils.hpp"
#include "raylib.h"

namespace Indie {

    class RaylibTexture : public ITexture {
    public:
        void setTexture(const char *fp) override;
        float textureGetHeight() override;
        float textureGetWidth() override;
        Texture2D &getTexture();
    private:
        Texture2D _texture;
    };

}

#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ATEXTURE_HPP
