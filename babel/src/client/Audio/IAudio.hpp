//
// Created by jbroesch on 10/16/21.
//

#ifndef BABEL_IAUDIO_HPP
#define BABEL_IAUDIO_HPP

namespace Audio{
    class IPAudio {
    public:
        IPAudio() = default;
        IPAudio(const IPAudio&) =delete;
        IPAudio& operator=(const IPAudio&) =delete;
        virtual void startRecord() = 0;
        virtual void stopRecord() = 0;
        virtual void startDisplay() = 0;
        virtual void stopDisplay() = 0;

        [[nodiscard]] virtual const std::queue<std::vector<unsigned char>> &getUq() const = 0;

        [[nodiscard]] virtual const std::queue<std::vector<unsigned char>> &getOutputq() const = 0;

        virtual void setOutputq(std::vector<unsigned char> outputq) = 0;

        virtual void set_popback_uq() = 0;

    };
}

#endif //BABEL_IAUDIO_HPP
