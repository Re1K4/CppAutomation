#include "Emulate.h"

static InterceptionContext context = interception_create_context();
static InterceptionDevice keyboard = INTERCEPTION_KEYBOARD(1);
static InterceptionDevice mouse = INTERCEPTION_MOUSE(1);

void Emulate::pressKey(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;

    // Key press
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::releaseKey(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    // Key release
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::pressKeyDirectX(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, 0);
    input.ki.dwFlags = KEYEVENTF_SCANCODE;

    // Key press
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::releaseKeyDirectX(WORD key) {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(key, 0);
    input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;

    // Key release
    SendInput(1, &input, sizeof(INPUT));
}

void Emulate::pressKeyInterCeption(WORD vk) {
    InterceptionKeyStroke stroke;
    stroke.code = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
    stroke.state = INTERCEPTION_KEY_DOWN;
    stroke.information = 0;

    interception_send(context, keyboard, (InterceptionStroke*)&stroke, 1);
}

void Emulate::releaseKeyInterCeption(WORD vk) {
    InterceptionKeyStroke stroke;
    stroke.code = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
    stroke.state = INTERCEPTION_KEY_UP;
    stroke.information = 0;

    interception_send(context, keyboard, (InterceptionStroke*)&stroke, 1);
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

void Emulate::moveMouseInterCeption(int x, int y) {
    InterceptionMouseStroke stroke;
    stroke.state = 0;
    stroke.flags = MOUSE_MOVE_ABSOLUTE;
    stroke.rolling = 0;
    stroke.x = x - SharedVariable::window_center_x;
    stroke.y = y - SharedVariable::window_center_y;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
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

void Emulate::moveMouseRelInterCeption(int dx, int dy) {
    InterceptionMouseStroke stroke;
    stroke.state = 0;
    stroke.flags = MOUSE_MOVE_RELATIVE;
    stroke.rolling = 0;
    stroke.x = dx;
    stroke.y = dy;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
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

void Emulate::pressMouseLeftInterception() {
    InterceptionMouseStroke stroke;
    stroke.state = INTERCEPTION_MOUSE_LEFT_BUTTON_DOWN;
    stroke.flags = 0;
    stroke.rolling = 0;
    stroke.x = 0;
    stroke.y = 0;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
}

void Emulate::releaseMouseLeftInterception() {
    InterceptionMouseStroke stroke;
    stroke.state = INTERCEPTION_MOUSE_LEFT_BUTTON_UP;
    stroke.flags = 0;
    stroke.rolling = 0;
    stroke.x = 0;
    stroke.y = 0;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
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

void Emulate::pressMouseRightInterception() {
    InterceptionMouseStroke stroke;
    stroke.state = INTERCEPTION_MOUSE_RIGHT_BUTTON_DOWN;
    stroke.flags = 0;
    stroke.rolling = 0;
    stroke.x = 0;
    stroke.y = 0;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
}

void Emulate::releaseMouseRightInterception() {
    InterceptionMouseStroke stroke;
    stroke.state = INTERCEPTION_MOUSE_RIGHT_BUTTON_UP;
    stroke.flags = 0;
    stroke.rolling = 0;
    stroke.x = 0;
    stroke.y = 0;
    stroke.information = 0;

    interception_send(context, mouse, (InterceptionStroke*)&stroke, 1);
}

void Emulate::sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}