#pragma once
#include<iostream>
#include<string>

using namespace std;

template<typename Type>
struct BinNode
{
	Type val;
	BinNode* left, * right;

	BinNode() :val(Type()), left(nullptr), right(nullptr) {}
	BinNode(Type val) :val(val), left(nullptr), right(nullptr) {}
	BinNode(Type val, BinNode* left, BinNode* right) :val(val), left(left), right(right) {}
};

template<typename Type>
struct BinTree
{
	BinNode<Type>* root;

	~BinTree() { clear(root); }
	void inOrder(BinNode<Type>* pos);
	void PreOrder(BinNode<Type>* pos);
	void PostOrder(BinNode<Type>* pos);

	// 迭代方式实现遍历
	void inOrder();
	void PreOrder();
	void PostOrder();

	void clear(BinNode<Type>* pos);
};

template<typename Type>
struct ListNode
{
	Type val;
	ListNode* next;

	ListNode(Type val) :val(val), next(nullptr) {}
	ListNode(Type val, ListNode* next) :val(val), next(next) {}
	ListNode() :val(Type()), next(nullptr) {}
};

template<typename Type>
struct DListNode // 双向链表节点 为非递归后序遍历而写
{
	Type val;
	DListNode* next, * pre;

	DListNode(Type val) :val(val), next(nullptr), pre(nullptr) {}
	DListNode(Type val, DListNode* pre, DListNode* next) :val(val), next(next), pre(pre) {}
	DListNode() :val(Type()), next(nullptr), pre(nullptr) {}
};

template<typename Type>
struct DList // 双向链表 为非递归后序遍历而写
{
	DListNode<Type>* head, * tail;
	DList();
	~DList();

	bool empty() { return head == tail; }
	void append(Type val);
	void del_last();

};

template<typename Type>
struct Stack
{
	ListNode<Type>* Top;
	int Length;

	Stack() :Top(nullptr), Length(0) {}
	bool empty() { return Length == 0; }
	void push(const Type& val); // 非常量引用的表达式必须为左值 所以加上const
	bool pop();
	bool pop(Type& return_val);
	Type* top() { return Top->val; }
	int length() { return Length; }
};

class Expression
{
private:
	BinTree<string>* tree;
public:
	Expression(string& formula);

	void toPolishNotation();
	void toAffixNotation();
	void Affix_Expression_to_Tree(BinNode<string>*& pos, string formula);
	void toReversePolishNotation();

	void inOrder() { tree->inOrder(); }
	void PreOrder() { tree->PreOrder(); }
	void PostOrder() { tree->PostOrder(); }
};
#pragma once
