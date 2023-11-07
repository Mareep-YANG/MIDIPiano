//
// Created by ly on 2023/11/7.
//
/*
 * 思路 : 主线程执行RecordCommand , 进行tick计时 , 开一个线程执行startCommand , extern主线程的tick数来输入到文件中
 *
 *
 *
 * */
#include "string"
#include <fstream>
#include<thread>
#include <synchapi.h>
#include "../Logger.cpp"
#include "chrono"
// 函数声明
void commandStart(int);// 开始演奏
//全局变量
extern int selectedMidiDev; // 选择的MIDI输出设备
std::ofstream musicFile; // 曲谱文件对象
bool isRecording = false; // 是否正在录制模式 , 该变量由主线程控制 , 在start线程使用
extern bool isPlaying; // 是否正在演奏 , 该变量由start线程控制 , 在主线程使用
std::chrono::steady_clock::time_point startRecordTime; // 开始时间
void commandRecord(const std::string &musicName) {
    std::thread startRecord(commandStart, selectedMidiDev); // 开线程
    isRecording = true;
    musicFile = std::ofstream("./musics/" + musicName + ".txt", std::ios::app);//  创建曲谱文件
    musicFile << musicName << std::endl;// 写入曲谱名
    Logger::info("正在录制曲谱...可以开始弹奏");
    startRecordTime = std::chrono::steady_clock::now();

    startRecord.join();
    isRecording = false;
    musicFile.close();
}
