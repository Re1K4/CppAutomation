#pragma once

class SharedVariable {
public:
    static bool exit_loop;
    static int window_size_x;
    static int window_size_y;
    static int window_center_x;
    static int window_center_y;

private:
    SharedVariable() = delete;
};

