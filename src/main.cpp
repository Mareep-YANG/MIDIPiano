// -*- coding: utf-8 -*-

#include <iostream>
#include <windows.h>
#include "KeyManager.cpp"
#include "fstream"
#include "filesystem"
#include "Entities/NoteEntity.cpp"

// 函数声明
int commandSelect(); // 选择MIDI输出设备

void commandHelp(); // 显示帮助

void commandStart(int);// 开始演奏

std::string getCurrentDate();// 获取当前时间

void initLogFile();// 初始化日志文件

void initNoteFile();// 初始化音符文件

void initCfgFile();// 初始化配置文件

void initConsole();// 初始化控制台

void initGui();// 初始化GUI
//全局变量
int selectedMidiDev = 0; // 选择的MIDI输出设备
std::string logFileName = "./logs/" + getCurrentDate() + ".log"; // 日志文件名
KeyManager keyManager;// 键盘映射管理器
std::map<std::string, NoteEntity> noteMap;// 音符表
bool isCommandLineMode = true;// 是否为命令行模式

//主函数
int main() {
    initCfgFile();// 初始化配置文件
    if (isCommandLineMode) {
        initConsole(); // 初始化控制台
    } else {
        initLogFile(); // 初始化日志文件
        initNoteFile();// 初始化音符文件
        initGui();// 初始化GUI
    }
}

//初始化控制台
void initConsole() {
    AllocConsole();// 打开一个控制台界面
    // 重定向标准输入输出到控制台
    if (!(freopen("CON", "r", stdin) && freopen("CON", "w", stdout))) {
        exit(1);
    }
    SetConsoleOutputCP(CP_UTF8);// 设置控制台输出编码为UTF-8
    initLogFile(); // 初始化日志文件
    initNoteFile();// 初始化音符文件
    Logger::info("欢迎使用MIDI电子琴,键入help以获取帮助");
    while (true) {
        //输入操作符
        std::string s;
        std::cout << "请输入指令>";
        std::cin >> s;
        //保存用户输入到日志文件
        std::ofstream logFile(logFileName, std::ios::app);
        logFile << "Console:" << s << std::endl;
        logFile.close();
        // 选择使用的MIDI输出设备
        if (s == "select") {
            selectedMidiDev = commandSelect();
        }
            // 显示当前键盘映射
        else if (s == "map") {
            keyManager.commandMap();
        }
            // 帮助
        else if (s == "help") {
            commandHelp();
        }
            // 开始演奏
        else if (s == "start") {
            commandStart(selectedMidiDev);
        }
            // 退出程序
        else if (s == "exit") {
            Logger::info("正在退出程序...按任意键继续");
            system("pause >nul");
            FreeConsole();
            exit(0);

        } else {
            Logger::warn("无效的指令 键入help以获取帮助");
        }
    }
}

// 获取当前时间
std::string getCurrentDate() {
    time_t now = time(nullptr);
    const tm *localTime = localtime(&now);
    std::stringstream ss;
    ss << (localTime->tm_year + 1900) << '-'
       << (localTime->tm_mon + 1) << '-'
       << localTime->tm_mday;

    // 返回日期字符串
    return ss.str();
}

// 初始化日志文件
void initLogFile() {
    //创建日志文件夹
    if (!std::filesystem::exists("./logs")) {
        std::filesystem::create_directory("./logs");
    }
    //创建日志文件
    for (int i = 1; std::filesystem::exists(logFileName); i++) {
        logFileName = "./logs/" + getCurrentDate() + "-" + std::to_string(i) + ".log";
    }
    std::ofstream logFile(logFileName, std::ios::app);
    logFile.close();
    Logger::info("LoggerService初始化完成");
}

// 初始化音符文件
void initNoteFile() {
    //创建音符文件夹
    if (!std::filesystem::exists("./notes")) {
        std::filesystem::create_directory("./notes");
    }

    //读取文件夹内所有音符文件
    int noteNum = 0;
    for (const auto &entry: std::filesystem::directory_iterator("./notes")) {
        std::ifstream noteFile(entry.path());
        int noteNo;
        std::string shortName;
        int key;
        noteFile >> noteNo >> shortName >> key;
        if (noteFile.fail()) {
            Logger::serious("音符文件格式错误 按任意键退出程序");
            system("pause >nul");
            exit(1);
        }
        if (noteMap.find(shortName) != noteMap.end()) {
            Logger::serious("音符文件" + shortName + "重复 按任意键退出程序");
            system("pause >nul");
            exit(1);
        }
        noteMap.insert(std::pair<std::string, NoteEntity>(shortName, NoteEntity(noteNo, shortName, key)));
        keyManager.addMapping(key, shortName);
        noteNum++;
    }
    Logger::info("NoteService初始化完成");
    Logger::info("共读取到" + std::to_string(noteNum) + "个音符文件");

}

// 初始化配置文件
void initCfgFile() {
    //创建配置文件
    if (!std::filesystem::exists("./config.cfg")) {
        std::ofstream cfgFile("./config.cfg", std::ios::app);
        cfgFile << "selectedMidiDev=0" << std::endl;
        cfgFile << "isCommandLineMode=true" << std::endl;
        cfgFile.close();
    } else {
        // 读取配置文件
        std::ifstream cfgFile("./config.cfg");
        std::string line;
        while (getline(cfgFile, line)) {
            if (line.find("selectedMidiDev=") != std::string::npos) {
                selectedMidiDev = stoi(line.substr(line.find('=') + 1)) - 1;
            } else if (line.find("isCommandLineMode=") != std::string::npos) {
                isCommandLineMode = line.find("true") != std::string::npos;
            }
        }
        cfgFile.close();
    }
}




