//
// Created by ly on 2023/10/25.
//
#include "windows.h"
#include "string"
using namespace std;
class NoteEntity {
public:
    BYTE noteNo;
    BYTE velocity;
    int voiceNumber;
    string shortName;
    int key;
    NoteEntity() {
        this->noteNo = 0;
        this->velocity = 0;
        this->voiceNumber = 0;
        this->shortName = "";
        this->key = 0;
    };
    NoteEntity(const BYTE& noteNo, const BYTE& velocity, const int& voiceNumber, const string& shortName , const int& key) {
        this->noteNo = noteNo;
        this->velocity = velocity;
        this->voiceNumber = voiceNumber;
        this->shortName = shortName;
        this->key = key;
    }
};