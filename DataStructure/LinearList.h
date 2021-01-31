#pragma once
#include <new>
#include<iostream>
#include "MyException.h"
using namespace std;
template <class T>
//��ʽ�����������Ա�
class LinearList {
public:
	LinearList(int MaxListSize = 10);// ���캯��
	~LinearList() { delete[]element; }//��������
	bool IsEmpty()const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T& x)const;//���ص�k��Ԫ�ص�x
	int Search(const T& x)const;//����x���ڵ�λ��
	LinearList<T>& Delete(int k, T& x);//ɾ����k��Ԫ�أ�������x
	LinearList<T>& Insert(int k, const T& x);//�ڵ�k��Ԫ�غ������x
	void Output(ostream& out) const;
	template <class TT>
	friend ostream& operator<<(ostream& out, const LinearList<TT>& x);

private:
	int length;
	int MaxSize;
	T* element;//һά��̬����
};

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{
	// ���ڹ�ʽ�����Ա�Ĺ��캯��
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
};
template <class T>
bool LinearList<T>::Find(int k, T& x) const
{
	//�ѵ�k��Ԫ��ȡ��x��
	//��������ڵ�k��Ԫ���򷵻�false�����򷵻�true
	if (k < 1 || k > length) { return false; }//�����ڵ�k��Ԫ��
	x = element[k - 1];
	return true;
}
template<class T>
int LinearList<T>::Search(const T& x) const
{
	//����x������ҵ����򷵻�x���ڵ�λ��
	//������ڣ��򷵻�0
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
		//��Ԫ��k+i������ǰ�ƶ�һ��λ��
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
	//�������ڵ�k��Ԫ�أ��������쳣OutOfBounds
	//���������������쳣Nomem
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
	//�ѱ����͵������
	for (int i = 0; i < length;i++)
	{
		out << element[i] << " ";
	}
}
//����<<
template <class T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
{
	x.Output(out);
	return out;
}