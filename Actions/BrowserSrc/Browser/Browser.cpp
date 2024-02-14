//
// Created by abore on 14.02.2024.
//

#include "Browser.h"

void Browser::open(const std::string &url) {
    ShellExecute(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}