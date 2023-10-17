#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft, * pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	} *Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		deleteall();
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	int minValue(Element* Root)
	{
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int minValue()
	{
		return minValue(Root);
	}
	int maxValue(Element* Root)
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int maxValue()
	{
		return maxValue(Root);
	}
	int Sum(Element* Root)
	{
		return Root ? Root->Data + Sum(Root->pLeft) + Sum(Root->pRight) : 0;
	}
	int Sum()
	{
		return Sum(Root);
	}
	int Count(Element* Root)
	{
		return Root ? 1 + Count(Root->pLeft) + Count(Root->pRight) : 0;
	}
	int Count()
	{
		return Count(Root);
	}
	double Avg()
	{
		return (double)Sum(Root) / Count(Root);
	}
	void deleteall(Element* Root)
	{
		if (Root == nullptr)return;
		else
		{
			deleteall(Root->pLeft);
			deleteall(Root->pRight);
			delete Root;
			Root = nullptr;
		}
	}
	void deleteall()
	{
		deleteall(Root);
	}
	
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void print()const
	{
		print(Root);
	}
};

class UniqueTree :public Tree
{
	std::vector<int> exists;
	static int skipped;
public:
	UniqueTree() :Tree() { cout << "UTConstructor:\t" << this << endl; }
	~UniqueTree() { cout << "UTDestructor:\t" << this << endl; }
	void insert(int Data)
	{
		if (std::find(exists.begin(), exists.end(), Data) != exists.end()) 
		{
			skipped++;
			return;
		}
		else
		{
			Tree::insert(Data);
			exists.push_back(Data);
		}
	}
	void print()const
	{
		Tree::print();
		cout << "\nВсего пропущено " << skipped << " повторяющихся элементов" << endl;
	}
};

int UniqueTree::skipped = 0;

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Количество элементов дерева: " << tree.Count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
}