#pragma once
#include "Logger.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <opencv2/opencv.hpp>

class Event {
public:
    // Constructor
    Event(int check_x, int check_y, COLORREF check_color, int fazzy, const std::string& colorType);

    //DeConstructor
    ~Event();

    // Check color
    bool checkColor(bool debugFlag = false);

    // Check RGB Category
    bool checkRGB(bool debugFlag = false);

    int x, y;          // Pixel Coordinates
    COLORREF c;        // Color to be checked (RGB)
    int fazzy;
    std::string colorType;

private:
    HDC hdc;
};