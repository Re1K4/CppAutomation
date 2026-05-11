# Name 
CppAutomation

## Overview
C++ template for GUI automation with OpenCV library. 
It is very fast and can automate most operations.

## Usage
This is a template, and the process must be written and built in the while loop in main.cpp according to the process you wish to automate.
The initial main.cpp contains test code for each function.

### Definition and method calls

#### Logger
```cpp
Logger::initialize("", true);
Logger::info("message");
Logger::warning("message");
Logger::error("message");
```
- `initialize(filename, consoleOutput)` initializes log output destination and console output settings.
- `info / warning / error` writes logs at each level.

#### Timer
```cpp
Timer tm;
tm.set();
double elapsed = tm.distance();
tm.reset();
```
- Create an instance and call `set()` to start measurement.
- `distance()` returns elapsed time.
- `reset()` resets the internal state.

#### Control
```cpp
Control control;
int current = control.NOW;
int previous = control.PREV;
control.changeCtrl(10);
```
- `NOW` and `PREV` store current/previous control numbers.
- Use `changeCtrl()` to update control state.

#### Event
```cpp
Event ev(28, 19, RGB(106, 167, 182), 0, "BLUE");
bool colorMatched = ev.checkColor();
bool rgbMatched = ev.checkRGB();
```
- Define with `(x, y, color, fazzy, colorType)`.
- `checkColor()` checks exact-like color matching with `fazzy` tolerance.
- `checkRGB()` checks by RGB category (`"RED"`, `"GREEN"`, `"BLUE"`).

#### MultiEvent
```cpp
Event ev1(28, 19, RGB(106, 167, 182), 0, "BLUE");
Event ev2(29, 13, RGB(104, 166, 181), 0, "BLUE");
Event ev3(28, 20, RGB(118, 184, 199), 0, "BLUE");

MultiEvent mev(ev1, ev2, ev3);
bool allColor = mev.checkColorMulti(ALL_MATCH, true);
bool anyRgb = mev.checkRGBMulti(ANY_MATCH, false);
```
- Pass two or more `Event` objects to the constructor.
- `checkColorMulti(mode, debugFlag)` and `checkRGBMulti(mode, debugFlag)` support:
  - `ALL_MATCH`: all events must match
  - `ANY_MATCH`: at least one event must match

#### TemplateMatching
```cpp
TemplateMatching tm("asset/images/notepad_icon.png");
bool found = tm.match(cv::Rect(0, 0, 1920, 1080), 0.9);
bool foundBinary = tm.matchBinary(cv::Rect(0, 0, 1920, 1080), 0.9);
```
- Create with template image path.
- `match(region, fuzzy)` performs normal template matching.
- `matchBinary(region, fuzzy)` performs binary-image-based matching.
- Last result rectangle is stored in `lastMatchResult`.

### How to call `WindowInit`
```cpp
WindowInit("notepad.exe");
```
- Pass the target application executable name as `const char*`.
- Run this before event checks or mouse/keyboard automation so shared window information is initialized.

## Author
[![Twitter: ReekerZrZr](https://img.shields.io/twitter/follow/ReekerZrZr?style=social)](https://x.com/ReekerZrZr)
