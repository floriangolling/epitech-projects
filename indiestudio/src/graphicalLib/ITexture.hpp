//
// Created by jbroesch on 5/25/21.
//

#ifndef B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ITEXTURE_H
#define B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ITEXTURE_H

namespace Indie {

    class ITexture {
    public:
        virtual void setTexture(const char *fp) = 0;
        virtual float textureGetHeight() = 0;
        virtual float textureGetWidth() = 0;
    };

}

#endif //B_YEP_400_STG_4_1_INDIESTUDIO_NICOLAS_SCHNEIDER_ITEXTURE_H
