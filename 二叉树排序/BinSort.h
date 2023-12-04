#pragma once
#include<iostream>

using namespace std;

template<typename Type>
struct BinNode
{
	Type val;
	BinNode* left, * right;

	BinNode() :val(Type()), left(nullptr), right(nullptr) {}
	BinNode(Type val) :val(val), left(nullptr), right(nullptr) {}
	BinNode(Type val, BinNode* left, BinNode* right, BinNode* parent) :val(val), left(left), right(right) {}
};

template<typename Type>
struct BST
{
	BinNode<Type>* root;

	BST() :root(nullptr) {}
	~BST() { clear(root); }
	void insert(Type val, BinNode<Type>*& pos);
	void inOrder(BinNode<Type>* pos);
	bool search(Type val, BinNode<Type>* pos);
	void clear(BinNode<Type>* pos);
	void del(Type val);
	BinNode<Type>* DeleteNode(Type val, BinNode<Type>*& pos);
};

//最好再加个删除功能 就更好了#pragma once
