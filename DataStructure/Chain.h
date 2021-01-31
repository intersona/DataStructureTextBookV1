#pragma once
#include<iostream>
#include"LinearList.h"
using namespace std;

template <class T>
class Chain;

//线性表的链表描述
template <class T>
class ChainNode {
	friend Chain<T>;
private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain {
public:
	Chain() { first = 0; }
	~Chain();
	bool IsEmpty()const { return first == 0; }
	int Length()const;
	bool Find(int k, T& x)const;
	int Search(const T& x)const;
	Chain<T>& Delete(int k, T& x);
	Chain<T>& Insert(int k, const T& x);
	void Output(ostream& out)const;
	template<class TT>
	friend ostream& operator<<(ostream& out, const Chain<TT>& x);

	void Erase();
	inline void Zero() { first = 0; }
	Chain<T>& Append(const T& x);
private:
	ChainNode<T>* first;//指向第一个节点的指针
	ChainNode<T>* last;//指向最后一个节点
};
template <class T>
Chain<T>::~Chain()
{
	//链表的析构函数，用于删除链表中的所有节点
	ChainNode<T>* next;
	while (first) {
		next = first->link;
		delete first;
		first = next;
	}
}

template <class T>
int Chain<T>::Length() const
{
	//返回链表中的元素个数，即链表长度
	ChainNode<T>* current = first;
	int len = 0;
	while (current) {
		len++;
		current = current->link;
	}
	return len;
}

template<class T>
bool Chain<T>::Find(int k, T& x) const
{// 寻找链表中的第k个元素，并将其传送至x
 //如果不存在第k个元素，则返回false，否则返回true
	if (k < 1) { return false; }
	ChainNode<T>* current = first;
	int index = 1; // current的索引
	while (index < k && current) {
		current = current->link;
		index++;
	}
	if (current) { x = current->data; return true; }
	return false; // 不存在第k个元素
}

template <class T>
int Chain<T>::Search(const T& x) const
{
	//寻找x，如果发现x，则返回x的地址
	//否则返回0
	ChainNode<T>* current = first;
	int index = 1;//current的索引
	while (current && current->data != x) {
		current = current->link;
		index++;
	}
	if (current) { return index; }
	return 0;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{//将链表元素送至输出流
	ChainNode<T>* current;
	for (current = first;current;current = current->link)
	{
		out << current->data << " ";
	}
}

//重载<<
template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.Output(out);
	return out;
}

//从链表中删除一个元素
template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{//把第k个元素取到x，然后从链表中删除第k个元素
//如果不存在，抛出异常
	if (k < 1 || !first) { throw OutOfBounds(); }//不存在第k个元素
	//p最终指向第k个元素
	ChainNode<T>* p = first;
	// 将p移动到第k个元素，并从链表中删除该元素
	if (k == 1)//p已经指向了第k个元素
	{
		first = first->link;
	}
	else {//q指向第k-1个元素
		ChainNode<T>* q = first;
		for (int index = 1;index < k - 1 && q;index++)
		{
			q = q->link;
		}
		if (!q || !q->link)
		{
			throw OutOfBounds();
		}
		p = q->link;
		if (p == last) {
			last = q;
		}
		q->link = p->link;
	}
	//保存第k个元素并释放节点p
	x = p->data;
	delete p;
	return *this;
}

//向链表中插入元素
template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{// 在第k个元素之后插入x
//如果不存在第k个元素，则引发异常O u t O f B o u n d s
// 如果没有足够的空间，则传递N o M e m异常
	if (k < 0) { throw OutOfBounds(); }
	//p最终指向第k个节点
	ChainNode<T>* p = first;
	for (int index = 1;index < k && p;index++)
	{
		p = p->link;
	}
	if (k > 0 && !p)
	{
		throw OutOfBounds();
	}
	//插入
	ChainNode<T>* y = new ChainNode<T>;
	y->data = x;
	if (k)
	{
		y->link = p->link;
		p->link = y;
	}
	else {
		y->link = first;
		first = y;
	}
	if (!y->link) { last = y; }
	return *this;
}

//删除链表中所有节点
template<class T>
void Chain<T>::Erase()
{
	ChainNode<T>* next;
	while (first)
	{
		next = first->link;
		delete first;
		first = next;
	}
}

//在链表右端添加一个元素
template <class T>
Chain<T>& Chain<T>::Append(const T& x)
{
	ChainNode<T>* y;
	y = new ChainNode<T>;
	y->data = x;
	y->link = 0;
	if (first) {
		last->link = y;
		last = y;
	}
	else {
		first = last = y;
	}
	return *this;
}

//链表遍历器
template <class T>
class ChainIterator {
private:
	ChainNode<T>* location;
public:
	T* Initialize(const Chain<T>& c)
	{
		location = c.first;
		if (location)
		{
			return &location->data;
		}
		return 0;
	}
	T* Next()
	{
		if (!location)
		{
			return 0;
		}
		location = location->link;
		if (location)
		{
			return &location->data;
		}
		return 0;
	}
};