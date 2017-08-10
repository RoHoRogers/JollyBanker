#include "stdafx.h"
#include "BSTree.h"

BSTree::BSTree()
{
	root = NULL;
}

BSTree::~BSTree() 
{
}

bool BSTree::Insert(Account *account)
{
	RecurseInsert(root, account);
	return true;
}

bool BSTree::Retrieve(const Account &target, Account *&source) const
{
	Account *temp = RecurseSearch(root, target);

	if (temp == NULL)
	{
		return false;
	}
	else
	{
		source = temp;
		return true;
	}
}

void BSTree::Display()
{
	//this->root->pAccount->
}

void BSTree::Empty()
{
	root = NULL;
}

bool BSTree::IsEmpty()
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Account * BSTree::RecurseSearch(Node *node, const Account &target) const
{
	if (node == NULL)
		return NULL;

	else if (target == *(node->pAccount))
	{
		return (node->pAccount);
	}
	else if (target < *(node->pAccount))
	{
		return RecurseSearch(node->left, target);
	}
	else
	{
		return RecurseSearch(node->right, target);
	}
}

void BSTree::RecurseInsert(Node *&node, Account *target)
{
	if (!node)
	{
		node = new Node();
		node->pAccount = target;
		return;
	}
	else if (*target < *node->pAccount)
	{
		RecurseInsert(node->left, target);
	}
	else
	{
		RecurseInsert(node->right, target);
	}
}

void BSTree:: Print()
{
	Print(root);
}

void BSTree:: Print(Node* parent)
{
	if (parent != NULL)
	{
		Print(parent->left);
		cout << *parent->pAccount << endl;
		Print(parent->right);
	}
	
}

ostream& operator<<(ostream& stream, const BSTree& tree)
{
	stream << tree.root->pAccount;

	return stream;
}