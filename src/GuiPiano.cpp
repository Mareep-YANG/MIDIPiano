// -*- coding: utf-8 -*-
// Created by ly on 2023/11/1.
//
#include <graphics.h>
#include <vector>
#include "thread"
#include "./KeyManager.cpp"

//函数声明
void commandStart(int);// 开始演奏
void drawPianoKeys();

// 全局变量
extern KeyManager keyManager;
extern int selectedMidiDev;
std::thread playThread;
extern BYTE nowVoice;
extern std::vector<std::string> midiSoundNamesEng;
char keyOne[]{'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '/'};
int codeOne[]{90, 88, 67, 86, 66, 78, 77, 188, 190, 191};
char keyTwo[]{'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '"'};
int codeTwo[]{65, 83, 68, 70, 71, 72, 74, 75, 76, 186, 222};
char keyThree[]{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', '\\'};
int codeThree[]{81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 219, 220};
extern bool keyState[256];
extern BYTE nowVelocity;

void initGui() {
    SetConsoleOutputCP(65001);
    bool isStart = false;
    initgraph(1000, 600);  // 初始化绘图环境
    setfillcolor(RGB(0, 168, 225));
    solidrectangle(0, 0, 1000, 50);
    settextcolor(RGB(255, 102, 0));
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
    outtextxy(500 - textwidth("Key Board MIDIPiano") / 2, 10, _T("Key Board MIDIPiano"));
    settextcolor(RGB(153, 204, 0));
    settextstyle(20, 0, _T("Tahoma"), 0, 0, 500, false, false, false);
    outtextxy(500 + textwidth("Key Board MIDIPiano"), 15, _T("Any key to continue"));
    IMAGE img;
    loadimage(&img, _T("./resource/background.png"));
    putimage(0, 50, &img);
    while (true) {
        ExMessage msg{};
        msg = getmessage(EX_KEY);
        if (isStart) {
            BeginBatchDraw();
            setfillcolor(RGB(0, 168, 225));
            solidrectangle(0, 0, 1000, 50);
            settextcolor(RGB(255, 102, 0));
            setbkmode(TRANSPARENT);
            settextstyle(30, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
            outtextxy(500 - textwidth("Key Board MIDIPiano") / 2, 10, _T("Key Board MIDIPiano"));
            setfillcolor(RGB(128, 0, 128));
            solidrectangle(0, 50, 1000, 100);
            settextcolor(RGB(255, 255, 255));
            setbkmode(TRANSPARENT);
            outtextxy(10, 60, _T("Voice:"));
            outtextxy(10 + textwidth("Voice:"), 60, midiSoundNamesEng[nowVoice].c_str());
            outtextxy(10 + textwidth("Voice:") + textwidth(midiSoundNamesEng[nowVoice].c_str()) + 20, 60,
                      _T("Velocity:"));
            outtextxy(
                    10 + textwidth("Voice:") + textwidth(midiSoundNamesEng[nowVoice].c_str()) + textwidth("Velocity:") +
                    20,
                    60, to_string(nowVelocity).c_str());
            loadimage(&img, _T("./resource/op.png"));
            putimage(0, 100, &img);
            drawPianoKeys();
            EndBatchDraw();
        }
        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
            Logger::info("正在退出程序...");
            closegraph();
            exit(0);
        }
        if (msg.message == WM_KEYDOWN && !isStart) {
            isStart = true;
            cleardevice();
            playThread = std::thread(commandStart, selectedMidiDev);
            continue;
        }
    }
    closegraph();

}

void drawPianoKeys() {
    int keyWidth = 56; // 每个琴键的宽度
    int keyHeight = 130; // 每个琴键的高度
    int numKeys = 18; // 总琴键数量
    // 第一行
    for (int i = 4; i < numKeys - 4; i++) {
        if (keyState[codeOne[i - 4]]) {
            setfillcolor(RGB(128, 128, 128));
        } else {
            setfillcolor(WHITE);
        }
        solidrectangle(i * keyWidth, 470, (i + 1) * keyWidth, 470 + keyHeight);
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
        outtextxy(i * keyWidth + 20, 470 + keyHeight - 30, keyOne[i - 4]);
        outtextxy(i * keyWidth + 20, 470 + keyHeight - 80, keyManager.getKeyNote(codeOne[i - 4]).c_str());
        setlinecolor(BLACK);
        line(i * keyWidth, 470, i * keyWidth, 470 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224, 470 - 5, 784, 470);
    //  第二行 11键
    setfillcolor(WHITE);
    for (int i = 3; i < numKeys - 4; i++) {
        if (keyState[codeTwo[i - 3]]) {
            setfillcolor(RGB(128, 128, 128));
        } else {
            setfillcolor(WHITE);
        }
        solidrectangle(i * keyWidth + 28, 335, (i + 1) * keyWidth + 28, 335 + keyHeight);
        outtextxy(28 + i * keyWidth + 20, 335 + keyHeight - 30, keyTwo[i - 3]);
        outtextxy(28 + i * keyWidth + 20, 335 + keyHeight - 80, keyManager.getKeyNote(codeTwo[i - 3]).c_str());
        line(i * keyWidth + 28, 335, i * keyWidth + 28, 335 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224 - 28, 335 - 5, 784 + 28, 335);
    // 第三行 13键
    setfillcolor(WHITE);
    for (int i = 3; i < numKeys - 2; i++) {
        if (keyState[codeThree[i - 3]]) {
            setfillcolor(RGB(128, 128, 128));
        } else {
            setfillcolor(WHITE);
        }
        solidrectangle(i * keyWidth + 28 - 56, 200, (i + 1) * keyWidth + 28 - 56, 200 + keyHeight);
        outtextxy(i * keyWidth + 20 + 28 - 56, 200 + keyHeight - 30, keyThree[i - 3]);
        outtextxy(i * keyWidth + 20 + 28 - 56, 200 + keyHeight - 80, keyManager.getKeyNote(codeThree[i - 3]).c_str());
        line(i * keyWidth + 28 - 56, 200, i * keyWidth + 28 - 56, 200 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224 - 28 - 56, 200 - 5, 784 + 28 + 56, 200);

}
