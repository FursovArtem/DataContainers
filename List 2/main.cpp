﻿#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	} *Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	//				Constructors:
	List();
	List(const std::initializer_list<T>& il);
	List(const List& other);
	~List();

	//					Operators:
	List& operator=(const List& other);

	//					Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//						Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);

	//						Methods:
	void print()const;
	void reverse_print()const;
};

////////////////////////////////////////////////////////////////
///////////			List member-functions		////////////////
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
//				Constructors:
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T>List<T>::List(const List& other) :List()
{
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	*this = other;
	cout << "LCopyConstruct: " << this << endl;
}
template<typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//					Operators:
template<typename T>List<T>& List<T>::operator=(const List & other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}

//					Addign elements:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	if (Index >= size)return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}

//						Removing elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>void List<T>::erase(int Index)
{
	if (Index == 0)return pop_front();
	if (Index == size - 1)return pop_back();
	if (Index >= size)return;

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	//В этом месте Temp указывает на нужный элемент.

	//1) Исключаем элемент из списка:
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;

	//2) Удаляем элемент из памяти:
	delete Temp;

	size--;
}

//						Methods:
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
///////////			List member-functions		////////////////
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
///////////		Element member-functions		////////////////
template<typename T>List<T>::Element::Element(T Data, Element * pNext, Element * pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}
///////////		Element member-functions		////////////////
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/////////	ConstBaseIterator member-functions	////////////////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
/////////	ConstBaseIterator member-functions	////////////////
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
/////////	ConstIterator member-functions		////////////////
template<typename T>List<T>::ConstIterator::ConstIterator(Element * Temp) :ConstBaseIterator(Temp) {}
template<typename T>List<T>::ConstIterator::~ConstIterator() {}

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
/////////	ConstIterator member-functions		////////////////
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
///////// ConstReverseIterator member-functions ////////////////
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator() {}

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
///////// ConstReverseIterator member-functions ////////////////
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/////////		Iterator member-functions		////////////////
template<typename T>List<T>::Iterator::Iterator(Element* Temp) :ConstIterator(Temp) {}
template<typename T>List<T>::Iterator::~Iterator() {}
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
/////////		Iterator member-functions		////////////////
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
/////////	ReverseIterator member-functions	////////////////
template<typename T>List<T>::ReverseIterator::ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
template<typename T>List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
/////////	ReverseIterator member-functions	////////////////
////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}

template<typename T>void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		//*it *= 10;
		cout << *it << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)cout << i << tab; cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITER

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	reverse_print(list3);
	for (List<int>::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 10;
	}
	reverse_print(list3);
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list = { 2.7, 3.14, 5.3, 8.1 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "No", "money", "no", "honey" };
	for (std::string i : s_list)cout << i << tab; cout << endl;


}