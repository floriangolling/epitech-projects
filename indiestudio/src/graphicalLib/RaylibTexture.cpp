//
// Created by jbroesch on 6/1/21.
//

#include "RaylibTexture.hpp"
#include <sstream>

namespace Indie {

    void RaylibTexture::setTexture(const char *fp) {
        _texture = LoadTexture(fp);
        if (_texture.id == 0) {
            std::stringstream ss;
            ss << "Error : Not a valid file" << fp << ", exiting";
            std::string file_error = ss.str();
            throw std::runtime_error(file_error);
        }
    }
    float RaylibTexture::textureGetHeight() {
        return (float)_texture.height;
    }
    float RaylibTexture::textureGetWidth() {
        return (float)_texture.width;
    }

    Texture2D &RaylibTexture::getTexture() {
        return _texture;
    }

}