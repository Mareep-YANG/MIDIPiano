//
// Created by ly on 2023/10/25.
//
#include "iostream"
#include "windows.h"
#include "mmeapi.h"


using namespace std;

// 选择音频设备
int  CommandSelect(){
    int selectedMidiDev = 0;
    int numDev = midiOutGetNumDevs(); // 获取输出设备数量
    cout <<"共有"<< numDev <<"个波形输出设备"<< endl;
    cout <<"---------------------------"<<endl;
    for(int i = 0 ; i < numDev ;i++){
        MIDIOUTCAPS * devResult = new MIDIOUTCAPS; // 输出设备信息指针
        MMRESULT resultState =  midiOutGetDevCaps(i,devResult,sizeof(MIDIOUTCAPS)); // 获取状态
        if (resultState == MMSYSERR_NOERROR){ // 若获取成功
            // 打印设备信息
            cout << "第" << i+1<<"个输出设备信息:"<<endl;
            cout <<"制造商ID:"<< devResult ->wMid<<" "<<"产品ID:"<<devResult ->wPid << endl;
            printf("设备名称:%s\n",devResult->szPname);
            cout <<"---------------------------"<<endl;
        }
        else{// 获取失败
            cout << "第" << i+1 <<"个输出设备信息获取失败"<<endl;
        }
        delete devResult;
    }
    // 开始选择
    cout << "请输入使用的MIDI输出设备的编号:";
    cin >> selectedMidiDev ;
    if (cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "请不要输入非法字符" << endl;
    }
    selectedMidiDev--;
    if(selectedMidiDev < numDev){
        cout << "选择成功!可以开始演奏"<<endl;
    }
    else{
        cout << "无该输出设备!"<<endl;
        selectedMidiDev = 0;
    }
    return selectedMidiDev;
}


