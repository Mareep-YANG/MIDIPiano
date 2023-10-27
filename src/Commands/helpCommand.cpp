//
// Created by ly on 2023/10/27.
//
#include "iostream"
#include "../Logger.cpp"
void CommandHelp(){
    using namespace std;
    Logger::info("---------------------------");
    Logger::info("help -> 打印帮助信息");
    Logger::info("select -> 选择MIDI输出设备");
    Logger::info("start -> 开始MIDI演奏");
    Logger::info("exit -> 退出程序");
    Logger::info("---------------------------");
}
