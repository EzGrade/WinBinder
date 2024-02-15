//
// Created by abore on 15.02.2024.
//

#include "Bind.h"


Keyboard Bind::setBinds() {
    Keyboard keyboard;
    json file = JsonUtil::read(R"(C:\Users\abore\CLionProjects\SimpleGUI\cfg\config.json)");
    json binds = file["binds"];
    int total = 0;
    for (auto &bind: binds) {
        if (bind["type"] == "text") {
            keyboard.addBind(bind["key"], bind["action"]);
        } else if (bind["type"] == "exe") {
            keyboard.addBindAction(bind["key"], new ExeAction(bind["path"]));
        } else if (bind["type"] == "url") {
            keyboard.addBindAction(bind["key"], new BrowserAction(bind["path"]));
        }
        total++;
    }
    std::cout << "Total binds: " << total << std::endl;
    return keyboard;
}