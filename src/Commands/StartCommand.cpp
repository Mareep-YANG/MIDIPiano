//
// Created by ly on 2023/10/27.
//
#include "iostream"
#include "windows.h"
#include "../KeyManager.cpp"
#include "map"
#include "../Entities/NoteEntity.cpp"
//全局变量
HMIDIOUT hMidiOut; // MIDI输出设备句柄
HHOOK hKeyboardHook; // 键盘钩子
BYTE nowChannel = 0; // 当前通道
extern KeyManager keyManager;
extern map<string , NoteEntity> noteMap;
bool keyState[256] = {false}; // 按键状态
//函数声明

void initMidiOut(int);


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    using namespace std;
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            const KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
            if (kbdStruct->vkCode == VK_ESCAPE) {
                Logger::info("ESC被按下,将退出演奏模式");
                PostQuitMessage(0);
            } else {
                string noteName = keyManager.getKeyNote(kbdStruct->vkCode);
                if (!noteName.empty()) {
                    if (keyState[kbdStruct->vkCode]) {
                        return CallNextHookEx(nullptr, nCode, wParam, lParam);
                    }
                    else{
                        keyState[kbdStruct->vkCode] = true;
                        DWORD noteOnMsg = 0x90 | nowChannel; // 0x90表示Note On消息

                        noteOnMsg |= (noteMap[noteName].noteNo & 0x7F) << 8;  // 音符号
                        noteOnMsg |= (noteMap[noteName].velocity & 0x7F) << 16; // 力度
                        midiOutShortMsg(hMidiOut, noteOnMsg);
                    }

                }

            }
        }
        if (wParam == WM_KEYUP){
            const KBDLLHOOKSTRUCT *kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT *>(lParam);
            string noteName = keyManager.getKeyNote(kbdStruct->vkCode);
            if (!noteName.empty()) {
                keyState[kbdStruct->vkCode] = false;
                DWORD noteOnMsg = 0x80 | nowChannel; // 0x90表示Note Off消息
                noteOnMsg |= (noteMap[noteName].noteNo & 0x7F) << 8;  // 音符号
                noteOnMsg |= (0 & 0x7F) << 16; // 力度
                midiOutShortMsg(hMidiOut, noteOnMsg);
            }
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
}


void commandStart(int selectMidiDev) {
    using namespace std; // 使用std名字空间
    initMidiOut(selectMidiDev);// 初始化Midi输出设备
    Logger::info("按ESC退出演奏模式");

    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(nullptr), 0); // 安装键盘钩子
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    cin.ignore();
    UnhookWindowsHookEx(hKeyboardHook);
    midiOutClose(hMidiOut);

}

// MIDI设备初始化函数
void initMidiOut(int selectMidiDev) {
    if(midiOutOpen(&hMidiOut, selectMidiDev, 0, 0, CALLBACK_NULL)==MMSYSERR_NOERROR){
        Logger::info("MIDI输出设备初始化成功");
    }
    else{
        Logger::warn("MIDI输出设备初始化失败");
    }

}
