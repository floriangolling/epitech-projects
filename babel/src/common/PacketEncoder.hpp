#ifndef COMMONPACKETHANDLER
#define COMMONPACKETHANDLER

#include <iostream>
#include <vector>
#include <utility>
#include <variant>
#include <filesystem>
#include "utils.hpp"

class PacketEncoder {
    public:
        PacketEncoder();
        PacketEncoder(const PacketEncoder&) =delete;
        PacketEncoder& operator=(const PacketEncoder&) =delete;
        ~PacketEncoder();
        std::vector<uint8_t> createPacket(int code);
        void addString(std::string str);
        void addInt(int);
        void addBool(bool);        
    private:
        std::vector<std::pair<type, std::variant<int, std::string, bool>>> _dataVector;
};

#endif

/*
HEADER
    MAGICNUMEBRint 
    PACKET SIZE
    CODE

ARG TYPe -> char

...

ARG TYPE -> INT


...


int total_size = 0;

total_size += taille header

for args {
    if (bool) total_size += taille char + taille char
    if (int) total_size += taille char + taille int
    if (string) total_size += taille char + taille int + (len string * taille char)
 }


std:vector<uint8> buffer(total_size, '\0');
Header header = {MAGIC, code, total_size};

std:memcpy(*buffer (en gros get le pointeur), &header, taille header);
indexmemory = sizeof(Header);
for args{

    std::memcpy(*buffer + indexMemory, &type, taille type);
    indexmemory += taille type;

    if (string) {
         std::memcpy(*buffer + indexMemory, &strlength, taille int);
        indexmemory += taille int;

        std::memcpy(*buffer + indexMemory, str.c_str(), taille char * length);
        ndexmemory += taille char * length;
    } else {
    std::memcpy(*buffer + indexMemory, &data, tailledata);
    indexmemory += tailledata;
    }
    

}


char *whatiread = read.socket();
Header header = {};
std::memcpy(&header, whatiread, taille header);

*/
