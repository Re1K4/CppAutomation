#include "resource.h"
#include "Event.h"
#include "Timer.h"
#include "Logger.h"
#include "SharedVariable.h"
#include "Control.h"
#include "WindowInit.h"
#include "CheckEscKey.h"
#include "Action.h"
#include "TemplateMatching.h"
#include "Emulate.h"
#include "MultiEvent.h"

int main() {
    //Logger Test
    Logger::initialize("", true);
    Logger::info("This is an informational message");
    Logger::warning("This is a warning message");
    Logger::error("This is an error message");

    //Timer Test
    Timer tm;
    tm.set();
    Logger::info("Timer Test:" + std::to_string(tm.distance()));

    //Control Test
    Control control;
    Logger::info("Default Control:" + std::to_string(control.NOW));
    control.changeCtrl(10);

    //Window initialization test
    WindowInit("無題 - メモ帳");

    //CheckEscKey Test(ESC key to force thread termination)
    Logger::info("ESC Check Thread On");
    std::thread CheckEscKey_Thread(CheckEscKey);

    //Event Test(Compare color matches for specific coordinates in the notepad app)
    Event ev(28, 19, RGB(106, 167, 182), 0,"BLUE");

    //Multi Event Test
    Event mlev1(28, 19, RGB(106, 167, 182), 0, "BLUE");
    Event mlev2(29, 13, RGB(104, 166, 181), 0, "BLUE");
    Event mlev3(28, 20, RGB(118, 184, 199), 0, "BLUE");
    MultiEvent mlev_obj(mlev1, mlev2, mlev3);

    //TemplateMatching (Find the notepad application icon on the desktop)
    TemplateMatching test(IDB_PNG1);

    Logger::info("Main Loop Start");
    while (!(SharedVariable::exit_loop)) {
        if (ev.checkColor()) {
            Logger::info("checkColor OK");
        } else {
            Logger::info("checkColor NG");
        }

        if (ev.checkRGB()) {
            Logger::info("checkRGB OK");
        } else {
            Logger::info("checkRGB NG");
        }

        if (mlev_obj.checkColorMulti(ALL_MATCH,true)) {
            Logger::info("Multi checkColor OK");
        } else {
            Logger::info("Multi checkColor NG");
        }

        if (mlev_obj.checkRGBMulti(ALL_MATCH,true)) {
            Logger::info("Multi checkRGB OK");
        }
        else {
            Logger::info("Multi checkRGB NG");
        }

        if (test.match(cv::Rect(0, 0, 1920, 1080), 0.9)) {
            Logger::info("TemplateMatching is True");
        } else {
            Logger::info("TemplateMatching is False");
        }

        if (test.matchBinary(cv::Rect(0, 0, 1920, 1080), 0.9)) {
            Logger::info("TemplateMatching(Binary) is True");
        } else {
            Logger::info("TemplateMatching(Binary) is False");
        }

        Emulate::sleep(1000);
    }

    WindowInit("無題 - メモ帳");
    Logger::info("Test Emulate Keyboard");

    Emulate::pressKey('T');
    Emulate::sleep(100);
    Emulate::releaseKey('T');

    Emulate::pressKeyDirectX('E');
    Emulate::sleep(100);
    Emulate::releaseKeyDirectX('E');

    Emulate::pressKeyInterCeption('S');
    Emulate::sleep(100);
    Emulate::releaseKeyInterCeption('S');

    Logger::info("Test Emulate Mouse");
    
    Emulate::moveMouse(1, 1);
    Emulate::sleep(1000);
    Emulate::moveMouseInterCeption(100, 100);
    Emulate::sleep(1000);
    for (int i = 0; i <= 10; i++) {
        Emulate::moveMouseRel(5, 5);
        Emulate::sleep(100);
    }
    Emulate::sleep(1000);
    for (int i = 0; i <= 10; i++) {
        Emulate::moveMouseRelInterCeption(-5, -5);
        Emulate::sleep(100);
    }

    Logger::info("Main Loop End");
    if (CheckEscKey_Thread.joinable()) CheckEscKey_Thread.join();

    return 0;
}
