#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

using TInfo = int;
struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE* right = nullptr) : info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level = 0)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << "    ";
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}

using TElem = Tree;

Tree Build_Balance(std::ifstream& file, int count)
{
	Tree result = nullptr;
	if (count)
	{
		int count_left = count / 2;
		int count_right = count - count_left - 1;
		int x;
		file >> x;
		result = new NODE(x);
		result->left = Build_Balance(file, count_left);
		result->right = Build_Balance(file, count_right);
	}
	return result;
}

using SInfo = Tree;

class stack
{
private:
	SInfo* elements;
	int size;
	int top;
public:
	stack();
	~stack();
	bool empty();
	bool full();
	void resize(int n_size);
	int get_alloc_size();
	void push(SInfo elem);
	SInfo pop();
	SInfo Top();
	void View();
};

stack::stack()
{
	size = 1;
	elements = new SInfo[size];
	top = -1;
}

stack::~stack()
{
	delete[] elements;
}

bool stack::empty()
{
	return top == -1;
}

bool stack::full()
{
	return top == size - 1;
}

void stack::resize(int n_size)
{
	if (n_size > size)
	{
		SInfo* temp = new SInfo[n_size];
		for (int i = 0; i <= top; i++)
			temp[i] = elements[i];
		size = n_size;
		delete[] elements;
		elements = temp;
	}
}

int stack::get_alloc_size()
{
	return size;
}

void stack::push(SInfo elem)
{
	if (size == top + 1)
		resize(2 * size);
	elements[++top] = elem;
}

SInfo stack::pop()
{
	SInfo elem = elements[top--];
	return elem;
}

SInfo stack::Top()
{
	return elements[top];
}

void stack::View()
{
	for (int i = top; i >= 0; i--)
		std::cout << elements[i] << ' ';
	std::cout << std::endl;
}

void task1(Tree root, Tree& max_tree, Tree& min_tree, Tree& max_p, Tree& min_p)
{
	if (root->right || root->left)
	{
		if (root->right)
		{
			task1(root->right, max_tree, min_tree, max_p, min_p);
			if (root->right == max_tree)
			{
				max_p = root;
			}
			else if (root->right == min_tree)
			{
				min_p = root;
			}
		}
		if (root->left)
		{
			task1(root->left, max_tree, min_tree, max_p, min_p);
			if (root->left == max_tree)
			{
				max_p = root;
			}
			else if (root->left == min_tree)
			{
				min_p = root;
			}
		}
	}
	else
	{
		if (!max_tree || max_tree->info < root->info)
		{
			max_tree = root;
		}
		if (!min_tree || min_tree->info > root->info)
		{
			min_tree = root;
		}
	}
}

void task2(Tree root, Tree& max_p, Tree& min_p, Tree& max_tree, Tree& min_tree) {
	stack s;
	while (root != NULL || !s.empty()) {
		if (!s.empty()) {
			root = s.pop();
			if (!s.empty() && root->right == s.Top()) {
				root = s.pop();
			}
			else {
				if (root->right == max_tree || root->left == max_tree)
					max_p = root;
				else if (root->right == min_tree || root->left == min_tree)
					min_p = root;
				root = NULL;
			}
		}
		while (root != NULL) {
			s.push(root);
			if (root->right != NULL) {
				s.push(root->right);
				s.push(root);
			}
			if (!root->left && !root->right && (!max_tree || max_tree->info < root->info))
				max_tree = root;
			else if (!root->left && !root->right && (!min_tree || min_tree->info > root->info))
				min_tree = root;
			root = root->left;
		}
	}
 }

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("input.txt");
	Tree root;
	int count;
	file >> count;
	root = Build_Balance(file, count);

	Print(root);
	std::cout << std::endl << std::endl;

	Tree max_tree = nullptr, min_tree = nullptr;
	Tree max_p = nullptr, min_p = nullptr;
	//task1(root, max_tree, min_tree, max_p, min_p);
	task2(root, max_p, min_p, max_tree, min_tree);
	if (max_p->right == max_tree && min_p->right == min_tree)
	{
		max_p->right = min_tree;
		min_p->right = max_tree;
	}
	else if (max_p->right == max_tree && min_p->left == min_tree)
	{
		max_p->right = min_tree;
		min_p->left = max_tree;
	}
	else if (max_p->left == max_tree && min_p->right == min_tree)
	{
		max_p->left = min_tree;
		min_p->right = max_tree;
	}
	else if (max_p->left == max_tree && min_p->left == min_tree)
	{
		max_p->left = min_tree;
		min_p->left = max_tree;
	}
	Print(root);
}
