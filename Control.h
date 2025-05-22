#pragma once
#include "Logger.h"

class Control {
public:
    int NOW = 0;
    int PREV = 0;

    Control();

    // Change of control number
    void changeCtrl(int ctrl);

private:
};
