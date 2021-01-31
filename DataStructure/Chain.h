#pragma once
#include<iostream>
#include"LinearList.h"
using namespace std;

template <class T>
class Chain;

//���Ա����������
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
	ChainNode<T>* first;//ָ���һ���ڵ��ָ��
	ChainNode<T>* last;//ָ�����һ���ڵ�
};
template <class T>
Chain<T>::~Chain()
{
	//�������������������ɾ�������е����нڵ�
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
	//���������е�Ԫ�ظ�������������
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
{// Ѱ�������еĵ�k��Ԫ�أ������䴫����x
 //��������ڵ�k��Ԫ�أ��򷵻�false�����򷵻�true
	if (k < 1) { return false; }
	ChainNode<T>* current = first;
	int index = 1; // current������
	while (index < k && current) {
		current = current->link;
		index++;
	}
	if (current) { x = current->data; return true; }
	return false; // �����ڵ�k��Ԫ��
}

template <class T>
int Chain<T>::Search(const T& x) const
{
	//Ѱ��x���������x���򷵻�x�ĵ�ַ
	//���򷵻�0
	ChainNode<T>* current = first;
	int index = 1;//current������
	while (current && current->data != x) {
		current = current->link;
		index++;
	}
	if (current) { return index; }
	return 0;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{//������Ԫ�����������
	ChainNode<T>* current;
	for (current = first;current;current = current->link)
	{
		out << current->data << " ";
	}
}

//����<<
template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.Output(out);
	return out;
}

//��������ɾ��һ��Ԫ��
template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{//�ѵ�k��Ԫ��ȡ��x��Ȼ���������ɾ����k��Ԫ��
//��������ڣ��׳��쳣
	if (k < 1 || !first) { throw OutOfBounds(); }//�����ڵ�k��Ԫ��
	//p����ָ���k��Ԫ��
	ChainNode<T>* p = first;
	// ��p�ƶ�����k��Ԫ�أ�����������ɾ����Ԫ��
	if (k == 1)//p�Ѿ�ָ���˵�k��Ԫ��
	{
		first = first->link;
	}
	else {//qָ���k-1��Ԫ��
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
	//�����k��Ԫ�ز��ͷŽڵ�p
	x = p->data;
	delete p;
	return *this;
}

//�������в���Ԫ��
template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{// �ڵ�k��Ԫ��֮�����x
//��������ڵ�k��Ԫ�أ��������쳣O u t O f B o u n d s
// ���û���㹻�Ŀռ䣬�򴫵�N o M e m�쳣
	if (k < 0) { throw OutOfBounds(); }
	//p����ָ���k���ڵ�
	ChainNode<T>* p = first;
	for (int index = 1;index < k && p;index++)
	{
		p = p->link;
	}
	if (k > 0 && !p)
	{
		throw OutOfBounds();
	}
	//����
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

//ɾ�����������нڵ�
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

//�������Ҷ����һ��Ԫ��
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

//���������
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