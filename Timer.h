#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void set();          // Set timer
    double distance();   // Obtain elapsed time
    void reset();        // Reset the timer

private:
    std::chrono::time_point<std::chrono::steady_clock> setTime;  // time variable
    bool usedFlg;  // use flag
};