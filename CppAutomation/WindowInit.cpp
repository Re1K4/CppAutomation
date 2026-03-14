#include "WindowInit.h"

// char* Å® wstring
static std::wstring ToWide(const char* s) {
    if (!s) return L"";
    int len = MultiByteToWideChar(CP_UTF8, 0, s, -1, nullptr, 0);
    if (len <= 0) {
        len = MultiByteToWideChar(CP_ACP, 0, s, -1, nullptr, 0);
        if (len <= 0) return L"";
        std::wstring w(len - 1, L'\0');
        MultiByteToWideChar(CP_ACP, 0, s, -1, w.data(), len);
        return w;
    }
    std::wstring w(len - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s, -1, w.data(), len);
    return w;
}

// Search for the top-level window by process name
static HWND FindWindowByProcessName(const wchar_t* targetExe) {
    struct Ctx { const wchar_t* target; HWND hit; } ctx{ targetExe, nullptr };

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        auto* c = reinterpret_cast<Ctx*>(lParam);

        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (!pid) return TRUE;

        HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (!hProc) return TRUE;

        wchar_t path[MAX_PATH] = {};
        DWORD size = MAX_PATH;
        BOOL ok = QueryFullProcessImageNameW(hProc, 0, path, &size);
        CloseHandle(hProc);
        if (!ok) return TRUE;

        // Extract the filename portion
        const wchar_t* last = wcsrchr(path, L'\\');
        const wchar_t* name = last ? (last + 1) : path;

        if (_wcsicmp(name, c->target) == 0) {
            c->hit = hwnd;
            return FALSE; // Found, so listing complete.
        }
        return TRUE;
        }, reinterpret_cast<LPARAM>(&ctx));

    return ctx.hit;
}

void WindowInit(const char* app_name) {
    std::wstring targetExe = ToWide(app_name);
    HWND app_window = FindWindowByProcessName(targetExe.c_str());

    if (!app_window) {
        Logger::error(std::string("Process window not found: ") + (app_name ? app_name : "(null)"));
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
