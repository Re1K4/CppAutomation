#include "CheckEscKey.h"

void CheckEscKey() {
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {  // Check if the ESC key is pressed
            Logger::info("ESC key pressed, End Script");
            SharedVariable::exit_loop = true;  // main Set the exit flag for the permanent loop
            break;
        }
        Emulate::sleep(10);
    }
}