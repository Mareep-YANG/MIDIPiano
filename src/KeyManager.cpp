//
// Created by ly on 2023/10/29.
//
/*
 * 该类用于管理键盘映射
 * 该类提供了添加映射和获取映射的方法
 */
#include <string>
#include "map"
#include "windows.h"
#include "./Logger.cpp"

using namespace std;

class KeyManager {
public:
    void addMapping(int key, const string &shortName) {
        if (keyMap.find(key) == keyMap.end()) {
            keyMap.insert(pair<int, string>(key, shortName));
        } else {
            //已经存在
            Logger::warn("已经存在" + to_string(MapVirtualKey(key, 0)) + "键的映射,请检查音符文件,将覆盖!");
            keyMap[key] = shortName;
        }

    }

    string getKeyNote(int key) {
        if (keyMap.find(key) == keyMap.end()) {
            Logger::warn("未找到" + to_string(MapVirtualKey(key, 0)) + "键的映射,请检查音符文件!");
            return "";
        } else {
            return keyMap[key];
        }
    }

    //获取所有键盘映射
    void commandMap() {
        Logger::info("当前键盘映射:");
        for (auto &it: keyMap) {
            Logger::info(to_string(MapVirtualKey(it.first, 2)) + " -> " + it.second);
        }
    }

private:
    map<int, string> keyMap;
};