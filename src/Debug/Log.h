#pragma once

#include <string>

struct Log {
    static void Info(const std::string& message);
    static void Error(const std::string& message);
    static void Warning(const std::string& message);
    static void Debug(const std::string& message);
    static void Fatal(const std::string& message);
}