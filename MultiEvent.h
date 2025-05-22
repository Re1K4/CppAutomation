#pragma once
#include "Event.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include "Logger.h"
#include <windows.h>
#include <sstream>
#include <stdexcept>

enum MatchMode {
    ALL_MATCH,
    ANY_MATCH
};

class MultiEvent {
public:
    // Receive multiple Events with variable argument templates
    template<typename... Events>
    MultiEvent(Events&... events) {
        static_assert(sizeof...(events) >= 2, "MultiEvent requires at least two Event objects.");
        (eventList.push_back(&events), ...); //Variable Argument Expansion
        hScreen = GetDC(NULL);
        calculateBoundingRect();
    }

    ~MultiEvent();

    bool checkColorMulti(MatchMode mode = ALL_MATCH, bool debugFlag = false);
    bool checkRGBMulti(MatchMode mode = ALL_MATCH, bool debugFlag = false);

private:
    std::vector<Event*> eventList;
    cv::Rect boundingRect;
    cv::Mat screenCapture;
    HDC hScreen;

    void calculateBoundingRect();
    void captureScreen();
    cv::Vec3b getPixelFromCapture(int x, int y);
};