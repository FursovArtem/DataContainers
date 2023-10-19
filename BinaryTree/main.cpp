#include <iostream>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft, * pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}

	int depth()const
	{
		return depth(Root);
	}
	void depth_print(int depth)const
	{
		return depth_print(Root, depth);
	}
	void tree_print()const
	{
		tree_print(0, this->depth() * 8);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
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
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr) return;
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
		if (Root)
		{
			erase(Data, Root->pLeft);
			erase(Data, Root->pRight);
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int sum(Element* Root)const
	{
		return Root ? Root->Data + sum(Root->pLeft) + sum(Root->pRight) : 0;
	}
	int count(Element* Root)const
	{
		return Root ? 1 + count(Root->pLeft) + count(Root->pRight) : 0;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		else
		{
			clear(Root->pLeft);
			clear(Root->pRight);
			delete Root;
		}
	}
	int depth(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		if (depth(Root->pLeft) + 1 > depth(Root->pRight) + 1) return depth(Root->pLeft) + 1;
		else return depth(Root->pRight) + 1;*/
		/*return Root == nullptr ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;*/
		if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
	}
	void depth_print(Element* Root, int depth, int width = 8)const
	{
		if (Root == nullptr)return;
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data << tab;
			return;
		}
		depth_print(Root->pLeft, depth - 1, width);
		cout.width(width); cout << "";
		depth_print(Root->pRight, depth - 1, width);
	}
	void tree_print(int depth, int width)const
	{
		if (depth == this->depth())return;
		depth_print(this->Root, depth, width);
		cout << endl;
		cout << endl;
		cout << endl;
		tree_print(depth + 1, width / 2);
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template<typename T>
void measure(const char msg[], T(Tree::* function)()const, const Tree& tree)
{
	cout << msg;
	clock_t start = clock();
	T value = (tree.*function)();
	clock_t end = clock();
	cout << value << ", вычислено за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
}

//#define BASE_CHECK
//#define PERFORMANCE_CHECK_1
//#define UNIQUE_TREE_CHECK
//#define ERASE_CHECK
#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();

#ifdef PERFORMANCE_CHECK_1
	clock_t start = clock();	//clock() возвращает количество тактов процессора
	cout << "Минимальное значение в дереве: " << tree.minValue() << ", вычислено за ";
	clock_t end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////
	start = clock();
	cout << "Максимальное значение в дереве: " << tree.maxValue() << ", вычислено за ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////
	start = clock();
	cout << "Сумма элементов дерева: " << tree.sum() << ", вычислено за ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////
	start = clock();
	cout << "Количество элементов дерева: " << tree.count() << ", вычислено за ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////
	start = clock();
	cout << "Среднее арифметическое элементов дерева: " << tree.avg() << ", вычислено за ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////
	start = clock();
	cout << "Глубина дерева: " << tree.depth() << ", вычислено за ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
	/////////////////////////////////////////////////////////////////////////////////  
#endif // PERFORMANCE_CHECK_1

	measure("Минимальное значение в дереве: ", &Tree::minValue, tree);
	measure("Максимальное значение в дереве: ", &Tree::maxValue, tree);
	measure("Сумма элементов в дереве: ", &Tree::sum, tree);
	measure("Количество элементов в дереве: ", &Tree::count, tree);
	measure("Среднее арифметическое элементов дерева: ", &Tree::avg, tree);
	measure("Глубина дерева: ", &Tree::depth, tree);

#ifdef UNIQUE_TREE_CHECK
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Количество элементов дерева: " << u_tree.count() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.avg() << endl;
#endif // UNIQUE_TREE_CHECK

#endif // BASE_CHECK

#ifdef ERASE_CHECK
	//Tree tree = { 50, 25, 75, 16, 32, 64, 90 };
	Tree tree = { 5, 8, 2, 6, 7, 9, 10, 1, 3, 4 };
	tree.print();

	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();
#endif // ERASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree =
	{ 50,
				25,					75,
			16,		 32,		64,		90,
		15,									91,
												98
	};
	//cout << "Глубина дерева: " << tree.depth() << endl;
#endif // DEPTH_CHECK
	tree.tree_print();
}