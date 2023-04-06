//
// Created by jbroesch on 6/4/21.
//

#include "../lodepng/lodepng.h"
#include "GenerateImages.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

namespace Indie {

    unsigned decodeBMP(std::vector<unsigned char>& image, unsigned& w, unsigned& h, const std::vector<unsigned char>& bmp) {
        static const unsigned MINHEADER = 54;

        if (bmp.size() < MINHEADER) return -1;
        if (bmp[0] != 'B' || bmp[1] != 'M')
            return 1;
        unsigned pixeloffset = bmp[10] + 256 * bmp[11];

        w = bmp[18] + bmp[19] * 256;
        h = bmp[22] + bmp[23] * 256;

        if (bmp[28] != 24 && bmp[28] != 32)
            return 2;
        unsigned numChannels = bmp[28] / 8;

        unsigned scanlineBytes = w * numChannels;
        if(scanlineBytes % 4 != 0) scanlineBytes = (scanlineBytes / 4) * 4 + 4;

        unsigned dataSize = scanlineBytes * h;
        if(bmp.size() < dataSize + pixeloffset) return 3;

        image.resize(w * h * 4);

        for(unsigned y = 0; y < h; y++)
            for(unsigned x = 0; x < w; x++) {

                unsigned bmpos = pixeloffset + (h - y - 1) * scanlineBytes + numChannels * x;
                unsigned newpos = 4 * y * w + 4 * x;
                if(numChannels == 3) {
                    image[newpos + 0] = bmp[bmpos + 2]; //R
                    image[newpos + 1] = bmp[bmpos + 1]; //G
                    image[newpos + 2] = bmp[bmpos + 0]; //B
                    image[newpos + 3] = 255;            //A
                } else {
                    image[newpos + 0] = bmp[bmpos + 2]; //R
                    image[newpos + 1] = bmp[bmpos + 1]; //G
                    image[newpos + 2] = bmp[bmpos + 0]; //B
                    image[newpos + 3] = bmp[bmpos + 3]; //A
                }
            }
        return 0;
    }

    const int BYTES_PER_PIXEL = 3;
    const int FILE_HEADER_SIZE = 14;
    const int INFO_HEADER_SIZE = 40;

    void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
    {
        int widthInBytes = width * BYTES_PER_PIXEL;

        unsigned char padding[3] = {0, 0, 0};
        int paddingSize = (4 - (widthInBytes) % 4) % 4;

        int stride = (widthInBytes) + paddingSize;

        FILE* imageFile = fopen(imageFileName, "wb");

        unsigned char* fileHeader = createBitmapFileHeader(height, stride);
        fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

        unsigned char* infoHeader = createBitmapInfoHeader(height, width);
        fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

        int i;
        for (i = 0; i < height; i++) {
            fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
            fwrite(padding, 1, paddingSize, imageFile);
        }

        fclose(imageFile);
    }

    unsigned char* createBitmapFileHeader (int height, int stride)
    {
        int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

        static unsigned char fileHeader[] = {
                0,0,     /// signature
                0,0,0,0, /// image file size in bytes
                0,0,0,0, /// reserved
                0,0,0,0, /// start of pixel array
        };

        fileHeader[0] = (unsigned char)('B');
        fileHeader[1] = (unsigned char)('M');
        fileHeader[2] = (unsigned char)(fileSize);
        fileHeader[3] = (unsigned char)(fileSize >> 8);
        fileHeader[4] = (unsigned char)(fileSize >> 16);
        fileHeader[5] = (unsigned char)(fileSize >> 24);
        fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

        return fileHeader;
    }

    unsigned char* createBitmapInfoHeader (int height, int width)
    {
        static unsigned char infoHeader[] = {
                0,0,0,0, /// header size
                0,0,0,0, /// image width
                0,0,0,0, /// image height
                0,0,     /// number of color planes
                0,0,     /// bits per pixel
                0,0,0,0, /// compression
                0,0,0,0, /// image size
                0,0,0,0, /// horizontal resolution
                0,0,0,0, /// vertical resolution
                0,0,0,0, /// colors in color table
                0,0,0,0, /// important color count
        };

        infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
        infoHeader[4] = (unsigned char)(width);
        infoHeader[5] = (unsigned char)(width >> 8);
        infoHeader[6] = (unsigned char)(width >> 16);
        infoHeader[7] = (unsigned char)(width >> 24);
        infoHeader[8] = (unsigned char)(height);
        infoHeader[9] = (unsigned char)(height >> 8);
        infoHeader[10] = (unsigned char)(height >> 16);
        infoHeader[11] = (unsigned char)(height >> 24);
        infoHeader[12] = (unsigned char)(1);
        infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

        return infoHeader;
    }

