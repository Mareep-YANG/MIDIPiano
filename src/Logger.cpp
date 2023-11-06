/*
 * 该类用于记录日志
 * 该类为静态类，不可实例化
 * 该类提供三种日志级别的输出方法：info, warn, serious
 */
#include "iostream"
#include "sstream"
#include "iomanip"
#include "fstream"


extern std::string logFileName;
extern bool isCommandLineMode;

class Logger {
public:
    static void info(const std::string &s) {
        sendMessage(INFO, s);
    }

    static void warn(const std::string &s) {
        sendMessage(WARN, s);
    }

    static void serious(const std::string &s) {
        sendMessage(SERIOUS, s);
    }

private:
    enum logLevel {
        INFO, WARN, SERIOUS
    };

    static void sendMessage(logLevel l, const std::string &s) {
        std::string logLevelStr;
        std::ofstream logFile(logFileName, std::ios::app);
        if (l == 0) {
            logLevelStr = "INFO";
        } else if (l == 1) {
            logLevelStr = "WARN";
        } else if (l == 2) {
            logLevelStr = "SERIOUS";
        }
        if (isCommandLineMode) {
            std::cout << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << std::endl;
        }
        logFile << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << std::endl;
        logFile.close();
    }

    static std::string getCurrentDate() {
        time_t now = time(nullptr);
        const tm *localTime = localtime(&now);
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << (localTime->tm_hour) << ":"
           << std::setw(2) << std::setfill('0') << (localTime->tm_min) << ":"
           << std::setw(2) << std::setfill('0') << localTime->tm_sec;
        return ss.str();
    }
};