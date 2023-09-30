#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	//Forward - �����������, ����������������
private:
	Element* Head;
public:
	ForwardList()
	{
		//Default ������� ������ ������
		this->Head = nullptr; //���� ������ ����, ��� Head ��������� �� 0
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	// Adding elements:
	void push_front(int Data)
	{
		/*
		//1) ������� ����� ������� ��� ������������ ��������
		Element* New = new Element(Data);
		//2) �������������� ������� � ������
		New->pNext = Head;
		//3) ������ ����� ������� �������� ��������� ��������� ������
		Head = New;
		*/
		Head = new Element(Data, Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data, Temp->pNext);
	}

	// Removing elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr) return pop_back();
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		Erased = nullptr;
	}

	// Methods:
	void print()const
	{
		/*
		Element* Temp = Head; //Temp - ��������
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //������� �� ��������� �������
		}
		*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//cout << "���������� ��������� ������: " << Head->count << endl;
		cout << "���������� ��������� ������: " << Element::count << endl;
		//� ����������� ����� ������� ���������� ����� ��� ������ � �������� ���������� ���������
	}
};

//#define BASE_CHECK
//#define ERASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();

#ifdef ERASE_CHECK
	cout << endl;
	list.erase(123);
	list.print();
#endif // ERASE_CHECK

#endif // BASE_CHECK
	

}