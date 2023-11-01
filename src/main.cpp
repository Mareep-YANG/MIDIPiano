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

string getCurrentDate();// 获取当前时间

void initLogFile();// 初始化日志文件

void initNoteFile();// 初始化音符文件

void initCfgFile();// 初始化配置文件

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void initWindows(HINSTANCE, int);

void initConsole();// 初始化控制台
//全局变量
int selectedMidiDev = 0; // 选择的MIDI输出设备
string logFileName = "./logs/" + getCurrentDate() + ".log"; // 日志文件名
KeyManager keyManager;// 键盘映射管理器
map<string, NoteEntity> noteMap;// 音符表
bool isCommandLineMode = true;// 是否为命令行模式
//主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    using namespace std;
    initCfgFile();// 初始化配置文件
    if (isCommandLineMode) {
        initConsole(); // 初始化控制台
    } else {
        initWindows(hInstance, nCmdShow);// 初始化窗口
    }
    initLogFile(); // 初始化日志文件
    initNoteFile();// 初始化音符文件


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
        string s;
        cout << "请输入指令>";
        cin >> s;
        //保存用户输入到日志文件
        ofstream logFile(logFileName, ios::app);
        logFile << "Console:" << s << endl;
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
    if (!filesystem::exists("./logs")) {
        filesystem::create_directory("./logs");
    }
    //创建日志文件
    for (int i = 1; filesystem::exists(logFileName); i++) {
        logFileName = "./logs/" + getCurrentDate() + "-" + to_string(i) + ".log";
    }
    ofstream logFile(logFileName, ios::app);
    logFile.close();
    Logger::info("LoggerService初始化完成");
}

// 初始化音符文件
void initNoteFile() {
    //创建音符文件夹
    if (!filesystem::exists("./notes")) {
        filesystem::create_directory("./notes");
    }

    //读取文件夹内所有音符文件
    int noteNum = 0;
    for (const auto &entry: filesystem::directory_iterator("./notes")) {
        ifstream noteFile(entry.path());
        int noteNo;
        int velocity;
        int voiceNumber;
        string shortName;
        int key;
        noteFile >> noteNo >> velocity >> voiceNumber >> shortName >> key;
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
        noteMap.insert(pair<string, NoteEntity>(shortName, NoteEntity(noteNo, velocity, voiceNumber, shortName, key)));
        keyManager.addMapping(key, shortName);
        noteNum++;
    }
    Logger::info("NoteService初始化完成");
    Logger::info("共读取到" + to_string(noteNum) + "个音符文件");

}

// 初始化配置文件
void initCfgFile() {
    //创建配置文件
    if (!filesystem::exists("./config.cfg")) {
        ofstream cfgFile("./config.cfg", ios::app);
        cfgFile << "selectedMidiDev=0" << endl;
        cfgFile << "isCommandLineMode=true" << endl;
        cfgFile.close();
    } else {
        // 读取配置文件
        ifstream cfgFile("./config.cfg");
        string line;
        while (getline(cfgFile, line)) {
            if (line.find("selectedMidiDev=") != string::npos) {
                selectedMidiDev = stoi(line.substr(line.find('=') + 1));
            } else if (line.find("isCommandLineMode=") != string::npos) {
                isCommandLineMode = line.find("true") != string::npos;
            }
        }
        cfgFile.close();
    }
}

//初始化窗口
void initWindows(HINSTANCE hinstance, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hinstance;
    wc.lpszClassName = "MidiPiano";
    RegisterClass(&wc);
    HWND hwnd = CreateWindowExW(
            0,                              // Optional window styles.
            L"MidiPiano",                     // Window class
            L"MIDI电子琴-科中软件考核-雷洋",    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            nullptr,       // Parent window
            nullptr,       // Menu
            hinstance,  // Instance handle
            nullptr        // Additional application data
    );

    if (hwnd == nullptr) {
        Logger::serious("窗口初始化失败 按任意键退出程序");
        exit(1);
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

