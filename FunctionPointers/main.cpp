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
	int (*p_hello)() = Hello;	// ��������� ��������� �� �������
	cout << p_hello << endl;
}