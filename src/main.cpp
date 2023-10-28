// -*- coding: utf-8 -*-

#include <iostream>
#include <windows.h>
#include "../include/Note.h"
#include "Logger.cpp"
#include "fstream"
#include "filesystem"

// 函数声明
int CommandSelect();

void CommandHelp();

void CommandStart(int);

string getCurrentDate();

void initLogFile();

//全局变量
int selectedMidiDev = 0;
string logFileName = "./log/" + getCurrentDate() + ".log";

//主函数
int main() {
    using namespace std;
    SetConsoleOutputCP(CP_UTF8);
    initLogFile();

    Logger::info("欢迎使用MIDI电子琴,键入help以获取帮助");
    while (true) {
        //输入操作符
        string s;

        cout << "请输入指令>";
        cin >> s;
        ofstream logFile(logFileName, ios::app);
        logFile << "Console:" << s << endl;
        logFile.close();
        // 选择使用的MIDI输出设备
        if (s == "select") {
            selectedMidiDev = CommandSelect();
        }
            // 帮助
        else if (s == "help") {
            CommandHelp();
        }
            // 开始演奏
        else if (s == "start") {
            CommandStart(selectedMidiDev);
        }
            // 退出程序
        else if (s == "exit") {
            Logger::info("正在退出程序...");
            return 0;
        } else {
            Logger::warn("无效的指令 键入help以获取帮助");
        }
    }

}

std::string getCurrentDate() {
    time_t now = time(0);
    const tm *localTime = localtime(&now);
    std::stringstream ss;
    ss << (localTime->tm_year + 1900) << '-'
       << (localTime->tm_mon + 1) << '-'
       << localTime->tm_mday;

    // 返回日期字符串
    return ss.str();
}

void initLogFile() {
    //创建日志文件夹
    if (!filesystem::exists("./log")) {
        filesystem::create_directory("./log");
    }
    //创建日志文件
    for (int i = 1; filesystem::exists(logFileName); i++) {
        logFileName = "./log/" + getCurrentDate() + "-" + to_string(i) + ".log";
    }
    ofstream logFile(logFileName, ios::app);
    logFile.close();
}

