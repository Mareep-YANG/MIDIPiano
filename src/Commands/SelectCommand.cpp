//
// Created by ly on 2023/10/25.
//
#include "iostream"
#include "windows.h"
#include "mmeapi.h"
#include "../Logger.cpp"
// 选择音频设备
int commandSelect() {
    int selectedMidiDev = 0; // 选择的MIDI输出设备
    int numDev = static_cast<int>(midiOutGetNumDevs()); // 获取输出设备数量
    Logger::info("共有" + std::to_string(numDev) + "个MIDI输出设备");
    Logger::info("---------------------------");
    for (int i = 0; i < numDev; i++) {
        auto *devResult = new MIDIOUTCAPS; // 输出设备信息指针
        MMRESULT resultState = midiOutGetDevCaps(i, devResult, sizeof(MIDIOUTCAPS)); // 获取状态
        if (resultState == MMSYSERR_NOERROR) { // 若获取成功
            // 打印设备信息
            Logger::info("第" + std::to_string(i + 1) + "个输出设备信息");
            Logger::info("制造商ID:" + std::to_string(devResult->wMid) + " 产品ID:" + std::to_string(devResult->wPid));
            std::ostringstream ss;
            ss << "设备名称:" << devResult->szPname;
            Logger::info(ss.str());
            Logger::info("---------------------------");
        } else {// 获取失败
            Logger::warn("第" + std::to_string(i + 1) + "个输出设备信息获取失败");
        }
        delete devResult;
    }
    // 开始选择
    Logger::info("请输入使用的MIDI输出设备的编号:");
    std::cin >> selectedMidiDev;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore();
        Logger::warn("请不要输入非法字符");
        return 0;
    }
    selectedMidiDev--;
    if (selectedMidiDev < numDev) {
        Logger::info("选择成功!可以开始演奏");
    } else {
        Logger::warn("无该输出设备!");
        return 0;
    }
    return selectedMidiDev;
}


