#include "MultiEvent.h"

MultiEvent::~MultiEvent() {
    if (hScreen) {
        ReleaseDC(NULL, hScreen);
        hScreen = nullptr;
    }
}

void MultiEvent::calculateBoundingRect() {
    int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;

    for (const auto& e : eventList) {
        int x = e->x;
        int y = e->y;

        minX = std::min(minX, x);
        minY = std::min(minY, y);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
    }

    boundingRect = cv::Rect(minX, minY, maxX - minX + 1, maxY - minY + 1);
}

void MultiEvent::captureScreen() {
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, boundingRect.width, boundingRect.height);
    SelectObject(hDC, hBitmap);

    BitBlt(hDC, 0, 0, boundingRect.width, boundingRect.height, hScreen,
        boundingRect.x, boundingRect.y, SRCCOPY);

    BITMAPINFOHEADER bi = {};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = boundingRect.width;
    bi.biHeight = -boundingRect.height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    int imageSize = boundingRect.width * boundingRect.height * 4;
    std::vector<uchar> buffer(imageSize);
    GetDIBits(hDC, hBitmap, 0, boundingRect.height, buffer.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    cv::Mat tmp(boundingRect.height, boundingRect.width, CV_8UC4, buffer.data());
    cv::cvtColor(tmp, screenCapture, cv::COLOR_BGRA2BGR);

    DeleteObject(hBitmap);
    DeleteDC(hDC);
}

cv::Vec3b MultiEvent::getPixelFromCapture(int x, int y) {
    int localX = x - boundingRect.x;
    int localY = y - boundingRect.y;
    return screenCapture.at<cv::Vec3b>(localY, localX);
}

bool MultiEvent::checkColorMulti(MatchMode mode, bool debugFlag) {
    captureScreen();

    for (const auto& e : eventList) {
        int x = e->x;
        int y = e->y;
        COLORREF target = e->c;
        int fazzy = e->fazzy;

        cv::Vec3b pixel = getPixelFromCapture(x, y);
        COLORREF screenColor = RGB(pixel[2], pixel[1], pixel[0]);

        int r_diff = std::abs(GetRValue(screenColor) - GetRValue(target));
        int g_diff = std::abs(GetGValue(screenColor) - GetGValue(target));
        int b_diff = std::abs(GetBValue(screenColor) - GetBValue(target));
        bool match = (r_diff <= fazzy && g_diff <= fazzy && b_diff <= fazzy);

        if (debugFlag) {
            std::ostringstream oss;
            oss << "bool [" << match << "] / screen[RGB("
                << int(GetRValue(screenColor)) << ","
                << int(GetGValue(screenColor)) << ","
                << int(GetBValue(screenColor)) << ")] : event[RGB("
                << int(GetRValue(target)) << ","
                << int(GetGValue(target)) << ","
                << int(GetBValue(target)) << ")] / xy("
                << x << "," << y << ")";
            Logger::info(oss.str());
        }

        if (mode == ALL_MATCH) {
            if (!match) return false;
        }
        else {  // ANY_MATCH
            if (match) return true;
        }
    }

    return (mode == ALL_MATCH);
}

bool MultiEvent::checkRGBMulti(MatchMode mode, bool debugFlag) {
    captureScreen();

    for (const auto& e : eventList) {
        int x = e->x;
        int y = e->y;
        std::string type = e->colorType;

        cv::Vec3b pixel = getPixelFromCapture(x, y);
        cv::Mat bgr(1, 1, CV_8UC3, pixel);
        cv::Mat hsv;
        cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);

        cv::Vec3b hsvVal = hsv.at<cv::Vec3b>(0, 0);
        int hue = hsvVal[0] * 2;
        int sat = hsvVal[1];
        int val = hsvVal[2];

        if (sat <= 102 || val <= 25) {
            if (debugFlag) {
                std::ostringstream oss;
                oss << "Ignoring due to low S or V: S [" << sat << "] V [" << val << "] at xy(" << x << "," << y << ")";
                Logger::info(oss.str());
            }

            if (mode == ALL_MATCH) {
                return false;
            }
            else {
                continue;  // ANY_MATCH ignores this event
            }
        }

        bool match = false;
        if (type == "RED")    match = (hue >= 0 && hue <= 30) || (hue >= 331 && hue <= 360);
        if (type == "ORANGE") match = (hue >= 31 && hue <= 50);
        if (type == "YELLOW") match = (hue >= 51 && hue <= 70);
        if (type == "GREEN")  match = (hue >= 71 && hue <= 160);
        if (type == "BLUE")   match = (hue >= 161 && hue <= 262);
        if (type == "PURPLE") match = (hue >= 263 && hue <= 330);

        if (debugFlag) {
            std::ostringstream oss;
            oss << "bool [" << match << "] / colortype[" << type << "] : hue[" << hue << "] / xy(" << x << "," << y << ")";
            Logger::info(oss.str());
        }

        if (mode == ALL_MATCH) {
            if (!match) return false;
        }
        else { // ANY_MATCH
            if (match) return true;
        }
    }

    return (mode == ALL_MATCH);
}