#include<iostream>
#include"Chain.h"
using namespace std;
int main()
{
	Chain<int> C;
	C.Insert(0, 1);
	C.Insert(1, 2);
	
	C.Insert(2,3);
	cout << C << endl;
	int x;
	C.Delete(2, x);
	cout << C << endl;

}