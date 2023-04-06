//
// Created by Nicolas on 4/6/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_CLOCK_HPP
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_CLOCK_HPP


#include <chrono>

class Clock {
public:
    Clock();
    ~Clock();
    void reset();
    float getElapsedTimeSinceLastReset();
    float getElapsedTimeSinceLastCall();
private:
    std::chrono::system_clock::time_point breakpoint;
    std::chrono::system_clock::time_point lastCall;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_CLOCK_HPP
