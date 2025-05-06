#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static void LogClassOnce(const std::string& className, const std::string& filePath);
};

#include <fstream>
#include <unordered_set>
#include <mutex>

void Logger::LogClassOnce(const std::string& className, const std::string& filePath)
{
#ifdef DEBUG_MODE
    static std::unordered_set<std::string> loggedClasses;
    static std::mutex mtx;

    std::lock_guard<std::mutex> lock(mtx);

    if (loggedClasses.find(className) == loggedClasses.end()) {
        std::ofstream file(filePath, std::ios::app); // 追記モード
        if (file.is_open()) {
            file << className << '\n';
            loggedClasses.insert(className);
        }
    }
#endif
}

#endif