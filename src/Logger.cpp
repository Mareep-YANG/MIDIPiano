#include "iostream"
#include "sstream"
using namespace std;
enum logLevel {
        INFO ,WARN,SERIOUS
};




class Logger {
public:
    static void info(const string& s) {
        sendMessage(INFO,s);
    }
    static void warn(const string& s){
        sendMessage(WARN,s);
    }
    static void serious(const string& s){
        sendMessage(SERIOUS , s);
    }
private:
    static void sendMessage(logLevel l , const string& s){
        string logLevelStr;
        if (l == 0){
            logLevelStr = "INFO";
        }
        else if (l == 1){
            logLevelStr = "WARN";
        }
        else if(l == 2){
            logLevelStr = "SERIOUS";
        }
        cout << "["+getCurrentDate()+" "<<logLevelStr<<"] :"<<s<<endl;
    }
    static string getCurrentDate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        ostringstream ss;
        ss << (localTime->tm_hour ) << ":"
           << (localTime->tm_min ) << ":"
           << localTime->tm_sec;
        return ss.str();
    }
};