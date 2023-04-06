#include "PacketEncoder.hpp"
#include "utils.hpp"
#include <cstring>

PacketEncoder::PacketEncoder() {

}

PacketEncoder::~PacketEncoder() {

}

void PacketEncoder::addBool(bool b) {
    std::pair<type, bool> pair;
    pair.first = BOOLTYPEENCODER;
    pair.second = b;
    _dataVector.push_back(pair);
}

void PacketEncoder::addInt(int number) {
    std::pair<type, int> pair;
    pair.first = INTTYPEENCODER;
    pair.second = number;
    _dataVector.push_back(pair);}

void PacketEncoder::addString(std::string str) {
    std::pair<type, std::string> pair;
    pair.first = STRINGTYPEENCODER;
    pair.second = str;
    _dataVector.push_back(pair);}

std::vector<uint8_t> PacketEncoder::createPacket(int code) {
    char strTYPE = STRINGTYPEENCODER;
    char intTYPE = INTTYPEENCODER;
    char boolTYPE = BOOLTYPEENCODER;

    Header header = {};
    int totalSize = sizeof(Header);
    header.code = code;
    header.magicNumber = 69420;
    int indexSizeMemory = sizeof(Header);

    for (auto it = _dataVector.begin(); it != _dataVector.end(); it++) {
        if (it->first == BOOLTYPEENCODER) {
            totalSize += sizeof(bool) + sizeof(char);
        } else if (it->first == INTTYPEENCODER) {
            totalSize += sizeof(int) + sizeof(char);
        } else if (it->first == STRINGTYPEENCODER) {
            totalSize += sizeof(char) + sizeof(int) + std::get<std::string>(it->second).size() * sizeof(char);
        }
    }
    std::vector<uint8_t> buffer(totalSize, '\0');
    header.size = totalSize;

    std::memcpy(buffer.data(), &header, sizeof(Header));

    for (auto it = _dataVector.begin(); it != _dataVector.end(); it++) {
        if (it->first == BOOLTYPEENCODER) {
            std::memcpy(buffer.data() + indexSizeMemory, &boolTYPE, sizeof(char));
            indexSizeMemory += sizeof(char);
            std::memcpy(buffer.data() + indexSizeMemory, &it->second, sizeof(bool));
            indexSizeMemory += sizeof(bool);
        } else if (it->first == INTTYPEENCODER) {
            std::memcpy(buffer.data() + indexSizeMemory, &intTYPE, sizeof(char));
            indexSizeMemory += sizeof(char);
            std::memcpy(buffer.data() + indexSizeMemory, &it->second, sizeof(int));
            indexSizeMemory += sizeof(int);
        } else if (it->first == STRINGTYPEENCODER) {
            std::memcpy(buffer.data() + indexSizeMemory, &strTYPE, sizeof(char));
            indexSizeMemory += sizeof(char);
            int size = std::get<std::string>(it->second).size();
            std::string str = std::get<std::string>(it->second);
            std::memcpy(buffer.data() + indexSizeMemory, &size, sizeof(int));
            indexSizeMemory += sizeof(int);
            std::memcpy(buffer.data() + indexSizeMemory, str.data(), str.size() * sizeof(char));
            indexSizeMemory += str.size() * sizeof(char);
        }  
    }
    return (buffer);
}