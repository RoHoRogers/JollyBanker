#pragma once
#ifndef BSTREE_H
#define BSTREE_H

#include "Account.h"



class BSTree
{
	friend ostream& operator<<(ostream& stream, const BSTree& tree);
public:
	BSTree::BSTree();
	BSTree::~BSTree();

	bool Insert(Account*);
	bool Retrieve(const Account &, Account * &) const;

	void Display();
	void Empty();
	bool IsEmpty();

	void Print();
	

private:
	struct Node
	{
		Account *pAccount;
		Node *left;
		Node *right;
	};
	Node *root = NULL;
	Account * RecurseSearch(Node *root, const Account &target) const;
	void BSTree::RecurseInsert(Node *&root, Account *target);
	void Print(Node* root);
};

#endif