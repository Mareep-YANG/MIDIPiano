//
// Created by ly on 2023/10/27.
//
#include "iostream"
#include "windows.h"
#include "../KeyManager.cpp"
#include "map"
#include "../Entities/NoteEntity.cpp"
#include "vector"
#include <fstream>
#include <chrono>

//全局变量
HMIDIOUT hMidiOut; // MIDI输出设备句柄
HHOOK hKeyboardHook; // 键盘钩子
BYTE nowChannel = 0; // 当前通道
BYTE nowVoice = 0; // 当前音色
BYTE nowVelocity = 80; // 当前力度
extern KeyManager keyManager;
extern std::map<std::string, NoteEntity> noteMap;
bool keyState[256] = {false}; // 按键状态
extern std::vector<std::string> midiSoundNames;
extern bool isPlaying; // 是否正在演奏
extern bool isRecording;// 是否正在录制
extern std::ofstream musicFile; // 曲谱文件对象
extern std::chrono::steady_clock::time_point startRecordTime; // 开始录制时间
//函数声明
void initMidiOut(int); // 初始化MIDI输出设备
void voiceChange(bool); // 音色改变
void velocityChange(bool);// 音量改变
void nodeKeyHandler(DWORD, bool); // 处理琴键按键
void keyHandler(DWORD, bool);// 处理按键
void nodeKeyHandler(const std::string &, bool);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        const KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
        if (wParam == WM_KEYDOWN) { // 处理键盘按键按下
            keyHandler(kbdStruct->vkCode, true);
        }
        if (wParam == WM_KEYUP) { // 处理键盘按键抬起
            keyHandler(kbdStruct->vkCode, false);
        }
    }
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}


void commandStart(int selectMidiDev) {
    initMidiOut(selectMidiDev);// 初始化Midi输出设备
    Logger::info("按ESC退出演奏模式 F1/F2切换音色");
    isPlaying = true;
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(nullptr), 0); // 安装键盘钩子
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    std::cin.ignore();
    std::cin.clear();
    UnhookWindowsHookEx(hKeyboardHook);// 卸载键盘钩子
    midiOutClose(hMidiOut); // 关闭MIDI输出设备
}

// MIDI设备初始化函数
void initMidiOut(int selectMidiDev) {
    if (midiOutOpen(&hMidiOut, selectMidiDev, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
        Logger::info("MIDI输出设备初始化成功");
    } else {
        Logger::warn("MIDI输出设备初始化失败");
    }
}

//改变音色函数
void voiceChange(bool sign) {
    if (sign) {
        Logger::info("右键被按下,音色+");
        nowVoice = (nowVoice + 1) % 128;
        Logger::info("当前音色:" + midiSoundNames[nowVoice]);
    } else {
        Logger::info("左键被按下,音色-");
        nowVoice = nowVoice == 0 ? 127 : nowVoice - 1;
        Logger::info("当前音色:" + midiSoundNames[nowVoice]);
    }
    DWORD msg = 0xC0 | nowChannel;
    msg |= (nowVoice & 0x7F) << 8;
    midiOutShortMsg(hMidiOut, msg);
}

void velocityChange(bool sign) {
    if (sign) {
        nowVelocity = nowVelocity == 127 ? 127 : nowVelocity + 1;
    } else {
        nowVelocity = nowVelocity == 0 ? 0 : nowVelocity - 1;
    }
    Logger::info("当前力度:" + std::to_string(nowVelocity));
}

void nodeKeyHandler(DWORD key, bool sign) {
    if (sign) {
        std::string noteName = keyManager.getKeyNote(static_cast<int>(key));
        if (!noteName.empty() && !keyState[key]) {
            keyState[key] = true;
            DWORD noteOnMsg = 0x90 | nowChannel; // 音符开启消息
            noteOnMsg |= (noteMap[noteName].noteNo & 0x7F) << 8;  // 音符号
            noteOnMsg |= (nowVelocity & 0x7F) << 16; // 力度
            midiOutShortMsg(hMidiOut, noteOnMsg);
            std::chrono::steady_clock::time_point via = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                    via - startRecordTime);
            if (isRecording) {
                musicFile << noteName << " " << duration.count() << " " << true << std::endl;
            }
            return;
        }
    } else {
        std::string noteName = keyManager.getKeyNote(static_cast<int>(key)); // 获取音符名
        if (!noteName.empty()) {
            keyState[key] = false;
            DWORD noteOnMsg = 0x80 | nowChannel; // 0x90表示Note Off消息
            noteOnMsg |= (noteMap[noteName].noteNo & 0x7F) << 8;  // 音符号
            noteOnMsg |= (0 & 0x7F) << 16; // 力度
            midiOutShortMsg(hMidiOut, noteOnMsg);
            std::chrono::steady_clock::time_point via = std::chrono::steady_clock::now();
            std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(
                    via - startRecordTime);
            if (isRecording) {
                musicFile << noteName << " " << duration.count() << " " << false << std::endl;
            }
        }
        return;
    }
}

void nodeKeyHandler(const std::string &noteName, bool sign) {
    nodeKeyHandler(keyManager.getNoteKey(noteName), sign);
}

void keyHandler(DWORD key, bool sign) {
    if (sign) {
        if (key == VK_ESCAPE) { // 按下ESC
            Logger::info("ESC被按下,将退出演奏模式");
            isPlaying = false;
            PostQuitMessage(0);
        } else if (key == VK_LEFT) { // 按下左键
            voiceChange(false);
        } else if (key == VK_RIGHT) { // 按下右键
            voiceChange(true);
        } else if (key == VK_UP) {
            velocityChange(true);
        } else if (key == VK_DOWN) {
            velocityChange(false);
        } else { // 处理其他按键
            nodeKeyHandler(key, true);
        }
    } else {
        if (!(key == VK_LEFT || key == VK_RIGHT || key == VK_UP || key == VK_DOWN)) {
            nodeKeyHandler(key, false);//处理琴键按键
        }
    }
}

