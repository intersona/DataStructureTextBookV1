#include<iostream>
#include "common.h"
using namespace std;

int main()
{
	try 
	{
		LinearList<int> L(5);
		cout << "Length = " << L.Length() << endl;
		cout << "IsEmpty = " << L.IsEmpty() << endl;
	}
	catch (...)
	{

	}
}