#include <iostream>
using namespace std;

int Hello()
{
	return 1;
}

void main()
{
	setlocale(LC_ALL, "");
	cout << Hello << endl;
	int (*p_hello)() = Hello;	// ќбъ€вл€ем указатель на функцию
	cout << p_hello << endl;
}