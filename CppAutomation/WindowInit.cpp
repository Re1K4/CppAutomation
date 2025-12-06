#include "WindowInit.h"

void WindowInit(const char* app_name) {
    
    HWND app_window = FindWindowA(nullptr, app_name);
    if (!app_window) {
        Logger::error("GameWindows is NotFound");
        std::exit(EXIT_FAILURE);
    }

    // Set window in foreground
    SetForegroundWindow(app_window);

    RECT rect;
    GetWindowRect(app_window, &rect);

    SharedVariable::window_size_x = rect.right - rect.left;
    SharedVariable::window_size_y = rect.bottom - rect.top;
    SharedVariable::window_center_x = SharedVariable::window_size_x / 2;
    SharedVariable::window_center_y = SharedVariable::window_size_y / 2;

    // Update window position and size
    MoveWindow(app_window, 0, 0, SharedVariable::window_size_x, SharedVariable::window_size_y, TRUE);
}
