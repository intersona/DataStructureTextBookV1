#include<iostream>
#include"Chain.h"
using namespace std;
int main()
{
	Chain<int> C;
	C.Insert(0, 1);
	C.Insert(1, 2);
	C.Insert(2,3);
	cout <<"C = " << C << endl;
	int x;
	C.Delete(2, x);
	cout << "C = " << C << endl;
	cout << "x = " << x << endl;
	C.Append(0);
	cout << "C = " << C << endl;
	x = C.Search(0);
	cout << "x = " << x << endl;
	C.Erase();
	cout << "C = " << C << endl;

}