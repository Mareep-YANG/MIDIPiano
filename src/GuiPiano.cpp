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

void commandMusicPlay(const std::string &musicName);

void commandRecord(const std::string &musicName);

void keyAndMouseHandler();

void drawPianoGUI();

void voiceChange(bool); // 音色改变
void velocityChange(bool);// 音量改变

// 全局变量
extern KeyManager keyManager;
extern int selectedMidiDev;
std::thread playThread;
extern BYTE nowVoice;
extern std::vector<std::string> midiSoundNamesEng;
// 键盘字符和键码对应表(按位置)
char keyOne[]{'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '/'};
int codeOne[]{90, 88, 67, 86, 66, 78, 77, 188, 190, 191};
char keyTwo[]{'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '"'};
int codeTwo[]{65, 83, 68, 70, 71, 72, 74, 75, 76, 186, 222};
char keyThree[]{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\\'};
int codeThree[]{81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 219, 220};
extern bool keyState[256];
extern BYTE nowVelocity;
extern bool isRecording;
extern std::string playingMusicName;
bool isStart = false;

[[noreturn]] void initGui() {
    initgraph(1000, 600);  // 初始化绘图环境
    // 绘制标题栏
    setfillcolor(RGB(0, 168, 225));
    solidrectangle(0, 0, 1000, 50);
    settextcolor(RGB(255, 102, 0));
    setbkmode(TRANSPARENT);
    settextstyle(30, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
    outtextxy(500 - textwidth("Key Board MIDIPiano") / 2, 10, _T("Key Board MIDIPiano"));
    settextcolor(RGB(153, 204, 0));
    settextstyle(20, 0, _T("Tahoma"), 0, 0, 500, false, false, false);
    outtextxy(500 + textwidth("Key Board MIDIPiano"), 15, _T("Any key to continue"));
    // 绘制背景图
    IMAGE img;
    loadimage(&img, _T("./resource/background.png"));
    putimage(0, 50, &img);
    keyAndMouseHandler();
}

void keyAndMouseHandler() {
    while (true) {
        ExMessage msg = getmessage();
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x <= 390 && msg.x >= 275 && msg.y >= 105 && msg.y <= 145) {
                velocityChange(true);
            }
            if (msg.x >= 420 && msg.y >= 105 && msg.x <= 540 && msg.y <= 145) {
                velocityChange(false);
            }
            if (msg.x >= 570 && msg.y >= 105 && msg.x <=690 && msg.y <= 145){
                voiceChange(true);
            }
            if(msg.x >= 720 && msg.y >= 105 && msg.x <= 840 && msg.y <= 145){
                voiceChange(false);
            }
            if (msg.x <= 120 && msg.x >= 20 && msg.y <= 145 && msg.y >= 105) {
                char musicName[256];
                InputBox(musicName, 256, "Please input music name");
                std::thread(commandRecord, musicName).detach();
            }
            if (msg.x <= 240 && msg.x >= 140 && msg.y <= 145 && msg.y >= 105) {
                char musicName[256];
                InputBox(musicName, 256, "Please input music name");
                std::thread(commandMusicPlay, musicName).detach();
            }

        }
        if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE && !isRecording) {
            Logger::info("正在退出程序...");
            closegraph();
            playThread.join();
            exit(0);
        }
        if (msg.message == WM_KEYDOWN && !isStart) {
            isStart = true;
            cleardevice();
            std::thread guiThread(drawPianoGUI);
            guiThread.detach();
            playThread = std::thread(commandStart, selectedMidiDev);
        }
    }
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
        outtextxy(i * keyWidth + 20, 470 + keyHeight - 80, keyManager.getKeyNote(codeOne[i - 4], false).c_str());
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
        outtextxy(28 + i * keyWidth + 20, 335 + keyHeight - 80, keyManager.getKeyNote(codeTwo[i - 3], false).c_str());
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
        outtextxy(i * keyWidth + 20 + 28 - 56, 200 + keyHeight - 80,
                  keyManager.getKeyNote(codeThree[i - 3], false).c_str());
        line(i * keyWidth + 28 - 56, 200, i * keyWidth + 28 - 56, 200 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224 - 28 - 56, 200 - 5, 784 + 28 + 56, 200);

}

void drawPianoGUI() {
    while (isStart) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        BeginBatchDraw(); // 开始批量绘图
        // 绘制标题栏
        setfillcolor(RGB(0, 168, 225));
        solidrectangle(0, 0, 1000, 50);
        settextcolor(RGB(255, 102, 0));
        setbkmode(TRANSPARENT);
        settextstyle(30, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
        outtextxy(500 - textwidth("Key Board MIDIPiano") / 2, 10, _T("Key Board MIDIPiano"));
        // 绘制状态栏
        setfillcolor(RGB(128, 0, 128));
        solidrectangle(0, 50, 1000, 100);
        settextcolor(RGB(255, 255, 255));
        setbkmode(TRANSPARENT);
        outtextxy(10, 60, _T("Voice:"));
        outtextxy(10 + textwidth("Voice:"), 60, midiSoundNamesEng[nowVoice].c_str());
        int textLength = 10 + textwidth("Voice:") + textwidth(midiSoundNamesEng[nowVoice].c_str()) + 20;
        outtextxy(textLength, 60, _T("Velocity:"));
        outtextxy(textLength + textwidth("Velocity:"), 60, std::to_string(nowVelocity).c_str());
        outtextxy(textLength + textwidth("Velocity:") + textwidth(std::to_string(nowVelocity).c_str()) + 20, 60,
                  _T("Playing:"));
        outtextxy(textLength + textwidth("Velocity:") + textwidth(std::to_string(nowVelocity).c_str()) + 20 +
                  textwidth("Playing:"), 60, playingMusicName.c_str());
        //绘制录制栏
        setfillcolor(RGB(0, 153, 78));
        solidrectangle(0, 100, 1000, 150);
        //绘制录制按钮
        setfillcolor(RGB(252, 211, 0));
        solidrectangle(20, 105, 120, 145);
        outtextxy(25, 110, "Record");
        if (isRecording) {
            setfillcolor(RGB(255, 0, 0));
            solidcircle(135, 125, 10);
        }
        //绘制播放按钮
        setfillcolor(RGB(252, 211, 0));
        solidrectangle(150, 105, 240, 145);
        outtextxy(175, 110, "Play");
        //绘制音量+按钮
        solidrectangle(270, 105, 390, 145);
        outtextxy(275, 110, "velocity+");
        //绘制音量-按钮
        solidrectangle(420, 105, 540, 145);
        outtextxy(425, 110, "velocity-");
        //绘制音色+按钮
        solidrectangle(570, 105, 690, 145);
        outtextxy(590, 110, "voice+");
        //绘制音色-按钮
        solidrectangle(720, 105, 840, 145);
        outtextxy(740, 110, "voice-");

        drawPianoKeys(); // 绘制琴键
        EndBatchDraw();// 结束批量绘图


    }
}
