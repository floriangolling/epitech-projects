//
// Created by jbroesch on 10/16/21.
//

#ifndef BABEL_IOPUS_HPP
#define BABEL_IOPUS_HPP

class IOpus {
public:
    IOpus() = default;
    IOpus(const IOpus&) =delete;

    virtual IOpus& operator=(const IOpus&) =delete;
    virtual std::vector<unsigned char> func_encode(std::vector<float>) = 0;
    virtual std::vector<float> func_decode(std::vector<unsigned char>) = 0;
};

#endif //BABEL_IOPUS_HPP
