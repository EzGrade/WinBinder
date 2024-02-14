//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_BROWSERACTION_H
#define SIMPLEGUI_BROWSERACTION_H

#include <iostream>
#include "Actions/ActionSrc/Action/Action.h"
#include "../Browser/Browser.h"

class BrowserAction : public Action {
private:
    std::string url;
public:
    explicit BrowserAction(std::string url) : url(std::move(url)) {}
    void execute() override;
};


#endif //SIMPLEGUI_BROWSERACTION_H
