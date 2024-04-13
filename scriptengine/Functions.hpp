#pragma once
#include <Windows.h>
#include <chrono>
#include <thread>
#include <chaiscript/chaiscript.hpp>
#include "Structs.hpp";

chaiscript::ChaiScript chai;

void nc_ThreadSleep(long t) {
	std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

intVector2 nc_GetCursorPos() {
	POINT pos;
	GetCursorPos(&pos);
	return intVector2(pos.x, pos.y);
}

COLORREF nc_GetPixel(int x, int y) {
	HDC screenDC = GetDC(NULL);
	COLORREF pixelColor = GetPixel(screenDC, x, y);
	return pixelColor;
}

COLORREF nc_Color(int r, int g, int b) {
	return RGB(r, g, b);
}

rgbTuple nc_ColorToRGB(COLORREF color) {
	return rgbTuple(GetRValue(color), GetGValue(color), GetBValue(color));
}