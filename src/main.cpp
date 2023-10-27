// -*- coding: utf-8 -*-

#include <iostream>
#include <windows.h>
#include "../include/Note.h"
#include "Logger.cpp"
// 函数声明
int CommandSelect();
void CommandHelp();
void CommandStart(int);
//全局变量
int selectedMidiDev = 0 ;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Logger::info("欢迎使用MIDI电子琴,键入help以获取帮助");
    while(true){
        using namespace std;
        //输入操作符
        string s;

        cout <<"请输入指令>";
        cin >> s;
        // 选择使用的MIDI输出设备
        if(s == "select"){
            selectedMidiDev = CommandSelect();
        }
        // 帮助
        else if(s == "help"){
            CommandHelp();
        }
        // 开始演奏
        else if(s == "start"){
            CommandStart(selectedMidiDev);
        }
        // 退出程序
        else if (s == "exit"){
            return 0;
        }
    }

}

