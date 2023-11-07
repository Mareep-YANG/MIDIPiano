//
// Created by ly on 2023/10/27.
//
#include "../Logger.cpp"

void commandHelp() {
    Logger::info("---------------------------");
    Logger::info("help -> 打印帮助信息");
    Logger::info("select -> 选择MIDI输出设备");
    Logger::info("map -> 显示当前键盘映射");
    Logger::info("start -> 开始MIDI演奏");
    Logger::info("exit -> 退出程序");
    Logger::info("record -> 录制曲谱");
    Logger::info("---------------------------");
}
