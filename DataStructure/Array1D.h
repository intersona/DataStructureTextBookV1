#pragma once
#include"MyException.h"
template <class T>
class Array1D {
public:
	Array1D(int size = 0);
	Array1D(const Array1D<T>& v);//���ƹ��캯��
	~Array1D() { delete[]element; }
	T& operator[](int i) const;
	int Size() { return size; }
	Array1D<T>& operator=(const Array1D<T>& v);
	Array1D<T> operator+() const; // һԪ�ӷ�������
	Array1D<T> operator+(const Array1D<T>& v) const;
	Array1D<T> operator-() const; // һԪ����������
	Array1D<T> operator-(const Array1D<T>& v) const;
	Array1D<T> operator*(const Array1D<T>& v) const;
	Array1D<T>& operator+=(const T& x);
private:
	int size;
	T* element;
};

//һά����Ĺ��캯��
template <class T>
Array1D<T>::Array1D(int sz)
{
	if (sz < 0) { throw OutOfBounds(); }
	size = sz;
	element = new T[sz];
}

//һά����ĸ��ƹ��캯��
template<class T>
Array1D<T>::Array1D(const Array1D<T>& v)
{
	size = v.size;
	element = new T[size];
	for (int i = 0;i < size;i++)
	{
		element[i] = v.element[i];
	}
}

//�����±������[]
template<class T>
T& Array1D<T>::operator[](int i) const
{// ����ָ���i��Ԫ�ص�����
	if (i < 0 || i >= size) throw OutOfBounds();
	return element[i];
}

//���ظ�ֵ������=
template<class T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T>& v)
{// ���ظ�ֵ������=
	if (this != &v) {// �������Ҹ�ֵ
		size = v.s i z e;
		delete[] element; // �ͷ�ԭ�ռ�
		element = new T[size]; // ����ռ�
		for (int i = 0; i < size; i++) //����Ԫ��
			element[i] = v.element[i];
	}
	return *this;
}

//���ض�Ԫ����������
template<class T>
Array1D<T> Array1D<T>:: operator-(const Array1D<T>& v) const
{// ����w = (*this) - v
	if (size != v.size) throw SizeMismatch();
	// �����������w
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] - v.element[i];
	return w;
}
//����һԪ����������
template<class T>
Array1D<T> Array1D<T>::operator-() const
{// ����w = -(*this)
// �����������w
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = -element[i];
	return w;
}
//������ֵ������
template<class T>
Array1D<T>& Array1D<T>::operator+=(const T& x)
{
	/ /��x �ӵ�(*this)��ÿ��Ԫ����
		for (int i = 0; i < size; i++)
		{
			element[i] += x;
		}
	return *this;
}

//��ά������ඨ��
template<class T>
class Array2D {
public:
	Array2D(int r = 0, int c = 0);
	Array2D(const Array2D<T>& m); // ���ƹ��캯��
	~Array2D() { delete[] row; }
	int Rows() const { return rows; }
	int Columns() const { return cols; }
	Array1D<T>& operator[](int i) const;
	Array2D<T>& operator=(const Array2D<T>& m);
	Array2D<T> operator+() const; // һԪ�ӷ�������
	Array2D<T> operator+(const Array2D<T>& m) const;
	Array2D<T> operator-() const; // һԪ����������
	Array2D<T> operator-(const Array2D<T>& m) const;
	Array2D<T> operator*(const Array2D<T>& m) const;
	Array2D<T>& operator+=(const T& x);
private:
	int rows, cols; // ����ά��
	Array1D<T>* row; // һά���������
};

//��ά����Ĺ��캯��
template<class T>
Array2D<T>::Array2D(int r, int c)
{
	if (r < 0 || c < 0) { throw BadInitializers(); }
	if ((!r || !c) && (r || c))
	{
		throw BadInitializers();
	}
	rows = r;
	cols = c;
	// ����r������ȱʡ��С��һά����
	row = new Array1D<T>[r];
	// ����ÿ��Ԫ�صĴ�С
	for (int i = 0; i < r; i++)
	{
		row[i].ReSize(c);
	}
}

//��ά����ĸ��ƹ��캯��
template<class T>
Array2D<T>::Array2D(const Array2D<T>& m)
{// ��ά����ĸ��ƹ��캯��
	rows = m.rows;
	cols = m.cols;
	// ����ָ��һά���������
	row = new Array1D<T>[rows];
	// ����ÿһ��
	for (int i = 0; i < rows; i++)
		row[i] = m.row[i];
}

//��ά��������ز�����[]
template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const
{
	//��ά����ĵ�һ������
	if (i < 0 || i >= rows) { throw OutOfBounds(); }
	return row[i];
}

//��Ԫ����������
template<class T>
Array2D<T> Array2D<T>:: operator-(const Array2D<T>& m) const
{// ����w = (*this) - m.
	if (rows != m.rows || cols != m.cols)
	{
		cout << "SizeMismatch" << endl;
	}
	// ������Ž��������w
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i] - m.row[i];
	return w;
}