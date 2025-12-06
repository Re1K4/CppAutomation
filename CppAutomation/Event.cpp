#include "Event.h"

Event::Event(int check_x, int check_y, COLORREF check_color, int fazzy, const std::string& colorType)
    : x(check_x), y(check_y), c(check_color), fazzy(fazzy), colorType(colorType) {
    hdc = GetDC(NULL);
}

Event::~Event() {
    ReleaseDC(NULL, hdc);
}

bool Event::checkColor(bool debugFlag) {
    COLORREF pixelColor = GetPixel(hdc, x, y);

    // Calculate the difference of RGB components
    int r_diff = std::abs(GetRValue(pixelColor) - GetRValue(c));
    int g_diff = std::abs(GetGValue(pixelColor) - GetGValue(c));
    int b_diff = std::abs(GetBValue(pixelColor) - GetBValue(c));

    // Check for acceptable match (tolerance)
    bool isMatch = (r_diff <= fazzy) && (g_diff <= fazzy) && (b_diff <= fazzy);

    if (debugFlag) {
        // Output debugging information
        std::ostringstream oss;
        oss << "bool [" <<
            isMatch <<
            "] / screen[RGB(" <<
                int(GetRValue(pixelColor)) << "," << int(GetGValue(pixelColor)) << "," << int(GetBValue(pixelColor)) <<
            ")] : event[RGB(" <<
                int(GetRValue(c)) << "," << int(GetGValue(c)) << "," << int(GetBValue(c)) <<
            ")] / xy(" <<
                x << "," << y <<
            ")";
        Logger::info(oss.str());
    }

    return isMatch;
}

bool Event::checkRGB(bool debugFlag) {
    COLORREF color = GetPixel(hdc, x, y);

    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);

    // Create an OpenCV Mat object
    cv::Mat rgbPixel(1, 1, CV_8UC3, cv::Scalar(blue, green, red)); // OpenCV‚ÍBGR‡

    // RGB to HSV conversion
    cv::Mat hsvPixel;
    cv::cvtColor(rgbPixel, hsvPixel, cv::COLOR_BGR2HSV);

    // Get HSV value
    cv::Vec3b hsv = hsvPixel.at<cv::Vec3b>(0, 0);
    int hue = hsv[0] * 2;       // Converted to 0-360 degrees since the range is 0-179 in OpenCV
    int saturation = hsv[1]; // Saturation (0 - 255)
    int value = hsv[2];     // Value (0 - 255)
    
    // Ignore if Saturation is below 40% (102 in 0-255 range) or Value is below 10% (25.5 in 0-255 range)
    if (saturation <= 102 || value <= 25) {
        if (debugFlag) {
            std::ostringstream oss;
            oss << "Ignoring due to low S or V: S [" << saturation << "] V [" << value << "] at xy(" << x << "," << y << ")";
            Logger::info(oss.str());
        }
        return false;
    }

    // Judgment of color system
    bool result = false;
    if (colorType == "RED") {
        result = (hue >= 0 && hue <= 30) || (hue >= 331 && hue <= 360);
    }
    if (colorType == "ORANGE") {
        result = (hue >= 31 && hue <= 50);
    }
    if (colorType == "YELLOW") {
        result = (hue >= 51 && hue <= 70);
    }
    if (colorType == "GREEN") {
        result = (hue >= 71 && hue <= 160);
    }
    if (colorType == "BLUE") {
        result = (hue >= 161 && hue <= 262);
    }
    if (colorType == "PURPLE") {
        result = (hue >= 263 && hue <= 330);
    }

    if (debugFlag) {
        // Output debugging information
        std::ostringstream oss;
        oss << "bool [" << 
            result <<
            "] / colortype[" <<
            colorType <<
            "] : hue[" <<
            hue <<
            "] / xy(" <<
            x << "," << y <<
            ")";
        Logger::info(oss.str());
    }

    return result;
}
