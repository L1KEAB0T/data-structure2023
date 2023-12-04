#include"BinSort.h"

template<typename Type>
void BST<Type>::insert(Type val, BinNode<Type>*& pos)
{
	if (!pos && pos == root)
	{
		pos = new BinNode<Type>(val);
		return;
	}
	else if (pos->val == val)
	{
		cout << "already have element:" << val << "!\n";
		return;
	}
	else if (pos->val > val)
		if (!pos->left)
			pos->left = new BinNode<Type>(val);
		else
			insert(val, pos->left);
	else
		if (!pos->right)
			pos->right = new BinNode<Type>(val);
		else
			insert(val, pos->right);
}

template<typename Type>
void BST<Type>::inOrder(BinNode<Type>* pos)
{
	if (!pos) return;

	inOrder(pos->left);
	cout << pos->val << " ";
	inOrder(pos->right);
}

template<typename Type>
bool BST<Type>::search(Type val, BinNode<Type>* pos)
{
	if (!pos) return false;
	else if (pos->val > val)
		return search(val, pos->left);
	else if (pos->val < val)
		return search(val, pos->right);
	else
		return true;
}

int input() // 0~
{
	int num;
	while (true)
	{
		cout << "1-展示 2-插入 3-查找 4-删除 0-退出\n"
			<< "请输入操作码：\n";
		cin >> num;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入有误！重新输入！\n";
			continue;
		}
		else if (num < 0 || num > 4)
		{
			cout << "操作码听不懂子~重新输入吧~\n";
			continue;
		}
		else
			break;
	}

	return num;
}

template<typename Type>
void BST<Type>::clear(BinNode<Type>* pos)
{
	if (!pos) return;
	else if (!pos->left && !pos->right)
	{
		delete pos;
		pos = nullptr;
	}
	else
	{
		clear(pos->left);
		clear(pos->right);
		pos->left = pos->right = nullptr;
	}
}

template<typename Type>
void BST<Type>::del(Type val)
{
	root = DeleteNode(val, root);
}

template<typename Type>
BinNode<Type>* BST<Type>::DeleteNode(Type val, BinNode<Type>*& pos) //555 终于做出来了
{
	if (!pos) return nullptr;

	if (pos->val > val)
		pos->left = DeleteNode(val, pos->left);
	else if (pos->val < val)
		pos->right = DeleteNode(val, pos->right);
	else
	{
		cout << "找到！已删除！\n";
		if (!pos->left) //leaf node or only have right child
		{
			auto temp = pos;
			pos = pos->right;
			delete temp;
		}
		else if (!pos->right) // only have left child
		{
			auto temp = pos;
			pos = pos->left;
			delete temp;
		}
		else // both
		{
			auto cursor = pos->right;
			while (cursor->left != nullptr)
				cursor = cursor->left;

			cursor->left = pos->left;
			auto temp = pos;
			pos = pos->right;
			delete temp;
		}
	}

	return pos;
}

int main()
{
	BST<int> bst_tree;
	int num;
	cout << "请先输入一串数字来创建二叉树 按Ctrl+Z结束输入（Windows）（Linux/Mac输入Ctrl+D）\n";
	while (cin >> num)
	{
		bst_tree.insert(num, bst_tree.root);
	}
	if (cin.fail())
	{
		cin.clear();
		cin.get();//^Z
	}

	while (true)
	{
		int choice = input();
		if (!choice)
		{
			cout << "拜拜嘞\n";
			break;
		}
		switch (choice)
		{
			case 1:
				bst_tree.inOrder(bst_tree.root);
				cout << endl;
				break;
			case 2:
				cout << "请输入插入数字：";
				while (true)
				{
					cin >> num;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "输入有误！重新输入！\n";
						continue;
					}
					else
						break;
				}
				bst_tree.insert(num, bst_tree.root);
				cout << "现在的次序为：\n";
				bst_tree.inOrder(bst_tree.root);
				cout << endl;
				break;
			case 3:
				cout << "请输入查找数字：";
				while (true)
				{
					cin >> num;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "输入有误！重新输入！\n";
						continue;
					}
					else
						break;
				}
				if (bst_tree.search(num, bst_tree.root))
					cout << "查找成功！\n";
				else
					cout << "没有呢\n";
				break;
			case 4:
				cout << "请输入删除数字：";
				while (true)
				{
					cin >> num;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "输入有误！重新输入！\n";
						continue;
					}
					else
						break;
				}
				bst_tree.del(num);
				break;
		}
	}

	return 0;
}