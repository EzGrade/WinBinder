//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_ACTION_H
#define SIMPLEGUI_ACTION_H


class Action {
public:
    virtual void execute() = 0; // Pure virtual function makes Actions an abstract base class
};


#endif //SIMPLEGUI_ACTION_H
