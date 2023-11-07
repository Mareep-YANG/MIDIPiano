//
// Created by ly on 2023/11/7.
//
#pragma once
#include <vector>
#include "string"
#include "MusicNoteEntity.cpp"
class MusicEntity{
public:
    std::string name;// 曲谱名
    std::vector<MusicNoteEntity> notes;// 音符列表
    MusicEntity(const std::string & name , const std::vector<MusicNoteEntity> & notes){
        this->name = name;
        this->notes = notes;
    }
    MusicEntity() = default;
};