//
// Created by abore on 14.02.2024.
//

#include "Mapper.h"

int Mapper::mapKeys(const std::string &key) {
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
    } else if (key == "lctrl" || key == "ctrl") {
        return 162;
    } else if (key == "rctrl") {
        return 163;
    } else if (key == "lalt" || key == "alt") {
        return 164;
    } else if (key == "ralt") {
        return 165;
    } else if (key == "lshift" || key == "shift") {
        return 0xA0;
    } else if (key == "rshift") {
        return 0xA1;
    } else if (key == "caps") {
        return 0x14;
    } else {
        return 0;
    }
}