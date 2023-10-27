//
// Created by ly on 2023/10/27.
//
#include "iostream"
#include "windows.h"
#include "../Logger.cpp"
//全局变量
HMIDIOUT hMidiOut; // MIDI输出设备句柄
HHOOK hKeyboardHook; // 键盘钩子
bool escState = true;// 退出状态
Logger logger =  Logger();
//函数声明
void handleKeyboardEvents(HMIDIOUT  , bool state);
void initMidiOut(int);


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    using namespace std;
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
            if (kbdStruct->vkCode == VK_ESCAPE) {
                escState = false;
                logger.info("123");
                cout << "<MIDI电子琴>:ESC被按下,将退出演奏模式" << endl;
                PostQuitMessage(0);
            }
            else{
                cout << kbdStruct->vkCode << endl;
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}



void CommandStart(int selectMidiDev) {
    using namespace std; // 使用std名字空间
    initMidiOut(selectMidiDev);// 初始化Midi输出设备
    cout << "<MIDI电子琴>:按ESC退出演奏模式" << endl; // 输出提示语
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0); // 安装键盘钩子
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hKeyboardHook);
    midiOutClose(hMidiOut);

}
// MIDI设备初始化函数
void initMidiOut(int selectMidiDev){
    std::cout << "<MIDI电子琴>:MIDI输出设备已经启动 可以开始演奏" << std::endl;
    midiOutOpen(&hMidiOut, selectMidiDev, 0, 0, CALLBACK_NULL);
}
