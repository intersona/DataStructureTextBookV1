#pragma once
#include"MyException.h"
template <class T>
class Array1D {
public:
	Array1D(int size = 0);
	Array1D(const Array1D<T>& v);//复制构造函数
	~Array1D() { delete[]element; }
	T& operator[](int i) const;
	int Size() { return size; }
	Array1D<T>& operator=(const Array1D<T>& v);
	Array1D<T> operator+() const; // 一元加法操作符
	Array1D<T> operator+(const Array1D<T>& v) const;
	Array1D<T> operator-() const; // 一元减法操作符
	Array1D<T> operator-(const Array1D<T>& v) const;
	Array1D<T> operator*(const Array1D<T>& v) const;
	Array1D<T>& operator+=(const T& x);
private:
	int size;
	T* element;
};

//一维数组的构造函数
template <class T>
Array1D<T>::Array1D(int sz)
{
	if (sz < 0) { throw OutOfBounds(); }
	size = sz;
	element = new T[sz];
}

//一维数组的复制构造函数
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

//重载下标操作符[]
template<class T>
T& Array1D<T>::operator[](int i) const
{// 返回指向第i个元素的引用
	if (i < 0 || i >= size) throw OutOfBounds();
	return element[i];
}

//重载赋值操作符=
template<class T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T>& v)
{// 重载赋值操作符=
	if (this != &v) {// 不是自我赋值
		size = v.s i z e;
		delete[] element; // 释放原空间
		element = new T[size]; // 申请空间
		for (int i = 0; i < size; i++) //复制元素
			element[i] = v.element[i];
	}
	return *this;
}

//重载二元减法操作符
template<class T>
Array1D<T> Array1D<T>:: operator-(const Array1D<T>& v) const
{// 返回w = (*this) - v
	if (size != v.size) throw SizeMismatch();
	// 创建结果数组w
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] - v.element[i];
	return w;
}
//重载一元减法操作符
template<class T>
Array1D<T> Array1D<T>::operator-() const
{// 返回w = -(*this)
// 创建结果数组w
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = -element[i];
	return w;
}
//重载增值操作符
template<class T>
Array1D<T>& Array1D<T>::operator+=(const T& x)
{
	/ /把x 加到(*this)的每个元素上
		for (int i = 0; i < size; i++)
		{
			element[i] += x;
		}
	return *this;
}

//二维数组的类定义
template<class T>
class Array2D {
public:
	Array2D(int r = 0, int c = 0);
	Array2D(const Array2D<T>& m); // 复制构造函数
	~Array2D() { delete[] row; }
	int Rows() const { return rows; }
	int Columns() const { return cols; }
	Array1D<T>& operator[](int i) const;
	Array2D<T>& operator=(const Array2D<T>& m);
	Array2D<T> operator+() const; // 一元加法操作符
	Array2D<T> operator+(const Array2D<T>& m) const;
	Array2D<T> operator-() const; // 一元减法操作符
	Array2D<T> operator-(const Array2D<T>& m) const;
	Array2D<T> operator*(const Array2D<T>& m) const;
	Array2D<T>& operator+=(const T& x);
private:
	int rows, cols; // 数组维数
	Array1D<T>* row; // 一维数组的数组
};

//二维数组的构造函数
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
	// 分配r个具有缺省大小的一维数组
	row = new Array1D<T>[r];
	// 调整每个元素的大小
	for (int i = 0; i < r; i++)
	{
		row[i].ReSize(c);
	}
}

//二维数组的复制构造函数
template<class T>
Array2D<T>::Array2D(const Array2D<T>& m)
{// 二维数组的复制构造函数
	rows = m.rows;
	cols = m.cols;
	// 分配指向一维数组的数组
	row = new Array1D<T>[rows];
	// 复制每一行
	for (int i = 0; i < rows; i++)
		row[i] = m.row[i];
}

//二维数组的重载操作符[]
template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const
{
	//二维数组的第一个索引
	if (i < 0 || i >= rows) { throw OutOfBounds(); }
	return row[i];
}

//二元减法操作符
template<class T>
Array2D<T> Array2D<T>:: operator-(const Array2D<T>& m) const
{// 返回w = (*this) - m.
	if (rows != m.rows || cols != m.cols)
	{
		cout << "SizeMismatch" << endl;
	}
	// 创建存放结果的数组w
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i] - m.row[i];
	return w;
}