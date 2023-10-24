// -*- coding: utf-8 -*-

#include <iostream>
#include <windows.h>
#include "mmeapi.h"
#include "cstring"

int selectedMidiDev = 0 ;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "欢迎使用MIDI电子琴,键入help以获取帮助"<<std::endl;
    while(true){
        using namespace std;
        //输入操作符
        string s;

        cout <<"请输入指令>";
        cin >> s;
        // 选择使用的MIDI输出设备
        if(s == "select"){

            int numDev = waveOutGetNumDevs(); // 获取输出设备数量
            cout <<"共有"<< numDev <<"个波形输出设备"<< endl;
            cout <<"---------------------------"<<endl;
            for(int i = 0 ; i < numDev ;i++){
                WAVEOUTCAPS *devResult; // 输出设备信息指针
                MMRESULT resultState =  waveOutGetDevCaps(i,devResult,sizeof(WAVEOUTCAPS)); // 获取状态
                if (resultState == MMSYSERR_NOERROR){ // 若获取成功
                    // 打印设备信息
                    cout << "第" << i+1<<"个输出设备信息:"<<endl;
                    cout <<"制造商ID:"<< devResult ->wMid<<" "<<"产品ID:"<<devResult ->wPid << endl;
                    printf("设备名称:%s\n",devResult->szPname);
                    cout <<"---------------------------"<<endl;
                }
                else{// 获取失败
                    cout << "第" << i+1 <<"个输出设备信息获取失s败"<<endl;
                }
            }
            // 开始选择
            cout << "请输入使用的MIDI输出设备的编号:";
            cin >> selectedMidiDev ;
            selectedMidiDev--;
            if(selectedMidiDev < numDev){
                cout << "选择成功!可以开始演奏"<<endl;
            }
            else{
                cout << "无该输出设备!"<<endl;
                selectedMidiDev = 0;
            }
        }

        // 帮助
        if(s == "help"){
           cout <<  "---------------------------" << endl;
           cout << "help -> 打印帮助信息" << endl;
           cout << "select -> 选择MIDI输出设备" << endl;
           cout << "start -> 开始MIDI演奏"<<endl;
           cout << "exit -> 退出程序"<<endl;
           cout <<"---------------------------"<<endl;
        }
        // 开始演奏
        if(s == "start"){

        }



        // 退出程序
        if (s == "exit"){
            return 0;
        }
    }

}
