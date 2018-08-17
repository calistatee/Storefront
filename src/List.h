#ifndef LIST_H_
#define LIST_H_

#include <cstddef> //for NULL
#include <assert.h>
#include <iostream>
#include <iomanip>
using namespace std;

template <class listdata> //list stores generic listdata, not any specific C++ type
class List {

private:
    struct Node {
        listdata data;
        Node* next;
        Node* previous;

        Node(listdata newData){
            data = newData;
            next = NULL;
            previous = NULL;
        }
    };

    Node* start;
    Node* stop;
    Node* iterator;
    int length;

    void displayReverse(Node* node, ostream& out) const;
	//Helper function for the public displayReverse wrapper function.
	//Recursively prints the data in a List in reverse.

    bool isSorted(Node* node) const;
	//Helper function for the public isSorted() function.
	//Recursively determines whether a list is sorted in ascending order.

    int binarySearch(int low, int high, listdata data) const;
    //Recursively search the list by dividing the search space in half
    //Returns the index of the element, if it is found in the List
    //Returns -1 if the element is not in the List
    //Post: The iterator location has not been changed

public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: List is made, contents are empty

    List(List const &list);
    //Copy constructor; copies an existing list into a new list
    //Postcondition: Copy of an existing list is made

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: List is destroyed, data in list also destroyed, list no longer exists

    /**Accessors*/

    listdata getStart() const;
    //Returns the data at the start of the list
    //Precondition: List is not empty

    listdata getStop() const;
    //Returns the data at the end of the list
    //Precondition: List is not empty

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    listdata* getIterator() const;
    //Returns the data at the iterator
    //Precondition: iterator not pointing to NULL

    bool offEnd() const;
    //Determines whether an iterator points to NULL

    bool operator==(const List &list);
    //Tests two lists to determine whether their contents are equal
	//Postcondition: returns true if lists are equal and false otherwise

    bool isSorted() const;
	//Wrapper function that calls the isSorted helper function to determine whether
	//a list is sorted in ascending order.
	//We will consider that a list is trivially sorted if it is empty.
	//Therefore, no precondition is needed for this function

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Iteratively searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed

    /**Manipulation Procedures*/

    void operator=(const List<listdata> &list);
	// Copies a List and assigns it to another variable
	// Used to copy list of dresses into copy of an order (used when creating sorted Order from the priority queue


    void removeStart();
    //Removes the value stored in first node in the list
    //Precondition: List is not empty
    //Postcondition: The first node is changed to the previous second node (start points at ex-second node)

    void removeStop();
    //Removes the value stored in the last node in the list
    //Precondition: List is not empty
    //Postcondition: The ex-last node does not exist anymore, stop moves to the ex-second to last

