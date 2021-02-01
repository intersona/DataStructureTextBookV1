#pragma once
#include <iostream>
#include"MyException.h"
using namespace std;

template<class T>
class Matrix {
public:
	Matrix(int r = 0, int c = 0);
	Matrix(const Matrix<T>& m); //复制构造函数
	~Matrix() { delete[] element; }
	int Rows() const { return rows; }
	int Columns() const { return cols; }
	T& operator()(int i, int j) const;
	Matrix<T>& operator=(const Matrix<T>& m);
	Matrix<T> operator+() const; // 一元加法
	Matrix<T> operator+(const Matrix<T>& m) const;
	Matrix<T> operator-() const; // 一元减法
	Matrix<T> operator-(const Matrix<T>& m) const;
	Matrix<T> operator*(const Matrix<T>& m) const;
	Matrix<T>& operator+=(const T& x);
private:
	int rows, cols; // 矩阵维数
	T* element; // 元素数组
};

//类Maxtrix的构造函数
template<class T>
Matrix<T>::Matrix(int r, int c)
{// 类M a t r i x的构造函数
// 验证r和c的合法性
	if (r < 0 || c < 0) throw BadInitializers();
	if ((!r || !c) && (r || c))
		throw BadInitializers();
	// 创建矩阵
	rows = r; cols = c;
	element = new T[r * c];
}

//下标操作符
template<class T>
T& Matrix<T>::operator()(int i, int j) const
{// 返回一个指向元素( i , j )的引用
	if (i < 1 || i > rows || j < 1 || j > cols) throw OutOfBounds();
	return element[(i - 1) * cols + j - 1];
}

//减法操作符
template<class T>
Matrix<T> Matrix<T>:: operator-(const Matrix<T>& m) const
{// 返回(*this) - m.
	if (rows != m.rows || cols != m.cols)
		throw SizeMismatch();
	// 创建结果矩阵w
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = element[i] - m.element[i];
	return w;
}

//乘法操作符
template<class T>
Matrix<T> Matrix<T>:: operator*(const Matrix<T>& m) const
{// 矩阵乘法，返回w = (*this) * m.
	if (cols != m.rows) throw SizeMismatch();
	Matrix<T> w(rows, m.cols); // 结果矩阵
	// 为*this, m和w定义游标
	// 并设定初始位置为( 1 , 1 )
	int ct = 0, cm = 0, cw = 0;
	// 对所有的i和j计算w ( i , j )
	for (int i = 1; i <= rows; i++) {
		// 计算出结果的第i 行
		for (int j = 1; j <= m.cols; j++) {
			// 计算w ( i , j )的第一项
			T sum = element[ct] * m.element[cm];
			// 累加其余项
			for (int k = 2; k <= cols; k++) {
				ct++; // 指向* t h i s第i行的下一个元素
				cm += m.cols; // 指向m 的第j 列的下一个项
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum; // 保存w ( i , j )
			// 重新调整至行首和下一列
			ct -= cols - 1;
			cm = j;
		}
		// 重新调整至下一行的行首和第一列
		ct += cols;
		cm = 0;
	}
	return w;
}