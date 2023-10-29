//
// Created by ly on 2023/10/29.
//
#include <string>
#include "map"
#include "windows.h"
#include "./Logger.cpp"
using namespace std;
class KeyManager {
public:
    void addMapping(int key, const string& shortName){
        if (keyMap.find(key) == keyMap.end()){
            keyMap.insert(pair<int, string>(key, shortName));
        }
        else{
            //已经存在
            Logger::warn("已经存在"+ to_string(MapVirtualKey(key, 2))+"键的映射,请检查音符文件,将覆盖!");
            keyMap[key] = shortName;
        }

    }
    string getKeyNote(int key){
        if (keyMap.find(key) == keyMap.end()){
            Logger::warn("未找到"+ to_string(MapVirtualKey(key, 2))+"键的映射,请检查音符文件!");
            return "";
        }
        else{
            return keyMap[key];
        }
    }
private:
    map<int, string> keyMap;
};