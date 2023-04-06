#ifndef COMMONPACKETHANDLERDECODER
#define COMMONPACKETHANDLERDECODER

#include <variant>
#include <vector>
#include "utils.hpp"
#include <iostream>
#include <cstring>

class PacketDecoder {
    public:
        PacketDecoder();
        PacketDecoder(const PacketDecoder&) =delete;
        PacketDecoder& operator=(const PacketDecoder&) =delete;
        ~PacketDecoder();
        void decodeHeader(std::vector<uint8_t> *);
        void decodePacket(std::vector<uint8_t> *);
        int getCode();
        int getMagicNumber();
        int getPacketSize();
        std::vector<std::pair<type, std::variant<int, std::string, bool>>> getDataVector();
    private:
        std::vector<std::pair<type, std::variant<int, std::string, bool>>> _dataVector;
        int _code;
        int _magicNumber;
        int _packetSize;
};

#endif