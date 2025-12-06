#include "Emulate.h"

void Emulate::pressKey(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, 0);
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    // Key press
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::releaseKey(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, 0);
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    // Key release
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::moveMouse(int x, int y) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = x - SharedVariable::window_center_x;
    input.mi.dy = y - SharedVariable::window_center_y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    // Move mouse relative coordinate
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::moveMouseRel(int dx, int dy) {
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;
    input.mi.dx = dx;
    input.mi.dy = dy;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    // Move mouse relative coordinate
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::pressMouseLeft() {
    INPUT input[1] = {};

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, input, sizeof(INPUT));
}

void Emulate::releaseMouseLeft() {
    INPUT input[1] = {};

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, input, sizeof(INPUT));
}

void Emulate::pressMouseRight() {
    INPUT input[1] = {};

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    SendInput(1, input, sizeof(INPUT));
}

void Emulate::releaseMouseRight() {
    INPUT input[1] = {};

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(1, input, sizeof(INPUT));
}

void Emulate::sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}