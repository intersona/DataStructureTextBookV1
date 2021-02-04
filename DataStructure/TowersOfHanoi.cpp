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
{// 把n 个碟子从塔x 移动到塔y，可借助于塔z
	int d; // 碟子编号
	if (n > 0) {
		TowersOfHanoi(n - 1, x, z, y);
		S[x]->Delete(d); //从x中移走一个碟子
		S[y]->Add(d); //把这个碟子放到y 上
		ShowState();
		TowersOfHanoi(n - 1, z, y, x);
	}
}
void TowersOfHanoi(int n)
{// Hanoi::towersOfHanoi的预处理程序
	Hanoi X;
		X.S[1] = new Stack<int>(n);
	X.S[2] = new Stack<int>(n);
	X.S[3] = new Stack<int>(n);
	for (int d = n; d > 0; d--) // 初始化
		X.S[1]->Add(d); // 把碟子d 放到塔1上
	//把塔1上的n个碟子移动到塔3上，借助于塔2 的帮助
		X.TowersOfHanoi(n, 1, 2, 3);
}