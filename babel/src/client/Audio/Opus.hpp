//
// Created by dmitry on 04/10/2021.
//

#ifndef BABEL_OPUS_HPP
#define BABEL_OPUS_HPP

#include "opus.h"
#include <vector>
#include "IOpus.hpp"

class Opus : public IOpus{
public:
    Opus();
    ~Opus();
    Opus(const Opus&) =delete;
    Opus& operator=(const Opus&) =delete;
    std::vector<unsigned char> func_encode(std::vector<float>) override;
    std::vector<float> func_decode(std::vector<unsigned char>) override;
private:
    OpusEncoder *_encode;
    OpusDecoder *_decode;
    int _error;
};


#endif //BABEL_OPUS_HPP
