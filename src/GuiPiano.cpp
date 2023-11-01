//
// Created by ly on 2023/11/1.
//
#include <graphics.h>
#include "thread"

//函数声明
void commandStart(int);// 开始演奏
void drawPianoKeys();

// 全局变量
extern int selectedMidiDev;
std::thread playThread;

void initGui() {
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
            loadimage(&img, _T("./resource/op.png"));
            putimage(0, 100, &img);
            drawPianoKeys();
            EndBatchDraw();
        }
        ExMessage msg{};
        msg = getmessage(EX_KEY);
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
    setfillcolor(WHITE);
    char keyOne[] {'Z','X','C','V','B','N','M','<','>','/'};
    char keyTwo[] {'A','S','D','F','G','H','J','K','L',';','"'};
    char keyThree[] {'Q','W','E','R','T','Y','U','I','O','P','[','\\'};
    for (int i = 4; i < numKeys - 4; i++) {
        solidrectangle(i * keyWidth, 470, (i + 1) * keyWidth, 470 + keyHeight);
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20, 0, _T("Tahoma"), 0, 0, 1000, false, false, false);
        outtextxy(i * keyWidth + 20, 470 + keyHeight - 30, keyOne[i - 4]);
        setlinecolor(BLACK);
        line(i * keyWidth, 470, i * keyWidth, 470 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224, 470 - 5, 784, 470);
    //  第二行 11键
    setfillcolor(WHITE);
    for (int i = 3; i < numKeys - 4; i++) {
        solidrectangle(i * keyWidth + 28, 335, (i + 1) * keyWidth + 28, 335 + keyHeight);
        outtextxy(28+i * keyWidth + 20, 335 + keyHeight - 30, keyTwo[i - 3]);
        line(i * keyWidth + 28, 335, i * keyWidth + 28, 335 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224-28, 335 - 5, 784+28, 335);
    // 第三行 13键
    setfillcolor(WHITE);
    for (int i = 3; i < numKeys - 2; i++) {
        solidrectangle(i * keyWidth + 28 - 56, 200, (i + 1) * keyWidth + 28 - 56, 200 + keyHeight);
        outtextxy(i * keyWidth + 20+ 28 - 56, 200 + keyHeight - 30, keyThree[i - 3]);
        line(i * keyWidth + 28 - 56, 200, i * keyWidth + 28 - 56, 200 + keyHeight);
    }
    setfillcolor(RED);
    solidrectangle(224-28 - 56, 200 - 5, 784+28 + 56, 200);

}
