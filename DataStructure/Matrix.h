#pragma once
#include <iostream>
#include"MyException.h"
using namespace std;

template<class T>
class Matrix {
public:
	Matrix(int r = 0, int c = 0);
	Matrix(const Matrix<T>& m); //���ƹ��캯��
	~Matrix() { delete[] element; }
	int Rows() const { return rows; }
	int Columns() const { return cols; }
	T& operator()(int i, int j) const;
	Matrix<T>& operator=(const Matrix<T>& m);
	Matrix<T> operator+() const; // һԪ�ӷ�
	Matrix<T> operator+(const Matrix<T>& m) const;
	Matrix<T> operator-() const; // һԪ����
	Matrix<T> operator-(const Matrix<T>& m) const;
	Matrix<T> operator*(const Matrix<T>& m) const;
	Matrix<T>& operator+=(const T& x);
private:
	int rows, cols; // ����ά��
	T* element; // Ԫ������
};

//��Maxtrix�Ĺ��캯��
template<class T>
Matrix<T>::Matrix(int r, int c)
{// ��M a t r i x�Ĺ��캯��
// ��֤r��c�ĺϷ���
	if (r < 0 || c < 0) throw BadInitializers();
	if ((!r || !c) && (r || c))
		throw BadInitializers();
	// ��������
	rows = r; cols = c;
	element = new T[r * c];
}

//�±������
template<class T>
T& Matrix<T>::operator()(int i, int j) const
{// ����һ��ָ��Ԫ��( i , j )������
	if (i < 1 || i > rows || j < 1 || j > cols) throw OutOfBounds();
	return element[(i - 1) * cols + j - 1];
}

//����������
template<class T>
Matrix<T> Matrix<T>:: operator-(const Matrix<T>& m) const
{// ����(*this) - m.
	if (rows != m.rows || cols != m.cols)
		throw SizeMismatch();
	// �����������w
	Matrix<T> w(rows, cols);
	for (int i = 0; i < rows * cols; i++)
		w.element[i] = element[i] - m.element[i];
	return w;
}

//�˷�������
template<class T>
Matrix<T> Matrix<T>:: operator*(const Matrix<T>& m) const
{// ����˷�������w = (*this) * m.
	if (cols != m.rows) throw SizeMismatch();
	Matrix<T> w(rows, m.cols); // �������
	// Ϊ*this, m��w�����α�
	// ���趨��ʼλ��Ϊ( 1 , 1 )
	int ct = 0, cm = 0, cw = 0;
	// �����е�i��j����w ( i , j )
	for (int i = 1; i <= rows; i++) {
		// ���������ĵ�i ��
		for (int j = 1; j <= m.cols; j++) {
			// ����w ( i , j )�ĵ�һ��
			T sum = element[ct] * m.element[cm];
			// �ۼ�������
			for (int k = 2; k <= cols; k++) {
				ct++; // ָ��* t h i s��i�е���һ��Ԫ��
				cm += m.cols; // ָ��m �ĵ�j �е���һ����
				sum += element[ct] * m.element[cm];
			}
			w.element[cw++] = sum; // ����w ( i , j )
			// ���µ��������׺���һ��
			ct -= cols - 1;
			cm = j;
		}
		// ���µ�������һ�е����׺͵�һ��
		ct += cols;
		cm = 0;
	}
	return w;
}