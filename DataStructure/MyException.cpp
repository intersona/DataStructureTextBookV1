#include"MyException.h"
using namespace std;
// 使new引发NoMem异常而不是xalloc异常
void my_new_handler()
{
	throw NoMem();
};
new_handler Old_Handler_ = set_new_handler(my_new_handler);