/*
 * Team 5
 *
 * DressBST.h
 */

#ifndef DressBST_H_
#define DressBST_H_

#include <iostream>
#include <string>
#include <cstddef>
#include <assert.h>
#include "Dress.h"

using namespace std;

template<typename Dress>
class DressBST
{
private:

    struct Node
	{
        Dress item;
        Node* left;
        Node* right;

        Node(Dress newItem)
        {
            item = newItem;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;
    bool isUnique;

    /**Private Helper Functions*/

    void getKeyItemsHelper(Node* root, Dress key, vector<Dress>* v) const;
    //private helper function for getKeyItems function to get keys for dresses

    void insertHelper(Node* root, Dress item);
    //private helper function for insert function to insert a new dress into a DressBST

    void inOrderPrintHelper(ostream& out, Node* root) const;
    //private helper function for inOrderPrint function,
    //recursively called to display dresses in order from smallest to largest

    void inOrderPrintHelper2(ostream& out, Node* root) const;
    //private helper function for inOrderPrint2 function

    void copyHelper(Node* copy);
    //recursive helper function for copy constructor

    void destructorHelper(Node* root);
    //private helper function for destructor,
    //recursively frees the memory in the DressBST

    bool searchHelper(Node* root, Dress item) const;
    //recursive helper function to search dresses in the cart,
    //returns whether the dress is found in the cart

    Dress minimumHelper(Node* root) const;
    //recursive helper function to removeHelper
    //returns the minimum value in the tree

    Node* removeHelper(Node* root, Dress item);
    //recursive helper function for remove function,
    //removes the dress from the cart

public:

    /**Constructors and Destructor*/

    DressBST();
    //instantiates a new DressBST

    DressBST(const DressBST &DressBST);
    //copy constructor

    ~DressBST();
    //deallocates the tree memory of DressBST

    /**Access Functions*/

    void setUnique(bool u);
    //sets to check whether dresses are duplicated in store

    bool isEmpty() const;
    //determines whether the DressBST is empty,
    //used to be precondition for search and remove functions

    bool search(Dress item) const;
    //returns whether the dress is found in the cart,
    //used to be precondition for remove function
    //precondition: !isEmpty() or the cart is not empty

    Dress getRoot() const;
    //returns the value stored at the root of the BST
    //precondition: !isEmpty()

    Dress minimum() const;
    //returns minimum value of dresses in store

    /**Manipulation Procedures*/

    void insert(Dress item);
    //inserts a new dress into the cart

    void remove(Dress item);
    //removes the dress from the cart
    //precondition: search(item) or dress is located in the cart or DressBST
    //precondition: !isEmpty() or the cart is not empty

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to display dresses stored in the cart
    //or DressBST in order from the smallest to the largest

    void inOrderPrint2(ostream& out) const;
    //calls the inOrderPrint2 function to display dresses stored in the cart

    /**Additional Functions*/

    vector<Dress> getKeyItems(Dress key) const;
    //calls the getKeyItems function to get keys to print out later
};

template<typename Dress>
void DressBST<Dress>::getKeyItemsHelper(Node* root, Dress key, vector<Dress>* v) const
{
	if(root != NULL)
	{
		if(root->item == key)
		{
			v->push_back(root->item);
			getKeyItemsHelper(root->right, key, v);
		}
		else if(key < root->item)
		{
			getKeyItemsHelper(root->left, key, v);
		}
		else
		{
			getKeyItemsHelper(root->right, key, v);
		}
	}
}

template<typename Dress>
void DressBST<Dress>::insertHelper(Node* root, Dress item)
{
	if(root == NULL)
		return;
	if(isUnique && item == root->item)
		return;
	else if(item < root->item)
	{
		if(root->left == NULL)
			root->left = new Node(item);
		else
			insertHelper(root->left, item);
	}
	else
	{
		if(root->right == NULL)
			root->right = new Node(item);
		else
			insertHelper(root->right, item);
	}
}

template<typename Dress>
void DressBST<Dress>::inOrderPrintHelper(ostream& out, Node* root) const
{
	if(root != NULL)
	{
		inOrderPrintHelper(out, root->left);
		if(root->left != NULL && root->item.getKey() == "Brand")
		{
			if(root->item != root->left->item)
				out << endl;
		}
		out << root->item << endl;
		inOrderPrintHelper(out, root->right);
	}
}

template<typename Dress>
void DressBST<Dress>::inOrderPrintHelper2(ostream& out, Node* root) const
{
	if(root != NULL)
	{
		inOrderPrintHelper2(out, root->left);
		if(root->left != NULL && (root->item).getKey() == "Brand")
		{
			if(root->item != root->left->item)
			{
				out << setw(120) << setfill('=') << ">>  " + (root->item).getBrand() << endl;
			}
			(root->item).printDetails(out);
			inOrderPrintHelper2(out, root->right);
		}
	}
}

template<typename Dress>
void DressBST<Dress>::copyHelper(Node* copy)
{
    if(copy == NULL)
		return;
	else
	{
        insert(copy->item);
        copyHelper(copy->left);
		copyHelper(copy->right);
	}
}

template<typename Dress>
void DressBST<Dress>::destructorHelper(Node* root)
{
    if(root != NULL)
	{
		destructorHelper(root->left);
		destructorHelper(root->right);
		delete root;
	}
}

template<typename Dress>
bool DressBST<Dress>::searchHelper(Node* root, Dress item) const
{
	if(item == root->item)
		return true;
	else if(item < root->item)
	{
		if(root->left == NULL)
			return false;
		else
			return searchHelper(root->left, item);
	}
	else
	{
		if(root->right == NULL)
			return false;
		else
			return searchHelper(root->right, item);
	}
	return false;
}

template<typename Dress>
Dress DressBST<Dress>::minimumHelper(Node* root) const
{
	if(root->left != NULL)
		return minimumHelper(root->left);
	else
		return root->item;
}

template<typename Dress>
typename DressBST<Dress>::Node* DressBST<Dress>::removeHelper(Node* root, Dress item)
{
	if(root == NULL)
		return root;
	else if(item < root->item)
		root->left = removeHelper(root->left, item);
	else if(item > root->item || (item == root->item && !item.isSame(root->item)))
		root->right = removeHelper(root->right, item);
	else if(item.isSame(root->item))
	{
		if(root->left == NULL && root->right == NULL)
		{
			delete root;
			root = NULL;
		}
		else if(root->left != NULL && root->right == NULL)
		{
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		else if(root->left == NULL && root->right != NULL)
		{
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else
		{
			root->item = minimumHelper(root->right);
			root->right = removeHelper(root->right, minimumHelper(root->right));
        }
	}
	return root;
}

template<typename Dress>
DressBST<Dress>::DressBST()
{
	root = NULL;
	isUnique = true;
}

template<typename Dress>
DressBST<Dress>::DressBST(const DressBST &DressBST)
{
    copyHelper(DressBST.root);
    isUnique = DressBST.isUnique;
}

template<typename Dress>
DressBST<Dress>::~DressBST()
{
	destructorHelper(root);
}

template<typename Dress>
void DressBST<Dress>::setUnique(bool u)
{
	isUnique = u;
}

template<typename Dress>
bool DressBST<Dress>::isEmpty() const
{
	return (root == NULL);
}

template<typename Dress>
bool DressBST<Dress>::search(Dress item) const
{
	assert(!isEmpty());
	if(item == root->item)
		return true;
	else
		return searchHelper(root, item);
}

template<typename Dress>
Dress DressBST<Dress>::getRoot() const
{
	assert(!isEmpty());
	return root->item;
}

template<typename Dress>
Dress DressBST<Dress>::minimum() const
{
	assert(!isEmpty());
	return minimumHelper(root);
}

template<typename Dress>
void DressBST<Dress>::insert(Dress item)
{
	if(root == NULL)
		root = new Node(item);
	else
		insertHelper(root, item);
}

template<typename Dress>
void DressBST<Dress>::remove(Dress item)
{
	assert(!isEmpty());
	assert(search(item));
	if(item.isSame(getRoot()))
	{
		root = removeHelper(root, item);
	}
}

template<typename Dress>
void DressBST<Dress>::inOrderPrint(ostream& out) const
{
	inOrderPrintHelper(out, root);
}

template<typename Dress>
void DressBST<Dress>::inOrderPrint2(ostream& out) const
{
	if((root->item).getKey() == "Brand")
	{
		out << setw(120) << setfill('=') << minimum().getBrand() << endl;
	}
	inOrderPrintHelper2(out, root);
	out << endl;
}

template<typename Dress>
vector<Dress> DressBST<Dress>::getKeyItems(Dress key) const
{
	assert(search(key));
	vector<Dress> v;
	getKeyItemsHelper(root, key, &v);
	return v;
}

#endif /* DressBST_H_ */
