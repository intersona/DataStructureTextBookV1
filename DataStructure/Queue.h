#pragma once
#include<iostream>
#include"MyException.h"
using namespace std;

//公式化描述
template<class T>
class Queue {
	// FIFO 对象
public:
	Queue(int MaxQueueSize = 10);
	~Queue() { delete[] queue; }
	bool IsEmpty() const { return front == rear; }
	bool IsFull() const {
		return (
			((rear + 1) % MaxSize == front) ? 1 : 0);
	}
	T First() const; //返回队首元素
	T Last() const; // 返回队尾元素
	Queue<T>& Add(const T& x);
	Queue<T>& Delete(T& x);
private:
	int front; //与第一个元素在反时针方向上相差一个位置
	int rear; // 指向最后一个元素
	int MaxSize; // 队列数组的大小
	T* queue; // 数组
};

template <class T>
Queue<T>::Queue(int MaxQueueSize)
{// 创建一个容量为MaxQueueSize的空队列
	MaxSize = MaxQueueSize + 1;
	queue = new T[MaxSize];
	front = rear = 0;
}
template<class T>
T Queue<T>::First() const
{// 返回队列的第一个元素
// 如果队列为空，则引发异常O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return queue[(front + 1) % MaxSize];
}
template<class T>
T Queue<T>::Last() const
{// 返回队列的最后一个元素
// 如果队列为空，则引发异常O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return queue[rear];
}
template<class T>
Queue<T>& Queue<T>::Add(const T& x)
{// 把x 添加到队列的尾部
// 如果队列满，则引发异常NoMem
	if (IsFull()) throw NoMem();
	rear = (rear + 1) % MaxSize;
	queue[rear] = x;
	return *this;
}
template<class T>
Queue<T>& Queue<T>::Delete(T& x)
{// 删除第一个元素，并将其送入x
// 如果队列为空，则引发异常O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	front = (front + 1) % MaxSize;
	x = queue[front];
	return *this;
}

template<class T>
class LinkedQueue {
	// FIFO对象
public:
	LinkedQueue() { front = rear = 0; } // 构造函数
	~LinkedQueue(); // 析构函数
	bool IsEmpty() const
	{
		return ((front) ? false : true);
	}
	bool IsFull() const;
	T First() const; // 返回第一个元素
	T Last() const; // 返回最后一个元素
	LinkedQueue<T>& Add(const T& x);
	LinkedQueue<T>& Delete(T& x);
private:
	Node<T>* front; // 指向第一个节点
	Node<T>* rear; //指向最后一个节点
};
template<class T>
LinkedQueue<T>:: ~LinkedQueue()
{// 队列析构函数，删除所有节点
	Node<T>* next;
	while (front) {
		next = front->link;
		delete front;
		front = next;
	}
}
template<class T>
bool LinkedQueue<T>::IsFull() const
{// 判断队列是否已满
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
{// 返回队列的第一个元素
// 如果队列为空，则引发异常O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return front->data;
}
template<class T>
T LinkedQueue<T>::Last() const
{// 返回队列的最后一个元素
// 如果队列为空，则引发异常O u t O f B o u n d s
	if (IsEmpty()) throw OutOfBounds();
	return rear->data;
}
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Add(const T& x)
{// 把x 添加到队列的尾部
// 不捕获可能由n e w引发的NoMem 异常
// 为新元素创建链表节点
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = 0;
	// 在队列尾部添加新节点
	if (front) rear->link = p; //队列不为空
	else front = p; // 队列为空
	rear = p;
	return *this;
}
template<class T>
LinkedQueue<T>& LinkedQueue<T>::Delete(T& x)
{// 删除第一个元素，并将其放入x
   // 如果队列为空，则引发异常O u t O f B o u n d s
		if (IsEmpty()) throw OutOfBounds();
		//保存第一个节点中的元素
			x = front->data;
		// 删除第一个节点
		Node<T>* p = front;
		front = front->link;
		delete p;
		return *this;
}