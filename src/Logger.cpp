/*
 * 该类用于记录日志
 * 该类为静态类，不可实例化
 * 该类提供三种日志级别的输出方法：info, warn, serious
 */
#include "iostream"
#include "sstream"
#include "iomanip"
#include "fstream"

using namespace std;

extern string logFileName;
extern bool isCommandLineMode;
class Logger {
public:
    static void info(const string &s) {
        sendMessage(INFO, s);
    }

    static void warn(const string &s) {
        sendMessage(WARN, s);
    }

    static void serious(const string &s) {
        sendMessage(SERIOUS, s);
    }

private:
    enum logLevel {
        INFO, WARN, SERIOUS
    };
    static void sendMessage(logLevel l, const string &s) {
        string logLevelStr;
        ofstream logFile(logFileName, ios::app);
        if (l == 0) {
            logLevelStr = "INFO";
        } else if (l == 1) {
            logLevelStr = "WARN";
        } else if (l == 2) {
            logLevelStr = "SERIOUS";
        }
        if (isCommandLineMode){
            cout << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << endl;
        }
        logFile << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << endl;
    }

    static string getCurrentDate() {
        time_t now = time(nullptr);
        const tm *localTime = localtime(&now);
        ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << (localTime->tm_hour) << ":"
           << std::setw(2) << std::setfill('0') << (localTime->tm_min) << ":"
           << std::setw(2) << std::setfill('0') << localTime->tm_sec;
        return ss.str();
    }
};