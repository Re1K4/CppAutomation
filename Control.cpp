#include "Control.h"

Control::Control() {};

void Control::changeCtrl(int ctrl) {
    PREV = NOW;
    NOW = ctrl;

    Logger::info("ChangeControl [" + std::to_string(PREV) + "] ÅÀ [" + std::to_string(NOW) + "]");
}