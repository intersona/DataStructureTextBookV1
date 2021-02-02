#include <iostream>
#include <string>
#include "StackOfFormula.h"
using namespace std;
const int MaxLength = 100; // 最大的字符串长度
void PrintMatchedPairs(char* expr)
{// 括号匹配
	DerivedStack<int> s(MaxLength);
	int j, length = strlen(expr);
	// 从表达式expr 中搜索
	for (int i = 1; i <= length; i++) {
		if (expr[i - 1] == '(') s.Add(i);
		else if (expr[i - 1] == ')')
			try{ s.Delete(j);
			cout << j << ' ' << i << endl; }
			catch (OutOfBounds)
			{
				cout << "No match for right parenthesis" << " at " << i << endl;
			}
	}
	// 堆栈中所剩下的(都是未匹配的
	while (!s.IsEmpty()) {
		s.Delete(j);
		cout << "No match for left parenthesis at " << j << endl;
	}
}
void main(void)
{
	char expr[MaxLength];
	cout << "Type an expression of length at most " << MaxLength << endl;
	cin.getline(expr,MaxLength);
	cout << "The pairs of matching parentheses in" << endl;
	puts(expr);
	cout << "are" << endl;
	PrintMatchedPairs(expr);
}