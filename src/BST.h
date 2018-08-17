#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>
#include <iostream>

using namespace std;
template<typename bstdata>
class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata){
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;
    bool isUnique;

    /**Private helper functions*/

    void insertHelper(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a value into the BST

    void inOrderPrintHelper(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void getKeyItemsHelper(Node* root, bstdata key, vector<bstdata>* v) const;

    void preOrderPrintHelper(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrintHelper(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyHelper(Node* copy);
    //recursive helper function to the copy constructor

    void destructorHelper(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchHelper(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the value is found in the tree

    bstdata minimumHelper(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximumHelper(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum value in the tree

    Node* removeHelper(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSizeHelper(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeightHelper(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

    void inOrderPrintHelper2(ostream& out, Node* root) const;

public:

    /**constructors and destructor*/

    void inOrderPrint2(ostream& out) const;

    void setUnique(bool u);
    // set whether or not the bst contain duplicates

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    /**access functions*/

    bstdata minimum() const;
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum value in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the value stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()

    /**manipulation procedures*/

    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified value from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()

    /**additional functions*/

    vector<bstdata> getKeyItems(bstdata key) const;

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the values
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the values
    //stored in the BST
};
#endif /* BST_H_ */

template<typename bstdata>
BST<bstdata>::BST(){
	root = NULL;
	isUnique = true;
}

template<typename bstdata>
bool BST<bstdata>::isEmpty() const{
	return (root==NULL);
}

template<typename bstdata>
bstdata BST<bstdata>::getRoot() const{
	assert(!isEmpty());
	return root->data;
}

template<typename bstdata>
void BST<bstdata>::insert(bstdata data){
	if(isEmpty()){
		root = new Node(data);
	}else{
		// call private helper for recursion
		insertHelper(root, data);
	}
}

template<typename bstdata>
void BST<bstdata>::insertHelper(Node* root, bstdata data){

	if(isUnique && data == root->data){return;}

	// if value is smaller or equal, go to left child
	if(data<root->data){
		if(root->left == NULL){
			root->left = new Node(data);
		}else{
			insertHelper(root->left, data);
		}
	}

	// if value is bigger, go to right child
	else{
		if(root->right == NULL){
			root->right = new Node(data);
		}else{
			insertHelper(root->right, data);
		}
	}
}

template<typename bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const{
	inOrderPrintHelper(out, root);
	out << endl;
}

template<typename bstdata>
void BST<bstdata>::inOrderPrintHelper(ostream& out, Node* root) const{
	// Left Print Right
	if(root != NULL)
	{
		inOrderPrintHelper(out, root->left);
		//(root->data).printDetails(out);
		if(root->left != NULL && (root->data).getKey()=="Brand"){
			if(!(root->data == root->left->data)){
				out << endl;
			}
		}
		out << root->data << endl;
		inOrderPrintHelper(out, root->right);
	}
}

template<typename bstdata>
void BST<bstdata>::inOrderPrint2(ostream& out) const{

	if((root->data).getKey()=="Brand"){
		out << setw(120) << setfill('=') << minimum().getBrand() << endl;
	}
	inOrderPrintHelper2(out, root);
	out << endl;
}

template<typename bstdata>
void BST<bstdata>::inOrderPrintHelper2(ostream& out, Node* root) const{
	// Left Print Right
	if(root != NULL)
	{
		inOrderPrintHelper2(out, root->left);
		if(root->left != NULL && (root->data).getKey()=="Brand"){
			if(!(root->data == root->left->data)){
				out << setw(120) << setfill('=') << ">>  " + (root->data).getBrand() << endl;
			}
		}
		(root->data).printDetails(out);
		inOrderPrintHelper2(out, root->right);
	}
}

template<typename bstdata>
void BST<bstdata>::preOrderPrint(ostream& out) const{
	preOrderPrintHelper(out, root);
	out << endl;
}

template<typename bstdata>
void BST<bstdata>::preOrderPrintHelper(ostream& out, Node* root) const{
	// Print Left Right
	if(root != NULL)
	{
		out << root->data << " ";
		preOrderPrintHelper(out, root->left);
		preOrderPrintHelper(out, root->right);
	}
}

template<typename bstdata>
void BST<bstdata>::postOrderPrint(ostream& out) const{
	postOrderPrintHelper(out, root);
}

template<typename bstdata>
void BST<bstdata>::postOrderPrintHelper(ostream& out, Node* root) const{
	// Left Right Print
	if(root != NULL)
	{
		postOrderPrintHelper(out, root->left);
		postOrderPrintHelper(out, root->right);
		(root->data).print(out);
	}
}

template<typename bstdata>
BST<bstdata>::~BST(){
	destructorHelper(root);
}

template<typename bstdata>
void BST<bstdata>::destructorHelper(Node* root){
	if(root!=NULL){
		destructorHelper(root->left);
		destructorHelper(root->right);
		delete root;
	}
}

template<typename bstdata>
BST<bstdata>::BST(const BST &bst){
	copyHelper(bst.root);
	isUnique = bst.isUnique;
}

template<typename bstdata>
void BST<bstdata>::copyHelper(Node* copy){
	// Insert Left Right, need to start from root
	if(copy!=NULL){
		insert(copy->data);
		copyHelper(copy->left);
		copyHelper(copy->right);
	}
}

template<typename bstdata>
bstdata BST<bstdata>::minimum() const{
	assert(!isEmpty());
	return minimumHelper(root);
}

template<typename bstdata>
bstdata BST<bstdata>::minimumHelper(Node* root) const{
	if(root->left!=NULL){
		return minimumHelper(root->left);
	}
	return root->data;
}

template<typename bstdata>
bstdata BST<bstdata>::maximum() const{
	assert(!isEmpty());
	return maximumHelper(root);
}

template<typename bstdata>
bstdata BST<bstdata>::maximumHelper(Node* root) const{
	if(root->right!=NULL){
		return maximumHelper(root->right);
	}
	return root->data;
}

template<typename bstdata>
int BST<bstdata>::getSize() const{
	int size=0;
	getSizeHelper(root, size);
	return size;
}

template<typename bstdata>
void BST<bstdata>::getSizeHelper(Node* root, int& size) const{
	if(root!=NULL){
		getSizeHelper(root->left, size);
		getSizeHelper(root->right, size);
		size++;
	}
}

template<typename bstdata>
bool BST<bstdata>::search(bstdata data) const{
	assert(!isEmpty());
	return searchHelper(root, data);
}

template<typename bstdata>
bool BST<bstdata>::searchHelper(Node* root, bstdata data) const{
	if(root!=NULL){
		if(root->data == data){
			return true;
		}else if(root->data < data){
			return searchHelper(root->right, data);
		}else{
			return searchHelper(root->left, data);
		}
	}
	return false;
}

template<typename bstdata>
void BST<bstdata>::remove(bstdata data){

	assert(search(data));

	Node* temp = root;

	// as the root node will be reassigned (if both roots are not NULL)
	if(data.isSame(getRoot()) && !(temp->left!=NULL && temp->right!=NULL)){

		// to assign the next root
		if(temp->left!=NULL){
			temp = temp->left;
		}else{
			temp = temp->right;			// if right is null then move root to null anyways
		}

	}
	removeHelper(root, data);
	root = temp;			// works even if root is not the one removed, as the initial value is root anyways
}

template <class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeHelper(Node* root, bstdata data){
	if(root==NULL){
		return root;
	}
	if(data < root->data){
		root->left = removeHelper(root->left, data);
	}else if(data > root->data || (data==root->data && !data.isSame(root->data))){
		root->right = removeHelper(root->right, data);
	}else if (data.isSame(root->data)){
		if(root->left == NULL && root->right == NULL){
			delete root;
			root = NULL;
		}else if(root->left == NULL && root->right != NULL){
			Node *temp = root;
			root = root->right;
			delete temp;
		}else if(root->left != NULL && root->right == NULL){
			Node *temp = root;
			root = root->left;
			delete temp;
		}else{
			root->data = minimumHelper(root->right);
			root->right = removeHelper(root->right, root->data);
		}
	}
	return root;
}

template<typename bstdata>
int BST<bstdata>::getHeight() const{
	return getHeightHelper(root);
}

template<typename bstdata>
int BST<bstdata>::getHeightHelper(Node* root) const{
	if(root == NULL){
		return -1;
	}
	if(getHeightHelper(root->left) < getHeightHelper(root->right)){
		return getHeightHelper(root->right) + 1;
	}else{
		return getHeightHelper(root->left) + 1;
	}
}

template<typename bstdata>
vector<bstdata> BST<bstdata>::getKeyItems(bstdata key) const{
	assert(search(key));
	vector<bstdata> v;
	getKeyItemsHelper(root, key, &v);
	return v;
}

template<typename bstdata>
void BST<bstdata>::getKeyItemsHelper(Node* root, bstdata key,vector<bstdata>* v) const{
	if(root!=NULL){
		if(root->data==key){v->push_back(root->data);getKeyItemsHelper(root->right, key,v);}
		else if(key<root->data){getKeyItemsHelper(root->left, key, v);}
		else{getKeyItemsHelper(root->right, key,v);}
	}
}

template<typename bstdata>
void BST<bstdata>::setUnique(bool u){
	isUnique = u;
}
