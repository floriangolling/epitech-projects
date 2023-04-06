//
// Created by jbroesch on 6/4/21.
//

#ifndef BOMBERMAN_GENERATEIMAGES_HPP
#define BOMBERMAN_GENERATEIMAGES_HPP
#include <utility>
#include <array>

namespace Indie {

    unsigned decodeBMP(std::vector<unsigned char>& image, unsigned& w, unsigned& h, const std::vector<unsigned char>& bmp);
    void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName);
    unsigned char* createBitmapFileHeader (int height, int stride);
    unsigned char* createBitmapInfoHeader (int height, int width);
    std::pair<int, std::array<std::string, 13>> createMap();
    int updateMap(std::array<std::string, 13> &map);
}
#endif //BOMBERMAN_GENERATEIMAGES_HPP
