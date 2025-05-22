#include "Logger.h"

std::ofstream Logger::logFile;
bool Logger::consoleOutputEnabled = true;

void Logger::initialize(const std::string& filename, bool consoleOutput) {
    consoleOutputEnabled = consoleOutput;

    if (!filename.empty()) {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open()) {
            std::cerr << "[Logger Error] Failed to open log file: " << filename << std::endl;
        }
    }
}

void Logger::info(const std::string& message) {
    log("INFO", message);
}

void Logger::warning(const std::string& message) {
    log("WARNING", message);
}

void Logger::error(const std::string& message) {
    log("ERROR", message);
}

void Logger::log(const std::string& level, const std::string& message) {
    std::string output = getCurrentTime() + " - " + level + ":" + message;

    if (logFile.is_open()) {
        logFile << output << std::endl;
    }

    if (consoleOutputEnabled) {
        std::cout << output << std::endl;
    }
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_s(&localTime, &time);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}