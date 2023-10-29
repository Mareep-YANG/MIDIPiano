// -*- coding: utf-8 -*-

#include <iostream>
#include <windows.h>
#include "KeyManager.cpp"
#include "fstream"
#include "filesystem"
#include "Entities/NoteEntity.cpp"
// 函数声明
int commandSelect();

void commandHelp();

void commandStart(int);

string getCurrentDate();

void initLogFile();

void initNoteFile();

//全局变量
int selectedMidiDev = 0;
string logFileName = "./logs/" + getCurrentDate() + ".log";
KeyManager keyManager;
map<string , NoteEntity> noteMap;
//主函数
int main() {
    using namespace std;
    SetConsoleOutputCP(CP_UTF8);
    initLogFile();
    initNoteFile();
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
            selectedMidiDev = commandSelect();
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
            return 0;
        } else {
            Logger::warn("无效的指令 键入help以获取帮助");
        }
    }

}

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
void initNoteFile(){
    //创建音符文件夹
    if (!filesystem::exists("./notes")) {
        filesystem::create_directory("./notes");
    }

    //读取文件夹内所有音符文件
    int noteNum = 0;
    for (const auto & entry : filesystem::directory_iterator("./notes")){
        ifstream noteFile (entry.path());
        int noteNo;
        int velocity;
        int voiceNumber;
        string shortName;
        int key;
        noteFile >> noteNo >> velocity >> voiceNumber >> shortName >> key;
        if (noteFile.fail()){
            Logger::serious("音符文件格式错误 按任意键退出程序");
            system("pause >nul");
            exit(1);
        }

        noteMap.insert(pair<string,NoteEntity>(shortName, NoteEntity(noteNo,velocity,voiceNumber,shortName,key)));
        keyManager.addMapping(key, shortName);
        noteNum++;
    }
    Logger::info("NoteService初始化完成");
    Logger::info("共读取到"+to_string(noteNum)+"个音符文件");

}

