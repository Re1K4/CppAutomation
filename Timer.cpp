#include "Timer.h"

Timer::Timer() : setTime(), usedFlg(false) {}

void Timer::set() {
    if (!usedFlg) {
        setTime = std::chrono::steady_clock::now();
        usedFlg = true;
    }
}

double Timer::distance() {
    if (usedFlg) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = currentTime - setTime;
        return elapsed.count();
    }
    return 0.0;  // If not already set
}

void Timer::reset() {
    usedFlg = false;
}