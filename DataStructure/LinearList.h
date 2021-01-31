#pragma once
#include <new>
#include<iostream>
#include "MyException.h"
using namespace std;
template <class T>
//公式化描述的线性表
class LinearList {
public:
	LinearList(int MaxListSize = 10);// 构造函数
	~LinearList() { delete[]element; }//析构函数
	bool IsEmpty()const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T& x)const;//返回第k个元素到x
	int Search(const T& x)const;//返回x所在的位置
	LinearList<T>& Delete(int k, T& x);//删除第k个元素，并放入x
	LinearList<T>& Insert(int k, const T& x);//在第k个元素后面插入x
	void Output(ostream& out) const;
	template <class TT>
	friend ostream& operator<<(ostream& out, const LinearList<TT>& x);

private:
	int length;
	int MaxSize;
	T* element;//一维动态数组
};

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{
	// 基于公式的线性表的构造函数
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
};
template <class T>
bool LinearList<T>::Find(int k, T& x) const
{
	//把第k个元素取至x中
	//如果不存在第k个元素则返回false，否则返回true
	if (k < 1 || k > length) { return false; }//不存在第k个元素
	x = element[k - 1];
	return true;
}
template<class T>
int LinearList<T>::Search(const T& x) const
{
	//查找x，如果找到，则返回x所在的位置
	//如果不在，则返回0
	for (int i = 0; i < length; i++)
	{
		if (element[i] == x)
		{
			return ++i;
		}
	}
	return 0;
}
template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{
	if (Find(k, x)) {
		//把元素k+i依次向前移动一个位置
		for (int i = k; i < length;i++)
		{
			element[i - 1] = element[i];
		}
		length--;
		return *this;
	}
	else { throw OutOfBounds(); }
}
template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
	//若不存在第k个元素，则引发异常OutOfBounds
	//若表已满，引发异常Nomem
	if (k < 0 || k > length) { throw OutOfBounds(); }
	if (length == MaxSize) { throw NoMem(); }
	for (int i = length - 1;i >= k;i--)
	{
		element[i + 1] = element[i];
	}
	element[k] = x;
	length++;
	return *this;
}
template<class T>
void LinearList<T>::Output(ostream& out) const
{
	//把表输送到输出流
	for (int i = 0; i < length;i++)
	{
		out << element[i] << " ";
	}
}
//重载<<
template <class T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
{
	x.Output(out);
	return out;
}