    void insertStart (listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both start and stop
    //Postcondition: The first node is now the new node (start points at new node, and it points at ex-start node)

    void insertStop(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both start and stop
    //Postcondition: The last node is now the new node (stop points at new node, and ex-stop node points to new node)

    void startIterator();
    //Moves the iterator to the start of the list
    //Precondition: List is not empty
    //Postcondition: Iterator points at start

    void removeIterator();
    //removes the element currently pointed to by the iterator. Iterator then points to NULL.
    //Precondition: Iterator not pointing to NULL (if not NULL then list is not empty)
    //Postcondition: element pointed by iterator does not exist, previous node points to next node, vise versa

    void insertIterator(listdata data);
    //Inserts a new data after the iterator
	//Postcondition: The node after the iterator is the new node

    void moveIterNext();
    //Moves the iterator to the next node
    //Precondition: iterator is not NULL
    //Postcondition: Iterator points at next node

    void moveIterPrevious();
    //Moves the iterator to the previous node
	//Precondition: iterator is not NULL
	//Postcondition: Iterator points at previous node

    void moveToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size


    /**Additional List Operations*/

    void displayList(ostream& out) const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..

    void displayNumberedList(ostream& out) const;
    //Prints to the console the value of each data in the list sequentially
	//and separated by a newline in the format #: data
	//Prints nothing if the list is empty
	//Prints a empty newline character if it's empty..

    void displayReverse(ostream& out) const;
	//Wrapper function that calls the private displayReverse helper function to print a list in reverse
	//prints nothing if the List is empty

    void displayListData(ostream& out) const;
};
#endif /* LIST_H_ */

template <class listdata>
List<listdata>::List() {
	start = stop = iterator = NULL;
    length = 0;
}

template <class listdata>
List<listdata>::List(List<listdata> const &list){

	if(list.start == NULL) //If the original list is empty, make an empty list for this list
	{
		start = stop = iterator = NULL;
	}
	else
	{
		start = new Node(list.start->data); //calling Node constructor
		Node* temp = list.start; //set a temporary node pointer to point at the start of the original list
		iterator = start; //set iterator to point to the start node of the new list

		while(temp->next != NULL)
		{

			temp = temp->next; //advance up to the next node in the original list
			iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
			(iterator->next)->previous = iterator;
			iterator = iterator->next; //advance to this new node

		}

		stop = iterator;
		iterator = NULL;

	}

	length = list.length;
}

template <class listdata>
List<listdata>::~List(){
	if(length!=0){
		startIterator();
		moveIterNext();
		while (!offEnd())
		{
			delete iterator->previous;
			moveIterNext();
		}
		delete stop;
	}
}


template <class listdata>
listdata List<listdata>::getStart() const
{
	assert(!isEmpty());
    return start -> data;
}

template <class listdata>
listdata List<listdata>::getStop() const
{
	assert(!isEmpty());
    return stop -> data;
}

template <class listdata>
bool List<listdata>::isEmpty() const
{
    return length == 0;
}

template <class listdata>
int List<listdata>::getLength() const
{
    return length;
}

template <class listdata>
listdata* List<listdata>::getIterator() const{
	assert(!offEnd());
	return &(iterator->data);
}

template <class listdata>
bool List<listdata>::offEnd() const{
	return iterator==NULL;
}

template <class listdata>
bool List<listdata>::operator==(const List &list){
	if(length != list.length)
		return false;
	Node* temp1 = start;			// I don't use iterator as there's a possibility that it's being used
	Node* temp2 = list.start;
	while(temp1 != NULL)
	{
		if(temp1->data != temp2->data)
			return false;
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return true;
}

template <class listdata>
void List<listdata>::removeStart()
{
	assert(!isEmpty());
    if(length == 1)
    {
        delete start;
        start = stop = NULL;
    }
    else
    {
        start = start->next;
        delete start->previous;
        start->previous = NULL;
    }
    length--;
}

template <class listdata>
void List<listdata>::removeStop()
{
	assert(!isEmpty());
	if(length == 1)
    {
        delete start;
        start = stop = NULL;
    }
    else
    {
    	stop = stop->previous;
    	delete stop->next;
    	stop->next = NULL;
      }
	length--;
}

template <class listdata>
void List<listdata>::insertStart(listdata data)
{
    Node* N = new Node(data);
    if (length == 0)
    {
        start = N;
        stop = N;
    }
    else
    {
        N->next = start;
        start->previous = N;
        start = N;
    }
    length++;
}

template <class listdata>
void List<listdata>::insertStop(listdata data)
{
    Node* N = new Node(data);
    if (length == 0)
    {
        start = stop = N;
    }
    else
    {
    	N->previous = stop;
        stop->next = N;
        stop = N;
    }
    length++;
}

template <class listdata>
void List<listdata>::startIterator(){
	assert(!isEmpty());
	iterator = start;
}

template <class listdata>
void List<listdata>::removeIterator(){
	assert(!offEnd());
	if(iterator == start){
		removeStart();
	}
	else if(iterator == stop){
		removeStop();
	}
	else{
		(iterator->previous)->next = iterator->next;
		(iterator->next)->previous = iterator->previous;
		delete iterator;
		length--;
	}
	iterator = NULL;
}

template <class listdata>
void List<listdata>::insertIterator(listdata data){
	assert(!offEnd());
	if(iterator==stop){
		insertStop(data);
	}
	else
	{
		Node* N = new Node(data);
		N->next = iterator->next;
		(iterator->next)->previous = N;
		iterator->next = N;
		N->previous = iterator;
		length++;
	}
}

template<class listdata>
void List<listdata>::moveIterNext(){
	assert(!offEnd());
	iterator = iterator->next;
}

template <class listdata>
void List<listdata>::moveIterPrevious(){
	assert(!offEnd());
	iterator = iterator->previous;
}

template <class listdata>
void List<listdata>::displayList(ostream& out) const
{
    Node* temp = start; //create a temporary iterator, I don't use iterator as it may be in use
    while (temp != NULL) {

        //Add two lines of code here
    	(temp->data).showAll(out);
    	temp = temp->next;
        //Hint: One statement should contain a cout

    }

}

template <class listdata>
void List<listdata>::displayListData(ostream& out) const
{
    Node* temp = start; //create a temporary iterator, I don't use iterator as it may be in use
    while (temp != NULL) {

        //Add two lines of code here
    	out << temp->data;
    	temp = temp->next;
        //Hint: One statement should contain a cout

    }

}

template <class listdata>
void List<listdata>::displayNumberedList(ostream& out) const{
	Node* temp = start; //create a temporary iterator, I don't use iterator as it may be in use
	for (int counter=1; counter<=length; counter++) {
		out << counter << ": " << temp->data << endl;
		temp = temp->next;
	}
	out << endl;
}

template <class listdata>
void List<listdata>::displayReverse(ostream& out) const{
	displayReverse(stop,out);
}

template <class listdata>
void List<listdata>::displayReverse(Node* node, ostream& out) const{
	if(node!=NULL){
		out << node->data << " ";
		displayReverse(node->previous, out);
	}
}

template <class listdata>
bool List<listdata>::isSorted() const{
	return isSorted(start);
}

template <class listdata>
bool List<listdata>::isSorted(Node* node) const{
	if(node!=stop){
		if(node->data > node->next->data){
			return false;
		}
		isSorted(node->next);
	}
	return true;
}

template <class listdata>
int List<listdata>::getIndex() const{
	assert(!offEnd());
	int index=0;
	Node* temp = iterator;
	while(temp!=NULL){
		temp = temp->previous;
		index++;
	}
	return index;
}

template <class listdata>
void List<listdata>::moveToIndex(int index){
	assert(!isEmpty() && index<=length);
	startIterator();
	for(int i=1; i<index; i++){
		moveIterNext();
	}
}

template <class listdata>
int List<listdata>::linearSearch(listdata data) const{
	assert(!isEmpty());
	Node * temp = start;
	int i=1;
	while(temp!=NULL){
		if(temp->data==data){
			return i;
		}
		temp = temp->next;
		i++;
	}
	return -1;
}

template <class listdata>
int List<listdata>::binarySearch(listdata data) const{
	assert(!isEmpty() && isSorted());
	return binarySearch(1,length,data);
}

template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const{
	if(low>high){
		return -1;
	}
	Node* temp = start;
	int mid = low+((high-low)/2);
	for(int i=1; i<mid; i++){
		temp = temp->next;
	}
	if(temp->data==data){
		return mid;
	}else if(temp->data<data){
		return binarySearch(mid+1,high,data);
	}else{
		return binarySearch(low,mid-1,data);
	}
}

template <class listdata>
void List<listdata>::operator=(const List<listdata> &list){
	if(list.start == NULL) //If the original list is empty, make an empty list for this list
		{
			start = stop = iterator = NULL;
		}
		else
		{
			start = new Node(list.start->data); //calling Node constructor
			Node* temp = list.start; //set a temporary node pointer to point at the start of the original list
			iterator = start; //set iterator to point to the start node of the new list

			while(temp->next != NULL)
			{

				temp = temp->next; //advance up to the next node in the original list
				iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
				(iterator->next)->previous = iterator;
				iterator = iterator->next; //advance to this new node

			}

			stop = iterator;
			iterator = NULL;

		}

		length = list.length;

}
