#pragma once
#include<iostream>
#include"MyException.h"
using namespace std;

//��ʽ������
template<class T>
class Queue {
	// FIFO ����
public:
	Queue(int MaxQueueSize = 10);
	~Queue() { delete[] queue; }
	bool IsEmpty() const { return front == rear; }
	bool IsFull() const {
		return (
			((rear + 1) % MaxSize == front) ? 1 : 0);
	}
	T First() const; //���ض���Ԫ��
	T Last() const; // ���ض�βԪ��
	Queue<T>& Add(const T& x);
	Queue<T>& Delete(T& x);
private:
	int front; //���һ��Ԫ���ڷ�ʱ�뷽�������һ��λ��
	int rear; // ָ�����һ��Ԫ��
	int MaxSize; // ��������Ĵ�С
	T* queue; // ����
};

template <class T>
Queue<T>::Queue(int MaxQueueSize)
{// ����һ������ΪMaxQueueSize�Ŀն���
	MaxSize = MaxQueueSize + 1;
	queue = new T[MaxSize];
	front = rear = 0;
}
template<class T>
T Queue<T>::First() const
{// ���ض��еĵ�һ��Ԫ��
// �������Ϊ�գ��������쳣O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return queue[(front + 1) % MaxSize];
}
template<class T>
T Queue<T>::Last() const
{// ���ض��е����һ��Ԫ��
// �������Ϊ�գ��������쳣O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return queue[rear];
}
template<class T>
Queue<T>& Queue<T>::Add(const T& x)
{// ��x ��ӵ����е�β��
// ������������������쳣NoMem
	if (IsFull()) throw NoMem();
	rear = (rear + 1) % MaxSize;
	queue[rear] = x;
	return *this;
}
template<class T>
Queue<T>& Queue<T>::Delete(T& x)
{// ɾ����һ��Ԫ�أ�����������x
// �������Ϊ�գ��������쳣O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	front = (front + 1) % MaxSize;
	x = queue[front];
	return *this;
}

template<class T>
class LinkedQueue {
	// FIFO����
public:
	LinkedQueue() { front = rear = 0; } // ���캯��
	~LinkedQueue(); // ��������
	bool IsEmpty() const
	{
		return ((front) ? false : true);
	}
	bool IsFull() const;
	T First() const; // ���ص�һ��Ԫ��
	T Last() const; // �������һ��Ԫ��
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
private:
	Node<T>* front; // ָ���һ���ڵ�
	Node<T>* rear; //ָ�����һ���ڵ�
};
template<class T>
LinkedQueue<T>:: ~LinkedQueue()
{// ��������������ɾ�����нڵ�
	Node<T>* next;
	while (front) {
		next = front->link;
		delete front;
		front = next;
	}
}
template<class T>
bool LinkedQueue<T>::IsFull() const
{// �ж϶����Ƿ�����
	Node<T>* p;
	try {
		p = new Node<T>;
		delete p;
		return false;
	}
	catch (NoMem) { return true; }
}
template<class T>
T LinkedQueue<T>::First() const
{// ���ض��еĵ�һ��Ԫ��
// �������Ϊ�գ��������쳣O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return front->data;
}
template<class T>
T LinkedQueue<T>::Last() const
{// ���ض��е����һ��Ԫ��
// �������Ϊ�գ��������쳣O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return rear->data;
}
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{// ��x ��ӵ����е�β��
// �����������n e w������NoMem �쳣
// Ϊ��Ԫ�ش�������ڵ�
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = 0;
	// �ڶ���β������½ڵ�
	if (front) rear->link = p; //���в�Ϊ��
	else front = p; // ����Ϊ��
	rear = p;
	return *this;
}
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{// ɾ����һ��Ԫ�أ����������x
   // �������Ϊ�գ��������쳣O u t O f B o u n d s
		if (IsEmpty()) throw OutOfBounds();
		//�����һ���ڵ��е�Ԫ��
			x = front->data;
		// ɾ����һ���ڵ�
		Node<T>* p = front;
		front = front->link;
		delete p;
		return *this;
}