/*
** EPITECH PROJECT, 2021
** B-CPP-500-STG-5-1-babel-jean-baptiste.roesch
** File description:
** audio
*/

#include "audio.hpp"
#include <iostream>
#include <fstream>


namespace Audio{
    PAudio::PAudio()
    {
        err = Pa_Initialize();
        _opus = new Opus;
        if (err != paNoError)
            exit(84);
        inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
        if (inputParameters.device == paNoDevice) {
            std::cout << "Error: No default input device.\n" << std::endl;
            exit(84);
        }
        inputParameters.channelCount = 2;                    /* stereo input */
        inputParameters.sampleFormat = PA_SAMPLE_TYPE;
        inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;
        outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
        if (outputParameters.device == paNoDevice) {
            fprintf(stderr,"Error: No default output device.\n");
            exit (84);
        }
        outputParameters.channelCount = 2;                     /* stereo output */
        outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        _record = false;
        _display = false;

        _stream = nullptr;
        _output = nullptr;
    }

    int PAudio::recordCallback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *userData)
    {
        PAudio *p = reinterpret_cast<PAudio *>(userData);
        std::vector<float> dec;
        dec.assign(reinterpret_cast<const float *>(inputBuffer), reinterpret_cast<const float *>(inputBuffer) + framesPerBuffer * 2);
        p->_uq.push(p->_opus->func_encode(dec));
        return 0;
    }
    int PAudio::playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
    {
        PAudio *l = reinterpret_cast<PAudio *>(userData);
        std::vector<float> dec;
        float *wptr = static_cast<float *>(outputBuffer);
        if (l->_outputq.empty())
            return 0;
        dec = l->_opus->func_decode(l->_outputq.front());
        auto it = dec.begin();
        for (int j = 0; j < framesPerBuffer * 2; ++j) {
            if (it != dec.end())
                *(wptr++) = *(it++);
            else
                *(wptr++) = 0;
        }
        l->_outputq.pop();
        return 0;
    }

    void PAudio::startRecord()
    {
        if (_record)
            return;
        err = Pa_OpenStream(
                &_stream,
                &inputParameters,
                nullptr,                  /* &outputParameters, */
                48000,
                480,
                paClipOff,      /* we won't output out of range samples so don't bother clipping them */
                recordCallback,
                this);
        if( err != paNoError ) exit(84);

        err = Pa_StartStream(_stream);
        if( err != paNoError ) exit(84);
        printf("\n=== Now recording!! Please speak into the microphone. ===\n");
        _record = true;
    }

    void PAudio::stopRecord()
    {
        if (!_record)
            return;
        if (Pa_StopStream(_stream) != paNoError) {
            std::cout << "Can't Pa_CloseStream" << std::endl;
            return;
        }
        if (Pa_CloseStream(_stream) != paNoError) {
            std::cout << "Can't Pa_CloseStream" << std::endl;
            return;
        }
        _record = false;
    }

    void PAudio::startDisplay()
    {
        if (_display)
            return;
        if (Pa_OpenStream(&_output, nullptr, &outputParameters, 48000, 480, paClipOff, playCallback, this) != paNoError) {
            std::cout << "Can't Pa_OpenStream" << std::endl;
            return;
        }
        if (Pa_StartStream(_output) != paNoError) {
            std::cout << "Can't Pa_StartStream" << std::endl;
            return;
        }
        _display = true;
    }

    void PAudio::stopDisplay()
    {
        if (!_display)
            return;
        if (Pa_StopStream(_output) != paNoError) {
            std::cout << "Can't Pa_CloseStream" << std::endl;
            return;
        }
        if (Pa_CloseStream(_output) != paNoError) {
            std::cout << "Can't Pa_CloseStream" << std::endl;
            return;
        }
        _display = false;
    }

    const std::queue<std::vector<unsigned char>> &PAudio::getUq() const {
        return _uq;
    }

    const std::queue<std::vector<unsigned char>> &PAudio::getOutputq() const {
        return _outputq;
    }

    void PAudio::setOutputq(std::vector<unsigned char>outputq) {
        _outputq.push(outputq);
    }

    void PAudio::set_popback_uq() {
        _uq.pop();
    }

    PAudio::~PAudio() = default;
}

