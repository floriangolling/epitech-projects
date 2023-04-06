//
// Created by Nicolas on 4/6/21.
//
#include <iostream>
#include "Clock.hpp"

Clock::Clock() {
    reset();
}

Clock::~Clock() {

}

void Clock::reset() {
    breakpoint = std::chrono::system_clock::now();
}

float Clock::getElapsedTimeSinceLastReset() {
    std::chrono::duration<float> ret = std::chrono::system_clock::now() - breakpoint;
    return ret.count();
}

float Clock::getElapsedTimeSinceLastCall() {
    std::chrono::duration<float> ret = std::chrono::system_clock::now() - lastCall;
    lastCall = std::chrono::system_clock::now();
    return ret.count();
}

