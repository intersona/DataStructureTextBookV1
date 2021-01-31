#pragma once
#include <new>
#include <iostream>
#include <exception>
using namespace std;
// 内存不足
class NoMem {
public:
	NoMem() {}
};

//越界
class OutOfBounds :exception {
public:
	OutOfBounds() { cout << "Out Of Bounds" << endl; }
};

class BadInitializers :exception {
public:
	BadInitializers() { cout << "BadInitializers" << endl; }
};