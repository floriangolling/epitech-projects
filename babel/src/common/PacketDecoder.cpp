#include "PacketDecoder.hpp"

PacketDecoder::PacketDecoder() {
    this->_code = -1;
    this->_packetSize = -1;
    this->_magicNumber = -1;
}

PacketDecoder::~PacketDecoder() {

}

void PacketDecoder::decodeHeader(std::vector<uint8_t> *package) {
    Header header = {};


    std::memcpy(&header, package->data(), sizeof(Header));
    this->_magicNumber = header.magicNumber;
    this->_packetSize = header.size;
    this->_code = header.code;
}

void PacketDecoder::decodePacket(std::vector<uint8_t> *data) {
    int indexMemory = sizeof(Header);
    int readSize = sizeof(Header);

    while (readSize < this->_packetSize) {
        char type;

        std::memcpy(&type, data->data() + readSize, sizeof(char));
        readSize += sizeof(char);
        if (type == STRINGTYPEENCODER) {
            char *finalString;
            int sizeString;
            std::memcpy(&sizeString, data->data() + readSize, sizeof(int));
            readSize += sizeof(int);
            std::string str(sizeString + 1, '\0');
            std::memcpy(str.data(), data->data() + readSize, sizeof(char) * sizeString);
            readSize += (sizeof(char) * sizeString);
            _dataVector.push_back(std::make_pair(STRINGTYPEENCODER, str));
        } else if (type == BOOLTYPEENCODER) {
            bool b;
            std::memcpy(&b, data->data() + readSize, sizeof(bool));
            readSize += sizeof(bool);
            _dataVector.push_back(std::make_pair(BOOLTYPEENCODER, b));
        } else if (type == INTTYPEENCODER) {
            int number;
            std::memcpy(&number, data->data() + readSize, sizeof(int));
            readSize += sizeof(int);
            _dataVector.push_back(std::make_pair(INTTYPEENCODER, number));
        }
    }
}

int PacketDecoder::getCode() {
    return (_code);
}

int PacketDecoder::getMagicNumber() {
    return (_magicNumber);
}

int PacketDecoder::getPacketSize() {
    return (this->_packetSize);
}

std::vector<std::pair<type, std::variant<int, std::string, bool>>> PacketDecoder::getDataVector() {
    return _dataVector;
}