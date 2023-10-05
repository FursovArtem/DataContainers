#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
//#define DEBUG

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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;

class Iterator
{
private:
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Iterator(const Iterator& other)
	{
		this->Temp = other.Temp;
#ifdef DEBUG
		cout << "ItCopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& rvalue)const
	{
		return this->Temp == rvalue.Temp;
	}
	bool operator!=(const Iterator& rvalue)const
	{
		return this->Temp != rvalue.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	//Forward - односвязный, однонаправленный
private:
	Element* Head;
	unsigned int size;
public:
	const Iterator begin()const
	{
		return Head;
	}
	const Iterator end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		//Default создает пустой список
		this->Head = nullptr; //Если список пуст, его Head указывает на 0
		this->size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//initializer_list - это контейнер.
		//Контейнер - это объект-органайзер объектов в памяти.
		//Как и у любого другого контейнера у него есть методы begin() и end().
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:\t" << this << "<-" << &other << endl;
	}
	ForwardList(ForwardList&& other)noexcept :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << "<-" << &other << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}
	// Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "LCopyAssignment:\t" << this << "<-" << &other << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << "<-" << &other << endl;
		return *this;
	}
	// Adding elements:
	void push_front(int Data)
	{
		/*
		//1) Создаем новый элемент для добавляемого значения
		Element* New = new Element(Data);
		//2) Пристыковываем элемент к списку
		New->pNext = Head;
		//3) Теперь новый элемент является начальным элементом списка
		Head = New;
		*/
		Head = new Element(Data, Head);
		size++;
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
		size++;
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
		size++;
	}

	// Removing elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext) Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp == nullptr) return;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		Erased = nullptr;
		size--;
	}

	// Methods:
	void print()const
	{
		/*
		Element* Temp = Head; //Temp - итератор
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
		*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//cout << "Количество элементов списка: " << Head->count << endl;
		cout << "Количество элементов списка: " << this->size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
		//К статическим полям принято обращаться через имя класса и оператор разрешения видимости
	}
	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			this->pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
};

ForwardList operator+(const ForwardList& lvalue, const ForwardList& rvalue)
{
	ForwardList result = lvalue;
	for (Iterator it = rvalue.begin(); it != rvalue.end(); it++)
		result.push_back(*it);
	return result;
}

//#define BASE_CHECK
//#define ERASE_CHECK
//#define RANGE_BASED_FORWARD_LIST_CHECK
//#define OPERATOR_PLUS_CHECK
#define FORWARD_LIST_PERFORMANCE_TEST

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
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

#ifdef RANGE_BASED_FORWARD_LIST_CHECK
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();

	for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FORWARD_LIST_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	for (int i : list1) cout << i << tab; cout << endl;

	ForwardList list2 = { 33, 55, 81 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3;
	list3 = list1 + list2;
	for (int i : list3)cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK

#ifdef FORWARD_LIST_PERFORMANCE_TEST
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		int value = rand() % 100;
		//cout << value << tab;
		list.push_front(value);
	}
	cout << endl;
	//for (int i : list)cout << i << tab; cout << endl;
	clock_t end = clock();
	cout << "Data loaded for " << double(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Copying list..." << endl;
	start = clock();
	ForwardList list2 = list;
	//for (int i : list2)cout << i << tab; cout << endl;
	end = clock();
	cout << "List copied for " << double(end - start) / CLOCKS_PER_SEC << endl;
#endif // FORWARD_LIST_PERFORMANCE_TEST


}