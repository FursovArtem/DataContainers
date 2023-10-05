#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
private:
	int Data;
	Element* Next, * Prev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), Next(Next), Prev(Prev)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class List;
};

class Iterator
{
private:
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	Iterator(const Iterator& other)
	{
		this->Temp = other.Temp;
		cout << "ItCopyConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->Next;
		return *this;
	}
	Iterator& operator--()
	{
		Temp = Temp->Prev;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->Next;
		return old;
	}
	Iterator operator--(int)
	{
		Iterator old = *this;
		Temp = Temp->Prev;
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

class List
{
private:
	Element* Head, * Tail;
	unsigned int size;
public:
	const Iterator cbegin()const
	{
		return Head;
	}
	const Iterator cend()const
	{
		return Tail;
	}
	List()
	{
		this->Head = this->Tail = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	List(List&& other)noexcept :List()
	{
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int> il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	~List()
	{
		deleteall();
		cout << "LDestructor:\t" << this << endl;
	}

	List& operator=(const List& other)
	{
		if (this == &other) return *this;
		this->~List();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->Next;
		}
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)noexcept
	{
		if (this == &other) return *this;
		this->~List();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t" << this << endl;
		return *this;
	}

	void deleteall()
	{
		while (size) del(1);
	}
	void del(int position = 1)
	{
		while (position < 1 || position > size)
		{
			cout << "Error: Wrong delete position.\nInput correct one: "; cin >> position;
		}
		int i = 1;
		Element* Erased = Head;
		for (; i < position; i++) Erased = Erased->Next;
		Element* Previous = Erased->Prev;
		Element* After = Erased->Next;
																// Check if deleting
		if (Previous && size != 1) Previous->Next = After;		// not Head
		if (After && size != 1) After->Prev = Previous;			// not Tail
		if (position == 1) Head = After;						// first
		if (position == size) Tail = Previous;					// last

		delete Erased;
		size--;
	}
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->Prev = nullptr;
		New->Next = Head;
		if (Head) Head->Prev = New;
		if (size == 0)Head = Tail = New;
		else Head = New;
		size++;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		New->Next = nullptr;
		New->Prev = Tail;
		if (Tail) Tail->Next = New;
		if (size == 0)Head = Tail = New;
		else Tail = New;
		size++;
	}

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->Next)
			cout << Temp->Data << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	List list{ 3,5,8,13,21 };
	list.print();
}