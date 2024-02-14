//
// Created by abore on 14.02.2024.
//

#include "Screen.h"

int Screen::getWidth()  {
    return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::getHeight() {
    return GetSystemMetrics(SM_CYSCREEN);
}