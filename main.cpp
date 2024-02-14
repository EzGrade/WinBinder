#include <windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <array>

class Mouse {
public:
    static void move(int x, int y) {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
        input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
        SendInput(1, &input, sizeof(INPUT));
    }

    static void leftDown() {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void leftUp() {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void leftDrag(int startX, int startY, int endX, int endY) {
        move(startX, startY);
        Sleep(50);
        leftDown();
        Sleep(50);
        move(endX, endY);
        Sleep(50);
        leftUp();
    }

    static void rightClick() {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }

    static void rightDown() {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void rightUp() {
        INPUT input = {0};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        SendInput(1, &input, sizeof(INPUT));
    }

    static void rightDrag(int startX, int startY, int endX, int endY) {
        move(startX, startY);
        Sleep(50);
        rightDown();
        Sleep(50);
        move(endX, endY);
        Sleep(50);
        rightUp();
    }
};


class Keyboard {
private:
    int delay = 50;
    // Map of key binds
    // Key: string of keys separated by '+'
    // Value: vector of virtual key codes
    std::map<std::vector<int>, std::vector<int>> keyBinds;

public:
    void setDelay(int delayMs) {
        this->delay = delayMs;
    }

    void addBind(const std::string &key, const std::string &command) {
        std::vector<int> keys;

        // Split the key string by '+'
        std::vector<std::string> splitKeys;
        std::string temp_str;
        for (char c: key) {
            if (c == '+') {
                splitKeys.push_back(temp_str);
                temp_str = "";
            } else {
                temp_str += c;
            }
        }
        splitKeys.push_back(temp_str);

        // Map the keys to their virtual key codes
        for (const std::string &c: splitKeys) {
            int temp = mapKeys(c);
            if (temp != 0) {
                keys.push_back(temp);
            } else {
                temp = mapKeys(c);
                if (temp != 0) {
                    keys.push_back(mapKeys("lshift"));
                    keys.push_back(temp);
                } else {
                    std::vector<int> mixedKeys = mapMixed(c);
                    for (int i: mixedKeys) {
                        keys.push_back(i);
                    }
                }
            }
        }

        // Map the command to its virtual key codes
        std::vector<int> commandKeys;
        for (char c: command) {
            int temp = mapKeys(std::string(1, c));
            if (temp != 0) {
                commandKeys.push_back(temp);
            } else {
                temp = mapKeys(std::string(1, tolower(c)));
                if (temp != 0) {
                    commandKeys.push_back(mapKeys("lshift"));
                    commandKeys.push_back(temp);
                } else {
                    std::vector<int> mixedKeys = mapMixed(std::string(1, c));
                    for (int i: mixedKeys) {
                        commandKeys.push_back(i);
                    }
                }
            }
        }

        std::cout << "Adding bind: ";
        std::cout << "Keys: ";
        for (int i: keys) {
            std::cout << i << " ";
        }
        std::cout << "Command: ";
        for (int i: commandKeys) {
            std::cout << i << " ";
        }

        this->keyBinds[keys] = commandKeys;
    }

    void executeBind(const std::vector<int> &key) {
        if (this->keyBinds.find(key) != this->keyBinds.end()) {
            sendMixedKeys(this->keyBinds[key]);
        }
    }

    int getMaxQueue() {
        auto max = 0;
        for (auto &bind: this->keyBinds) {
            if (bind.first.size() > max) {
                max = bind.first.size();
            }
        }
        return max;
    }

    [[noreturn]] void keysLister() {
        std::cout << "Listening for keys..." << std::endl;
        std::set<int> pressed_keys;
        std::array<SHORT, 256> keyStates;
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
                    pressed_keys.erase(i);
                }
            }

            for (auto &bind: this->keyBinds) {
                if (bind.first.size() > pressed_keys.size()) {
                    continue;
                }
                bool match = true;
                for (int j = 0; j < bind.first.size(); j++) {
                    if (bind.first[j] != *std::next(pressed_keys.begin(), j)) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    // Release all keys
                    for (int i: pressed_keys) {
                        releaseKey(i);
                    }
                    executeBind(bind.first);
                }
            }
        }
    }

