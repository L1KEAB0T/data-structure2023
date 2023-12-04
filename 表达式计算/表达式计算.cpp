#include"expression.h"

template<typename Type>
DList<Type>::DList()
{
	head = new DListNode<Type>();
	tail = head;
}

template<typename Type>
DList<Type>::~DList()
{
	while (head)
	{
		DListNode<Type>* temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename Type>
void DList<Type>::append(Type val)
{
	DListNode<Type>* new_data = new DListNode<Type>(val, tail, nullptr);
	tail->next = new_data;
	tail = tail->next;
}

template<typename Type>
void DList<Type>::del_last()
{
	if (!empty())
	{
		tail = tail->pre;
		delete tail->next;
		tail->next = nullptr;
	}
}

template<typename Type>
void BinTree<Type>::inOrder(BinNode<Type>* pos)
{
	if (!pos) return;

	inOrder(pos->left);
	cout << pos->val << " ";
	inOrder(pos->right);
}

template<typename Type>
void BinTree<Type>::PreOrder(BinNode<Type>* pos)
{
	if (!pos) return;

	cout << pos->val << " ";
	PreOrder(pos->left);
	PreOrder(pos->right);
}

template<typename Type>
void BinTree<Type>::PostOrder(BinNode<Type>* pos)
{
	if (!pos) return;

	PostOrder(pos->left);
	PostOrder(pos->right);
	cout << pos->val << " ";
}

template<typename Type>
void BinTree<Type>::inOrder()
{
	Stack<BinNode<Type>*> stack;
	BinNode<Type>* cursor = root;

	while (!stack.empty() || cursor)
	{
		while (cursor)
		{
			stack.push(cursor);
			cursor = cursor->left;
		}

		stack.pop(cursor);

		cout << cursor->val << " ";

		cursor = cursor->right;
	}
}

template<typename Type>
void BinTree<Type>::PreOrder()
{
	Stack<BinNode<Type>*> stack;
	BinNode<Type>* cursor = nullptr;

	if (root) stack.push(root);

	// left later in and earlier out
	while (!stack.empty())
	{
		stack.pop(cursor);

		cout << cursor->val << " ";

		if (cursor->right) stack.push(cursor->right);
		if (cursor->left) stack.push(cursor->left);
	}
}

template<typename Type>
void BinTree<Type>::PostOrder()
{
	Stack<BinNode<Type>*> stack;
	DList<Type> result;
	BinNode<Type>* cursor = nullptr;

	if (root) stack.push(root);

	// right later in and earlier out
	while (!stack.empty())
	{
		stack.pop(cursor);

		result.append(cursor->val);

		if (cursor->left) stack.push(cursor->left);
		if (cursor->right) stack.push(cursor->right);
	}

	DListNode<Type>* result_cursor = result.tail;

	while (result_cursor != result.head)
	{
		cout << result_cursor->val << " ";
		result_cursor = result_cursor->pre;
	}
}

template<typename Type>
void BinTree<Type>::clear(BinNode<Type>* pos)
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
void Stack<Type>::push(const Type& val)
{
	if (empty())
		Top = new ListNode<Type>(val);
	else
	{
		ListNode<Type>* new_data = new ListNode<Type>(Type(val), Top);
		Top = new_data;
	}

	Length++;
}

template<typename Type>
bool Stack<Type>::pop()
{
	if (empty()) return false;

	ListNode<Type>* del_data = Top;
	Top = Top->next;
	delete del_data;
	Length--;
	return true;
}

template<typename Type>
bool Stack<Type>::pop(Type& return_val)
{
	if (empty()) return false;

	ListNode<Type>* del_data = Top;
	return_val = del_data->val;
	Top = Top->next;
	delete del_data;
	Length--;
	return true;
}

Expression::Expression(string& formula)
{
	tree = new BinTree<string>;
	Affix_Expression_to_Tree(tree->root, formula);
}

void Expression::toPolishNotation()
{
	tree->PreOrder(tree->root);
}

void Expression::toAffixNotation()
{
	tree->inOrder(tree->root);
}

void Expression::Affix_Expression_to_Tree(BinNode<string>*& pos, string formula)
{
	while (formula[formula.size() - 1] == ')' && formula[0] == '(')
	{
		formula.erase(0, 1);
		formula.erase(formula.size() - 1, 1);
	}

	for (int i = formula.size() - 1; i >= 0; i--)
	{
		if (formula[i] == ')')
		{
			while (formula[i] != '(')
				i--;
		}
		else if (formula[i] == '+' || (formula[i] == '-' && i != 0 && (isdigit(formula[i - 1]) || formula[i - 1] == ')') || (formula[i] == '-' && i != 0 && (isdigit(formula[i - 1]) || formula[i - 1] == '��'))))
		{
			pos = new BinNode<string>(string(1, formula[i])); // "+"*1 or "-"*1
			Affix_Expression_to_Tree(pos->left, formula.substr(0, i));
			Affix_Expression_to_Tree(pos->right, formula.substr(i + 1, formula.size() - i));
			return;
		}
	}

	for (int i = formula.size() - 1; i >= 0; i--)
	{
		if (formula[i] == ')')
		{
			while (formula[i] != '(')
				i--;
		}
		else if (formula[i] == '*' || formula[i] == '/')
		{
			pos = new BinNode<string>(string(1, formula[i]));
			Affix_Expression_to_Tree(pos->left, formula.substr(0, i));
			Affix_Expression_to_Tree(pos->right, formula.substr(i + 1, formula.size() - i));
			return; // !!!
		}
	}

	pos = new BinNode<string>(formula);
}

void Expression::toReversePolishNotation()
{
	tree->PostOrder(tree->root);
}

int main()
{
	cout << "��������ʽ��";
	string expression;
	cin >> expression;
	Expression result(expression);

	cout << "ǰ׺���ʽΪ��";
	result.toPolishNotation();

	cout << endl;
	cout << "��׺���ʽΪ��" << expression << endl;

	cout << "��׺���ʽΪ��";
	result.toReversePolishNotation();
	cout << endl;

	cout << "�������ǵݹ鷽ʽ���ǰ׺��׺��׺���ʽ��\n";
	result.PreOrder();
	cout << endl;
	result.inOrder();
	cout << endl;
	result.PostOrder();
	cout << endl;
	return 0;
}