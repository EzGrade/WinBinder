//
// Created by abore on 14.02.2024.
//

#include "Exe.h"

void Exe::open(const std::string &path) {
    ShellExecute(nullptr, "open", path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}