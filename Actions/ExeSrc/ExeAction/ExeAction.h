//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_EXEACTION_H
#define SIMPLEGUI_EXEACTION_H

#include <iostream>

#include "../../ActionSrc/Action/Action.h"
#include "../Exe/Exe.h"

class ExeAction : public Action {
private:
    std::string path;
public:
    explicit ExeAction(std::string path) : path(std::move(path)) {}

    void execute() override;
};


#endif //SIMPLEGUI_EXEACTION_H
