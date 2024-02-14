//
// Created by abore on 14.02.2024.
//

#ifndef SIMPLEGUI_MOUSE_H
#define SIMPLEGUI_MOUSE_H

#include <windows.h>

class Mouse {
public:
    static void move(int x, int y);

    static void leftDown();

    static void leftUp();

    static void leftDrag(int startX, int startY, int endX, int endY);

    static void rightClick();

    static void rightDown();

    static void rightUp();

    static void rightDrag(int startX, int startY, int endX, int endY);
};


#endif //SIMPLEGUI_MOUSE_H
