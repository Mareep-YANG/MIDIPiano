//
// Created by ly on 2023/11/7.
//
#pragma once
#include "string"
class MusicNoteEntity {
public:
    std::string shortName;// 音符唯一标识符
    double time;// 音符时间(相对曲谱开始)
    bool isDown;// 是否为按下
    MusicNoteEntity(const std::string & shortName , double time , bool isDown){
        this->shortName = shortName;
        this->time = time;
        this->isDown = isDown;
    }
};