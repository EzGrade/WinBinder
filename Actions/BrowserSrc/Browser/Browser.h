//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_BROWSER_H
#define SIMPLEGUI_BROWSER_H

#pragma once

#include <iostream>
#include <windows.h>

#include "Actions/ActionSrc/Action/Action.h"

class Browser {
public:
    static void open(const std::string &url);
};


#endif //SIMPLEGUI_BROWSER_H
