#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "SharedVariable.h"

class Emulate {
public:
	static void pressKey(WORD key);
	static void releaseKey(WORD key);
	static void moveMouse(int x, int y);
	static void moveMouseRel(int dx, int dy);
	static void sleep(int ms);
	static void pressMouseLeft();
	static void releaseMouseLeft();
	static void pressMouseRight();
	static void releaseMouseRight();

private:
	Emulate() = delete;
};

