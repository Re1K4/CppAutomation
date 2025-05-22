#pragma once
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "SharedVariable.h"
#include "interception.h"

class Emulate {
public:
	static void pressKey(WORD key);
	static void releaseKey(WORD key);
	static void pressKeyDirectX(WORD key);
	static void releaseKeyDirectX(WORD key);
	static void pressKeyInterCeption(WORD vk);
	static void releaseKeyInterCeption(WORD vk);
	static void moveMouse(int x, int y);
	static void moveMouseRel(int dx, int dy);
	static void moveMouseInterCeption(int x, int y);
	static void moveMouseRelInterCeption(int dx, int dy);
	static void sleep(int ms);
	static void pressMouseLeft();
	static void releaseMouseLeft();
	static void pressMouseLeftInterception();
	static void releaseMouseLeftInterception();
	static void pressMouseRight();
	static void releaseMouseRight();
	static void pressMouseRightInterception();
	static void releaseMouseRightInterception();

private:
	Emulate() = delete;
};