    static std::array<std::string, 13>fillStructMap(const char *pathMap) {
        std::array<std::string, 13> map;
        std::ifstream myFile(pathMap);
        std::string string;

        if (myFile.is_open()) {
            for (int i = 0; getline(myFile,string) && i < 13; i++) {
                std::replace(string.begin(), string.end(), '\n', '\0');
                map[i] = string;
            }
            myFile.close();
        }
        return map;
    }

    static int countCharacter(std::string string) {
        int count = 0;
        for (int y = 1; y < string.size() - 1; y++)
            if (string[y] == ' ')
                count++;
        return count;
    }

    static std::array<std::string, 13> addRandomBlock(std::array<std::string, 13> map) {
        int random = 0;
        for (int i = 1; i <= 6; i ++) {
            for (int j = 1; j <= 7; j++) {
                random = rand() % 4;
                if (map[i][j] == ' ' && (i != 1 || j != 1) && (i != 1 || j != 2) && (i != 2 || j != 1) && random != 0) {
                    map[i][j] = 'B';
                }
            }
        }
        for (int i = 1; i <= 6; i++) {
            for (int j = 13; j > 7; j--) {
                map[i][j] = map[i][14 - j];
            }
        }
        for (int i = 7; i <= 11; i++) {
            for (int j = 1; j <= 13; j++) {
                map[i][j] = map[12 - i][j];
            }
        }
        return map;
    }

    int bmpToPng(char *imageFileName)
    {
        std::vector<unsigned char> bmp;
        lodepng::load_file(bmp, imageFileName);
        std::vector<unsigned char> image;
        unsigned w, h;
        unsigned error = decodeBMP(image, w, h, bmp);

        if(error) {
            std::cout << "BMP decoding error " << error << std::endl;
            return 0;
        }

        std::vector<unsigned char> png;
        error = lodepng::encode(png, image, w, h);

        if(error) {
            std::cout << "PNG encoding error " << error << ": " << lodepng_error_text(error) << std::endl;
            return 0;
        }

        lodepng::save_file(png, "../assets/maps/mapBox.png");
        return 1;
    }

    std::pair<int, std::array<std::string, 13>> createMap()
    {
        srand(time(nullptr));
        const char *pathMap[2] {"../assets/maps/mapInitial.txt", "../assets/maps/mapOne.txt"};
        int itMap = 0;
        std::array<std::string, 13> myMap = fillStructMap(pathMap[itMap]);

        myMap = addRandomBlock(myMap);
        const int height = 13;
        const int width = 15;
        unsigned char imageBMP[height][width][BYTES_PER_PIXEL];
        char* imageFileName = (char*) "../assets/maps/bitmapImage.bmp";

        int i, j;
        int x = 12;
        for (i = 0; i < height; i++, x--) {
            for (j = 0; j < width; j++) {
                if (myMap[x][j] == 'B') {
                    imageBMP[i][j][2] = (unsigned char) (255);
                    imageBMP[i][j][1] = (unsigned char) (255);
                    imageBMP[i][j][0] = (unsigned char) (255);
                } else {
                    imageBMP[i][j][2] = (unsigned char) (0);
                    imageBMP[i][j][1] = (unsigned char) (0);
                    imageBMP[i][j][0] = (unsigned char) (0);
                }

            }
        }

        generateBitmapImage((unsigned char*) imageBMP, height, width, imageFileName);

        bmpToPng(imageFileName);
        return std::pair<int, std::array<std::string, 13>>(itMap, myMap);
    }
    int updateMap(std::array<std::string, 13> &map)
    {
        const int height = 13;
        const int width = 15;
        unsigned char imageBMP[height][width][3];
        char* imageFileName = (char*) "../assets/maps/bitmapImage.bmp";

        int i, j;
        int x = 12;
        for (i = 0; i < height; i++, x--) {
            for (j = 0; j < width; j++) {
                if (map[x][j] == 'B') {
                    imageBMP[i][j][2] = (unsigned char) (255);
                    imageBMP[i][j][1] = (unsigned char) (255);
                    imageBMP[i][j][0] = (unsigned char) (255);
                } else {
                    imageBMP[i][j][2] = (unsigned char) (0);
                    imageBMP[i][j][1] = (unsigned char) (0);
                    imageBMP[i][j][0] = (unsigned char) (0);
                }

            }
        }

        generateBitmapImage((unsigned char*) imageBMP, height, width, imageFileName);

        std::vector<unsigned char> bmp;
        lodepng::load_file(bmp, imageFileName);
        std::vector<unsigned char> image;
        unsigned w, h;
        unsigned error = decodeBMP(image, w, h, bmp);

        if(error) {
            std::cout << "BMP decoding error " << error << std::endl;
            return 0;
        }

        std::vector<unsigned char> png;
        error = lodepng::encode(png, image, w, h);

        if(error) {
            std::cout << "PNG encoding error " << error << ": " << lodepng_error_text(error) << std::endl;
            return 0;
        }

        lodepng::save_file(png, "../assets/maps/mapBox.png");

        return 1;
    }
}
