#pragma once
#include <windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "Emulate.h"

class Action {
public:
    static void sample();

private:
    Action() = delete;
};