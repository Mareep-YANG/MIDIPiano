//
// Created by ly on 2023/10/25.
//

/*
 * 该类用于存储音符信息
 * noteNo:音符号
 * velocity:力度
 * shortName:音符代码
 * key:键盘按键
 * */
#pragma once
#include "windows.h"
#include "string"


class NoteEntity {
public:
    BYTE noteNo;
    std::string shortName;
    int key;

    NoteEntity() {
        this->noteNo = 0;
        this->shortName = "";
        this->key = 0;
    };

    NoteEntity(const BYTE &noteNo, const std::string &shortName, int key) {
        this->noteNo = noteNo;
        this->shortName = shortName;
        this->key = key;
    }
};