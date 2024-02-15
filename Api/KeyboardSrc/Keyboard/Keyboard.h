//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_KEYBOARD_H
#define SIMPLEGUI_KEYBOARD_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <array>
#include <windows.h>

#include "../../../Actions/ActionSrc/Action/Action.h"
#include "../Mappers/Mapper/Mapper.h"
#include "../Mappers/MixedMapper/MixedMapper.h"


class Keyboard {
private:
    int delay = 50;
    // Map of key binds
    // Key: string of keys separated by '+'
    // Value: vector of virtual key codes
    std::map<std::vector<int>, std::vector<int>> keyBinds;
    std::map<std::vector<int>, Action *> actionBinds;

public:
    void setDelay(int delayMs) {
        this->delay = delayMs;
    }

    static std::vector<int> parseBindKeys(std::string &bind);

    void addBind(const std::string &key, const std::string &command);

    void addBindAction(const std::string &key, Action *action);

    void executeBind(const std::vector<int> &key);

    int getMaxQueue();

    [[noreturn]] void keysLister();

    void sendMixedKeys(const std::vector<int> &keys) const;

    void pressKey(int key) const;

    void pressKey(const std::string &key) const;


    // Overloaded function to accept virtual key codes
    static void holdKey(int key);

    static void holdKey(const std::string &key);

    static void releaseKey(int key);

    static void releaseKey(const std::string &key);

    void printText(const std::string &text) const;
};


#endif //SIMPLEGUI_KEYBOARD_H
