#pragma once
#include "Chain.h"
using namespace std;

template<class T>
class DerivedLinkedStack :
    private Chain<T>
{
public:
    bool IsEmpty() const { return Chain<T>::IsEmpty(); }
    bool IsFull() const;
    T Top()const
    {
        if (IsEmpty())
        {
            throw OutOfBounds();
        }
        T x;
        Find(1, x);
        return x;
    }
    DerivedLinkedStack<T>& Add(const T& x)
    {
        Chain<T>::Insert(0, x); return *this;
    }
    DerivedLinkedStack<T>& Delete(T& x)
    {
        Chain<T>::Delete(1, x); return *this;
    }
};

template<class T>
bool DerivedLinkedStack<T>::IsFull() const
{// ��ջ�Ƿ���?
    try {
        ChainNode<T>* p = new ChainNode<T>;
        delete p; return false;
    }
    catch (NoMem) { return true; }
}

template<class T>
class LinkedStack;
//�Զ���������ʽ�Ķ�ջ
template <class T>
class Node {
    friend LinkedStack<T>;
private:
    T data;
    Node<T>* link;
};

template<class T>
class LinkedStack {
public:
    LinkedStack() { top = 0; }
    ~LinkedStack();
    bool IsEmpty() const { return top == 0; }
    bool IsFull() const;
    T Top() const;
    LinkedStack<T>& Add(const T& x);
    LinkedStack<T>& Delete(T& x);
private:
    Node<T>* top; // ָ��ջ���ڵ�
};

template<class T>
LinkedStack<T>::~LinkedStack()
{
    Node<T>* next;
    while (top) {
        next = top->link;
        delete top;
        top = next;
    }
}
template<class T>
bool LinkedStack<T>::IsFull() const
{
    try {
        Node<T>* p = new Node<T>;
        delete p;
        return false;
    }
    catch (NoMem) {
        return true;
    }
}
template<class T>
T LinkedStack<T>::Top() const
{// ����ջ��Ԫ��
    if (IsEmpty()) throw OutOfBounds();
    return top->data;
}
template<class T>
LinkedStack<T>& LinkedStack<T>::Add(const T& x)
{// ���Ԫ��x
    Node<T>* p = new Node<T>;
    p->data = x;
    p->link = top;
    top = p;
    return *this;
}
template<class T>
LinkedStack<T>& LinkedStack<T>::Delete(T& x)
{// ɾ��ջ��Ԫ�أ�����������x
    if (IsEmpty()) throw OutOfBounds();
    x = top->data;
    Node<T>* p = top;
    top = top->link;
    delete p;
    return *this;
}