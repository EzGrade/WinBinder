//
// Created by abore on 14.02.2024.
//

#include "Keyboard.h"

std::vector<int> Keyboard::parseBindKeys(std::string &bind) {
    std::vector<int> keys;
    std::vector<std::string> splitKeys;
    std::string temp_str;
    for (char c: bind) {
        if (c == '+') {
            splitKeys.push_back(temp_str);
            temp_str = "";
        } else {
            temp_str += c;
        }
    }
    splitKeys.push_back(temp_str);
    for (const std::string &c: splitKeys) {
        int temp = Mapper::mapKeys(c);
        if (temp != 0) {
            keys.push_back(temp);
        } else {
            temp = Mapper::mapKeys(c);
            if (temp != 0) {
                keys.push_back(Mapper::mapKeys("lshift"));
                keys.push_back(temp);
            } else {
                std::vector<int> mixedKeys = MixedMapper::mapMixed(c);
                for (int i: mixedKeys) {
                    keys.push_back(i);
                }
            }
        }
    }
    return keys;
}

void Keyboard::addBind(const std::string &key, const std::string &command) {
    std::vector<int> keys;

    // Split the key string by '+'
    keys = parseBindKeys(const_cast<std::string &>(key));


    // Map the command to its virtual key codes
    std::vector<int> commandKeys;
    for (char c: command) {
        int temp = Mapper::mapKeys(std::string(1, c));
        if (temp != 0) {
            commandKeys.push_back(temp);
        } else {
            temp = Mapper::mapKeys(std::string(1, tolower(c)));
            if (temp != 0) {
                commandKeys.push_back(Mapper::mapKeys("lshift"));
                commandKeys.push_back(temp);
            } else {
                std::vector<int> mixedKeys = MixedMapper::mapMixed(std::string(1, c));
                for (int i: mixedKeys) {
                    commandKeys.push_back(i);
                }
            }
        }
    }

    // Sort the keys
    std::sort(keys.begin(), keys.end());
    this->keyBinds[keys] = commandKeys;
}

void Keyboard::addBindAction(const std::string &key, Action *action) {
    std::vector<int> keys = parseBindKeys(const_cast<std::string &>(key));
    std::sort(keys.begin(), keys.end());
    this->actionBinds[keys] = action;
}

void Keyboard::executeBind(const std::vector<int> &key) {
    if (this->keyBinds.find(key) != this->keyBinds.end()) {
        sendMixedKeys(this->keyBinds[key]);
    }
}

int Keyboard::getMaxQueue() {
    auto max = 0;
    for (auto &bind: this->keyBinds) {
        if (bind.first.size() > max) {
            max = bind.first.size();
        }
    }
    return max;
}

[[noreturn]] void Keyboard::keysLister() {
    std::cout << "Listening for keys..." << std::endl;
    std::set<int> pressed_keys;
    std::array<SHORT, 256> keyStates{};
    while (true) {
        // Get the state of all keys
        for (int i = 0; i < 256; i++) {
            keyStates[i] = GetAsyncKeyState(i);
        }
        for (int i = 8; i <= 190; i++) {
            if (i == VK_CONTROL || i == VK_SHIFT || i == VK_MENU) {
                continue;
            }
            bool isKeyDown = (keyStates[i] & 0x8000) != 0;
            if (isKeyDown && pressed_keys.find(i) == pressed_keys.end()) {
                pressed_keys.insert(i);
            } else if (!isKeyDown && pressed_keys.find(i) != pressed_keys.end()) {
                for (auto &bind: this->keyBinds) {
                    if (bind.first.size() > pressed_keys.size()) {
                        continue;
                    }
                    bool found = true;

                    for (int j = 0; j < bind.first.size(); j++) {
                        if (pressed_keys.find(bind.first[j]) == pressed_keys.end()) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        // Release all keys
                        for (int j: pressed_keys) {
                            releaseKey(j);
                        }
                        executeBind(bind.first);
                    }
                }
                for (auto &bind: this->actionBinds) {
                    if (bind.first.size() > pressed_keys.size()) {
                        continue;
                    }
                    bool found = true;

                    for (int j = 0; j < bind.first.size(); j++) {
                        if (pressed_keys.find(bind.first[j]) == pressed_keys.end()) {
                            found = false;
                            break;
                        }
                    }
                    if (found) {
                        // Release all keys
                        for (int j: pressed_keys) {
                            releaseKey(j);
                        }
                        bind.second->execute();
                    }
                }
                pressed_keys.erase(i);
            }
        }
    }
}

void Keyboard::sendMixedKeys(const std::vector<int> &keys) const {
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == 0xA0 || keys[i] == 0xA1) {
            holdKey(keys[i]);
            pressKey(keys[i + 1]);
            releaseKey(keys[i]);
            i++;
        } else {
            pressKey(keys[i]);
        }
    }
    for (int key: keys) {
        releaseKey(key);
    }
}

void Keyboard::pressKey(int key) const {
    holdKey(key);
    Sleep(this->delay);
    releaseKey(key);
}

void Keyboard::pressKey(const std::string &key) const {
    holdKey(key);
    Sleep(this->delay);
    releaseKey(key);
}

void Keyboard::holdKey(int key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::holdKey(const std::string &key) {
    int intKey = Mapper::mapKeys(key);
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = intKey;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::releaseKey(int key) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::releaseKey(const std::string &key) {
    int intKey = Mapper::mapKeys(key);
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = intKey;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

void Keyboard::printText(const std::string &text) const {
    for (char c: text) {
        int temp = Mapper::mapKeys(std::string(1, c));
        if (temp != 0) {
            pressKey(std::string(1, c));
        } else {
            temp = Mapper::mapKeys(std::string(1, tolower(c)));
            if (temp != 0) {
                holdKey("lshift");
                pressKey(std::string(1, tolower(c)));
                releaseKey("lshift");
            } else {
                std::vector<int> keys = MixedMapper::mapMixed(std::string(1, c));
                sendMixedKeys(keys);
            }
        }
    }
}