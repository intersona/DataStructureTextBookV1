#include<iostream>
#include"StackOfFormula.h"
using namespace std;

class Hanoi {
	friend void TowersOfHanoi(int);
public:
	void TowersOfHanoi(int n, int x, int y, int z);
	void ShowState() {};
private:
	Stack<int>* S[4];
};
void Hanoi::TowersOfHanoi(int n, int x, int y, int z)
{// ��n �����Ӵ���x �ƶ�����y���ɽ�������z
	int d; // ���ӱ��
	if (n > 0) {
		TowersOfHanoi(n - 1, x, z, y);
		S[x]->Delete(d); //��x������һ������
		S[y]->Add(d); //��������ӷŵ�y ��
		ShowState();
		TowersOfHanoi(n - 1, z, y, x);
	}
}
void TowersOfHanoi(int n)
{// Hanoi::towersOfHanoi��Ԥ�������
	Hanoi X;
		X.S[1] = new Stack<int>(n);
	X.S[2] = new Stack<int>(n);
	X.S[3] = new Stack<int>(n);
	for (int d = n; d > 0; d--) // ��ʼ��
		X.S[1]->Add(d); // �ѵ���d �ŵ���1��
	//����1�ϵ�n�������ƶ�����3�ϣ���������2 �İ���
		X.TowersOfHanoi(n, 1, 2, 3);
}