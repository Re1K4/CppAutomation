#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class Logger {
public:
    static void initialize(const std::string& filename = "", bool consoleOutput = true);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

private:
    static void log(const std::string& level, const std::string& message);
    static std::string getCurrentTime();

    static std::ofstream logFile;
    static bool consoleOutputEnabled;

    Logger() = delete;
};