#pragma once
#include <new>
using namespace std;
template <class T>
class LinearList {
public:
	LinearList(int MaxListSize = 10);// ���캯��
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

// �ڴ治��
class NoMem {
public:
	NoMem() {}
};
// ʹnew����NoMem�쳣������xalloc�쳣
void my_new_handler()
{
	throw NoMem();
};
new_handler Old_Handler_ = set_new_handler(my_new_handler);

template<class T>
LinearList<T>::LinearList(int MaxListSize)
{
	// ���ڹ�ʽ�����Ա�Ĺ��캯��
	MaxSize = MaxListSize;
	element = new T[MaxSize];
	length = 0;
};
template <class T>
bool LinearList<T>::LinearList(int MaxListSize)
{
	//�ѵ�k��Ԫ��ȡ��x��
	//��������ڵ�k��Ԫ���򷵻�false�����򷵻�true
	if (k < 1 || k > length) { return false; }//�����ڵ�k��Ԫ��
}