    // Map of virtual key codes: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    static int mapKeys(const std::string &key) {
        if (key == "a") {
            return 0x41;
        } else if (key == "b") {
            return 0x42;
        } else if (key == "c") {
            return 0x43;
        } else if (key == "d") {
            return 0x44;
        } else if (key == "e") {
            return 0x45;
        } else if (key == "f") {
            return 0x46;
        } else if (key == "g") {
            return 0x47;
        } else if (key == "h") {
            return 0x48;
        } else if (key == "i") {
            return 0x49;
        } else if (key == "j") {
            return 0x4A;
        } else if (key == "k") {
            return 0x4B;
        } else if (key == "l") {
            return 0x4C;
        } else if (key == "m") {
            return 0x4D;
        } else if (key == "n") {
            return 0x4E;
        } else if (key == "o") {
            return 0x4F;
        } else if (key == "p") {
            return 0x50;
        } else if (key == "q") {
            return 0x51;
        } else if (key == "r") {
            return 0x52;
        } else if (key == "s") {
            return 0x53;
        } else if (key == "t") {
            return 0x54;
        } else if (key == "u") {
            return 0x55;
        } else if (key == "v") {
            return 0x56;
        } else if (key == "w") {
            return 0x57;
        } else if (key == "x") {
            return 0x58;
        } else if (key == "y") {
            return 0x59;
        } else if (key == "z") {
            return 0x5A;
        } else if (key == "0") {
            return 0x30;
        } else if (key == "1") {
            return 0x31;
        } else if (key == "2") {
            return 0x32;
        } else if (key == "3") {
            return 0x33;
        } else if (key == "4") {
            return 0x34;
        } else if (key == "5") {
            return 0x35;
        } else if (key == "6") {
            return 0x36;
        } else if (key == "7") {
            return 0x37;
        } else if (key == "8") {
            return 0x38;
        } else if (key == "9") {
            return 0x39;
        } else if (key == "enter") {
            return 0x0D;
        } else if (key == "space" || key == " ") {
            return 0x20;
        } else if (key == "backspace") {
            return 0x08;
        } else if (key == "tab") {
            return 0x09;
        } else if (key == "esc") {
            return 0x1B;
        } else if (key == "up") {
            return 0x26;
        } else if (key == "down") {
            return 0x28;
        } else if (key == "left") {
            return 0x25;
        } else if (key == "right") {
            return 0x27;
        } else if (key == "f1") {
            return 0x70;
        } else if (key == "f2") {
            return 0x71;
        } else if (key == "f3") {
            return 0x72;
        } else if (key == "f4") {
            return 0x73;
        } else if (key == "f5") {
            return 0x74;
        } else if (key == "f6") {
            return 0x75;
        } else if (key == "f7") {
            return 0x76;
        } else if (key == "f8") {
            return 0x77;
        } else if (key == "f9") {
            return 0x78;
        } else if (key == "f10") {
            return 0x79;
        } else if (key == "f11") {
            return 0x7A;
        } else if (key == "f12") {
            return 0x7B;
        } else if (key == ",") {
            return 0xBC;
        } else if (key == ".") {
            return 0xBE;
        } else if (key == "/") {
            return 0xBF;
        } else if (key == "`") {
            return 0xC0;
        } else if (key == "[") {
            return 0xDB;
        } else if (key == "\\") {
            return 0xDC;
        } else if (key == "]") {
            return 0xDD;
        } else if (key == "'") {
            return 0xDE;
        } else if (key == "-") {
            return 0xBD;
        } else if (key == "=") {
            return 0xBB;
        } else if (key == "ctrl") {
            return 0x11;
        } else if (key == "alt") {
            return 0x12;
        } else if (key == "lshift") {
            return 0xA0;
        } else if (key == "rshift") {
            return 0xA1;
        } else if (key == "caps") {
            return 0x14;
        } else {
            return 0;
        }
    }

    std::vector<int> mapMixed(const std::string &key) {
        std::vector<int> keys;
        if (key == "!") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("1"));
        } else if (key == "@") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("2"));
        } else if (key == "#") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("3"));
        } else if (key == "$") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("4"));
        } else if (key == "%") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("5"));
        } else if (key == "^") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("6"));
        } else if (key == "&") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("7"));
        } else if (key == "*") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("8"));
        } else if (key == "(") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("9"));
        } else if (key == ")") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("0"));
        } else if (key == "_") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("-"));
        } else if (key == "+") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("="));
        } else if (key == "{") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("["));
        } else if (key == "}") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("]"));
        } else if (key == "|") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("\\"));
        } else if (key == ":") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys(";"));
        } else if (key == "\"") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("'"));
        } else if (key == "<") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys(","));
        } else if (key == ">") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("."));
        } else if (key == "?") {
            keys.push_back(mapKeys("lshift"));
            keys.push_back(mapKeys("/"));
        }
        return keys;
    }

    void sendMixedKeys(const std::vector<int> &keys) {
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

    void pressKey(int key) const {
        holdKey(key);
        Sleep(this->delay);
        releaseKey(key);
    }

    void pressKey(const std::string &key) const {
        holdKey(key);
        Sleep(this->delay);
        releaseKey(key);
    }


    // Overloaded function to accept virtual key codes
    static void holdKey(int key) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = key;
        input.ki.dwFlags = 0;

        SendInput(1, &input, sizeof(INPUT));
    }

    static void holdKey(const std::string &key) {
        int intKey = mapKeys(key);
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = intKey;
        input.ki.dwFlags = 0;

        SendInput(1, &input, sizeof(INPUT));
    }

    static void releaseKey(int key) {
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = key;
        input.ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(1, &input, sizeof(INPUT));
    }

    static void releaseKey(const std::string &key) {
        int intKey = mapKeys(key);
        INPUT input;
        input.type = INPUT_KEYBOARD;
        input.ki.wVk = intKey;
        input.ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(1, &input, sizeof(INPUT));
    }

    void printText(const std::string &text) {
        for (char c: text) {
            int temp = mapKeys(std::string(1, c));
            if (temp != 0) {
                pressKey(std::string(1, c));
            } else {
                temp = mapKeys(std::string(1, tolower(c)));
                if (temp != 0) {
                    holdKey("lshift");
                    pressKey(std::string(1, tolower(c)));
                    releaseKey("lshift");
                } else {
                    std::vector<int> keys = mapMixed(std::string(1, c));
                    sendMixedKeys(keys);
                }
            }
        }
    }

};


int main() {
    Keyboard keyboard;
    keyboard.setDelay(0);
    keyboard.addBind("lshift+rshift", "aborecevskij94@gmail.com");
    keyboard.keysLister();
};