//
// Created by dmitry on 04/10/2021.
//

#include <iostream>
#include "Opus.hpp"

Opus::Opus()
{
    _encode = opus_encoder_create(48000, 2, OPUS_APPLICATION_VOIP, &_error);
    if (_error != OPUS_OK)
        return;
    _decode = opus_decoder_create(48000, 2, &_error);
    if (_error != OPUS_OK)
        return;
}

Opus::~Opus()
{
}

std::vector<unsigned char> Opus::func_encode(std::vector<float> decode)
{
    std::vector<unsigned char> enc;
    if (decode.size() == 0) {
        enc.resize(0);
        return enc;
    }
    enc.resize(static_cast<int>(decode.size()) * 2);
    int res = opus_encode_float(_encode, decode.data(), 480, enc.data(), static_cast<int>(enc.size()) * 2);
    if (res < 0) {
        std::cout << "Fail to encode" << std::endl;
    }
    if (res > 0) {
        enc.resize(res);
    }
    return enc;
}

std::vector<float> Opus::func_decode(std::vector<unsigned char> encodepacket)
{
    std::vector<float> dec;
    if (encodepacket.size() == 0) {
        dec.resize(0);
        return dec;
    }
    dec.resize(480 * 2);
    int res = opus_decode_float(_decode, encodepacket.data(), static_cast<int>(encodepacket.size()), dec.data(), 480, 0) * 2;
    if (res > 0) {
        dec.resize(res);
    }
    return dec;
}
