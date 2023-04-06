/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-jean-baptiste.roesch
** File description:
** audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <portaudio.h>
#include <vector>
#include <queue>
#include "Opus.hpp"
#include "IAudio.hpp"

#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)

namespace Audio{
    class PAudio : public IPAudio {
    public:
        typedef struct {
            int frameIndex;
            int maxFrameIndex;
            std::vector<float> recordedSamples;
        } paTestData;

        PAudio();
        PAudio(const PAudio&) =delete;
        PAudio& operator=(const PAudio&) =delete;
        ~PAudio();
        void startRecord() override;
        void stopRecord() override;
        void startDisplay() override;
        void stopDisplay() override;

        [[nodiscard]] const std::queue<std::vector<unsigned char>> &getUq() const override;

        [[nodiscard]] const std::queue<std::vector<unsigned char>> &getOutputq() const override;

        void setOutputq(std::vector<unsigned char> outputq) override;

        void set_popback_uq() override;

    private:
        static int playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);
        static int recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *userData);
        PaStreamParameters inputParameters, outputParameters;
        PaStream *_stream;
        PaStream *_output;
        PaError err = paNoError;
        bool _record;
        bool _display;
        Opus *_opus;
        std::queue<std::vector<unsigned char>> _uq;
        std::queue<std::vector<float>> _inputq;
        std::queue<std::vector<unsigned char>> _outputq;
    };
}

#endif /* !AUDIO_HPP_ */
