#pragma once
#include "Logger.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <windows.h>


class TemplateMatching {
public:
    cv::Rect lastMatchResult;
    /* Retrieve image files from directory Path
    TemplateMatching(const std::string& filename);
    */
    TemplateMatching(int resourceId);
    ~TemplateMatching();
    bool match(const cv::Rect& region, double fuzzy);
    bool matchBinary(const cv::Rect& region, double fuzzy);

private:
    HDC hScreenDC;
    cv::Mat image;
    cv::Mat captureScreen(const cv::Rect& region);
    cv::Mat loadResourceData(int resourceId);
};
