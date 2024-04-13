#pragma once

struct intVector2 {
	int x, y;
	intVector2(int x, int y) : x(x), y(y) {}
};

struct intVector3 {
	int x, y, z;
	intVector3(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct rgbTuple {
	int r, g, b;
	rgbTuple(int r, int g, int b) : r(r), g(g), b(b) {}
};