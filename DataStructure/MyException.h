#pragma once
#include <new>
#include <iostream>
#include <exception>
using namespace std;
// �ڴ治��
class NoMem {
public:
	NoMem() {}
};

//Խ��
class OutOfBounds :exception {
public:
	OutOfBounds() { cout << "Out Of Bounds" << endl; }
};

class BadInitializers :exception {
public:
	BadInitializers() { cout << "BadInitializers" << endl; }
};