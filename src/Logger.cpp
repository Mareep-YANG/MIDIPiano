#include "iostream"
#include "sstream"
#include "iomanip"
#include "fstream"

using namespace std;
enum logLevel {
    INFO, WARN, SERIOUS
};
extern string logFileName;

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
        cout << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << endl;
        logFile << "[" + getCurrentDate() + " " << logLevelStr << "] :" << s << endl;
    }

    static string getCurrentDate() {
        time_t now = time(0);
        tm *localTime = localtime(&now);
        ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << (localTime->tm_hour) << ":"
           << std::setw(2) << std::setfill('0') << (localTime->tm_min) << ":"
           << std::setw(2) << std::setfill('0') << localTime->tm_sec;
        return ss.str();
    }
};