#include"MyException.h"
using namespace std;
// ʹnew����NoMem�쳣������xalloc�쳣
void my_new_handler()
{
	throw NoMem();
};
new_handler Old_Handler_ = set_new_handler(my_new_handler);