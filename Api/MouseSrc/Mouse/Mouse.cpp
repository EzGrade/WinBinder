//
// Created by abore on 14.02.2024.
//

#include "Mouse.h"

void Mouse::move(int x, int y) {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
    input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::leftDown() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::leftUp() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::leftDrag(int startX, int startY, int endX, int endY) {
    move(startX, startY);
    Sleep(50);
    leftDown();
    Sleep(50);
    move(endX, endY);
    Sleep(50);
    leftUp();
}

void Mouse::rightClick() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void Mouse::rightDown() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::rightUp() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void Mouse::rightDrag(int startX, int startY, int endX, int endY) {
    move(startX, startY);
    Sleep(50);
    rightDown();
    Sleep(50);
    move(endX, endY);
    Sleep(50);
    rightUp();
}