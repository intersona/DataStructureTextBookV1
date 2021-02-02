#pragma once
#include "LinearList.h"
//��ʽ������

//�̳������Ա�
template <class T>
class DerivedStack :private LinearList<T>
{
public:
	DerivedStack(int MaxStackSize = 10) :LinearList<T>(MaxStackSize) {}
	bool IsEmpty() const
	{
		return LinearList<T>::IsEmpty();
	}
	bool IsFull() const
	{
		return (LinearList<T>::Length() == LinearList<T>::GetMaxSize());
	}
	T Top() const
	{
		if (IsEmpty()) { throw OutOfBounds(); }
		T x;
		Find(LinearList<T>::Length(), x);
		return x;
	}
	DerivedStack<T>& Add(const T& x)
	{
		LinearList<T>::Insert(LinearList<T>::Length(), x); return *this;
	}
	DerivedStack<T>& Delete(T& x)
	{
		LinearList<T>::Delete(LinearList<T>::Length(), x);
		return *this;
	}
};

//�Զ���stack��
template<class T>
class Stack {
	// LIFO ����
public:
	Stack(int MaxStackSize = 10);
	~Stack() { delete[] stack; }
	bool IsEmpty() const { return top == -1; }
	bool IsFull() const { return top == MaxTop; }
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Delete(T& x);
private:
	int top; // ջ��
	int MaxTop; // ����ջ��ֵ
	T* stack; // ��ջԪ������
};
template<class T>
Stack<T>::Stack(int MaxStackSize)
{// Stack �๹�캯��
	MaxTop = MaxStackSize - 1;
	stack = new T[MaxStackSize];
	top = -1;
}
template<class T>
T Stack<T>::Top() const
{// ����ջ��Ԫ��
	if (IsEmpty()) throw OutOfBounds();
	else return stack[top];
}
template<class T>
Stack<T>& Stack<T>::Add(const T& x)
{
	//���Ԫ��x
	if (IsFull()) throw NoMem();
	stack[++top] = x;
	return *this;
}
template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{// ɾ��ջ��Ԫ�أ�����������x
	if (IsEmpty()) throw OutOfBounds();
	x = stack[top--];
	return *this;
}