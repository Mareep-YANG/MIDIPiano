//
// Created by ly on 2023/11/7.
//
#include <map>
#include "string"
#include "../Entities/MusicEntity.cpp"
#include "chrono"
#include "thread"
#include "../Logger.cpp"
#include "windows.h"
//全局变量
extern std::map<std::string , MusicEntity> musicMap;
extern int selectedMidiDev; // 选择的MIDI输出设备
std::chrono::steady_clock::time_point startPlay;
//函数声明
void commandStart(int);// 开始演奏
void nodeKeyHandler(const std::string& ,bool);
void keyHandler(DWORD key, bool sign);
//主要逻辑
void commandMusicPlay(const std::string &musicName){
    if (musicMap.find(musicName) == musicMap.end()) {
        Logger::warn("曲谱不存在");
        return;
    }
    else{
        int nodeCount = 0;
        std::thread startRecord(commandStart, selectedMidiDev); // 开线程
        startPlay = std::chrono::steady_clock::now();
        while(true){
            std::chrono::steady_clock::time_point via = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(via - startPlay);
            if (duration.count() >= musicMap[musicName].notes[nodeCount].time){
                nodeKeyHandler(musicMap[musicName].notes[nodeCount].shortName,musicMap[musicName].notes[nodeCount].isDown);
                nodeCount++;
            }
            if (nodeCount == musicMap[musicName].notes.size()){
                Logger::info("演奏结束 , 您可以继续弹奏");
                startRecord.join();
                break;
            }
        }
    }

}