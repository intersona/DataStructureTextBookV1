#pragma once
#include <new>
using namespace std;
template <class T>
class LinearList {
public:
	LinearList(int MaxListSize = 10);// 构造函数
	~LinearList() { delete[]element; }
	bool IsEmpty()const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T& x)const;
	int Search(const T& x)const;

private:
	int length;
	int MaxSize;
	T* element;
};

// 内存不足
class NoMem {
public:
	NoMem() {}
};
// 使new引发NoMem异常而不是xalloc异常
void my_new_handler()
{
	throw NoMem();
};
new_handler Old_Handler_ = set_new_handler(my_new_handler);

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{
	// 基于公式的线性表的构造函数
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
};
template <class T>
bool LinearList<T>::LinearList(int MaxListSize)
{
	//把第k个元素取至x中
	//如果不存在第k个元素则返回false，否则返回true
	if (k < 1 || k > length) { return false; }//不存在第k个元素
}