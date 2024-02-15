//
// Created by abore on 15.02.2024.
//

#ifndef SIMPLEGUI_BIND_H
#define SIMPLEGUI_BIND_H

#include "nlohmann/json.hpp"
#include "Utils/Json/JsonUtil.h"

#include "Api/KeyboardSrc/Keyboard/Keyboard.h"
#include "Actions//ExeSrc/ExeAction/ExeAction.h"
#include "Actions//BrowserSrc/BrowserAction/BrowserAction.h"

using json = nlohmann::json;

class Bind : Keyboard {
public:
    static Keyboard setBinds();
};


#endif //SIMPLEGUI_BIND_H
