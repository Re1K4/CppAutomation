#include "TemplateMatching.h"

/* Retrieve image files from directory Path
TemplateMatching::TemplateMatching(const std::string& filename) {
    image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::exit(EXIT_FAILURE);
    }
}
*/

TemplateMatching::TemplateMatching(int resourceId) {
    image = loadResourceData(resourceId);
    hScreenDC = GetDC(nullptr);
    if (image.empty()) {
        throw std::runtime_error("Failed to load template image from resource.");
    }
}

TemplateMatching::~TemplateMatching() {
    if (hScreenDC) ReleaseDC(nullptr, hScreenDC);
}

// matching function
bool TemplateMatching::match(const cv::Rect& region, double fuzzy) {
    cv::Mat screenshot = captureScreen(region);
    cv::Mat result;
    cv::matchTemplate(screenshot, image, result, cv::TM_CCOEFF_NORMED);

    double maxVal;
    cv::Point maxLoc;
    cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);

    if (maxVal < fuzzy) {
        return false;
    } else {
        lastMatchResult = cv::Rect(maxLoc.x, maxLoc.y, image.cols, image.rows);
        return true;
    }
}

// binary matching function
bool TemplateMatching::matchBinary(const cv::Rect& region, double fuzzy) {
    cv::Mat grayImage, binaryImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cv::threshold(grayImage, binaryImage, 127, 255, cv::THRESH_BINARY);

    cv::Mat screenshot = captureScreen(region);
    cv::Mat grayScreenshot, binaryScreenshot;
    cv::cvtColor(screenshot, grayScreenshot, cv::COLOR_BGR2GRAY);
    cv::threshold(grayScreenshot, binaryScreenshot, 127, 255, cv::THRESH_BINARY);

    cv::Mat result;
    cv::matchTemplate(binaryScreenshot, binaryImage, result, cv::TM_CCOEFF_NORMED);

    double maxVal;
    cv::Point maxLoc;
    cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);

    if (maxVal < fuzzy) {
        return false;
    } else {
        lastMatchResult = cv::Rect(maxLoc.x, maxLoc.y, image.cols, image.rows);
        return true;
    }
}

cv::Mat TemplateMatching::captureScreen(const cv::Rect& region) {
    // Create memory DC
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    // Get the width and height of the capture area
    int width = region.width;
    int height = region.height;

    // Create bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

    // Select bitmap for memory DC
    SelectObject(hMemoryDC, hBitmap);

    // Copy specified area from screen to memory DC
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, region.x, region.y, SRCCOPY);

    // Set bitmap information
    BITMAPINFOHEADER bi = {};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    // BGRA buffer
    int imageSize = width * height * 4;
    std::vector<uchar> buffer(imageSize);
    GetDIBits(hMemoryDC, hBitmap, 0, height, buffer.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // BGRA Å® BGR
    cv::Mat tmp(height, width, CV_8UC4, buffer.data());
    cv::Mat screenCapture;
    cv::cvtColor(tmp, screenCapture, cv::COLOR_BGRA2BGR);

    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);

    return screenCapture;
}

cv::Mat TemplateMatching::loadResourceData(int resourceId) {
    // Get Resources
    HRSRC hResource = FindResource(nullptr, MAKEINTRESOURCE(resourceId), L"PNG");
    if (!hResource) {
        throw std::runtime_error("Failed to find PNG resource.");
    }

    // Load resource data into memory
    HGLOBAL hMemory = LoadResource(nullptr, hResource);
    if (!hMemory) {
        throw std::runtime_error("Failed to load PNG resource.");
    }

    // Get data pointer
    const void* resourceData = LockResource(hMemory);
    DWORD resourceSize = SizeofResource(nullptr, hResource);
    if (!resourceData || resourceSize == 0) {
        throw std::runtime_error("Failed to access PNG resource.");
    }

    // Decode PNG data with OpenCV
    std::vector<uchar> buffer(static_cast<const uchar*>(resourceData),
        static_cast<const uchar*>(resourceData) + resourceSize);
    cv::Mat image = cv::imdecode(buffer, cv::IMREAD_COLOR);
    if (image.empty()) {
        throw std::runtime_error("Failed to decode PNG resource.");
    }

    return image;
}