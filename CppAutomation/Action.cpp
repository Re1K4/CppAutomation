#include "Action.h"

void Action::test() {
    Emulate::pressKey('T');
    Emulate::sleep(100);
    Emulate::releaseKey('T');

    Emulate::pressKey('E');
    Emulate::sleep(100);
    Emulate::releaseKey('E');

    Emulate::pressKey('S');
    Emulate::sleep(100);
    Emulate::releaseKey('S');

    Emulate::pressKey('T');
    Emulate::sleep(100);
    Emulate::releaseKey('T');
}