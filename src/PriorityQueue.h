#ifndef PriorityQueue_H_
#define PriorityQueue_H_

#include <vector>
#include <iostream>
#include <cmath>
#include <assert.h>
#include <utility>
using namespace std;

template <class PriorityQueuedata>
class PriorityQueue {
private:
    int priorityQueue_size;
    vector<PriorityQueuedata> *priorityQueue;
    // we use pointers as we want to make it as efficient as possible for orders to be both in the
    // List of orders a customer has and the Priority Queue (such as changing the state of the order from confirmed
    // to shipped)

    /**Helper Functions*/

    void heapify(int i);
    //helper function to build_PriorityQueue, remove, and sort
    //bubbles an element down to its proper location within the PriorityQueue

    void PriorityQueue_increase_key(int i, PriorityQueuedata key);
    //helper function to insert
    //bubbles an element up to its proper location

public:

    /**Constructors*/

    PriorityQueue(vector<PriorityQueuedata> &v);
    //assigns PriorityQueue to point to v, an unordered array of pointers
    //calls build_PriorityQueue to convert the unordered array into a valid max PriorityQueue (arranged by the values
    //that the pointer is pointing to

    /**Manipulation Procedures*/

    void build_PriorityQueue();
    //Takes an unordered vector and builds it into a PriorityQueue
    //Called as a helper function of the constructor
    //Calls heapify as a helper function

    void insert(PriorityQueuedata value);
    //Inserts a new pointer to a value onto the end of the PriorityQueue and
    //Bubbles it up to the correct location in the PriorityQueue
    //Calls PriorityQueue_increase_key as a helper function

    void remove(int index);
    //removes the node at the provided index of the PriorityQueue
    //pre: 1 <= i <= get_size()


    int search(PriorityQueuedata d);

    vector<PriorityQueuedata> sort();
    //sorts a PriorityQueue into ascending order of values being pointed
    //returns the sorted array of values (not pointer)
    //post: PriorityQueue restored to max PriorityQueue
    //calls build PriorityQueue as a helper function
    //calls heapify as a helper function

    /**Access Functions*/

    PriorityQueuedata get_max() const;
    //returns the pointer to maximum value in the PriorityQueue
    //pre: priorityQueue_size > 0

    int get_parent(int i) const;
    //returns the location (index) of the element stored at index i
    //pre: 0 < i <= priorityQueue_size

    int get_left(int i)  const;
    //returns the location (index) of the left child of the element stored at i
    //pre: 0 < i <= priorityQueue_size

    int get_right(int i)  const;
    //returns the location (index) of the right child of the element stored at i
    //pre: 0 < i <= priorityQueue_size

    int get_size() const;
    //returns the priorityQueue_size (current number of elements

    PriorityQueuedata get_element(int i) const;
    //returns the pointer at the specified index i
    //pre: 0 < i <= priorityQueue_size

    /**Additional Operations*/

    void displayPriorityQueue(ostream& out) const;
    //prints the PriorityQueue in level order
    //Hint: level = floor(log2(i) + 1)

    void displayArray(ostream& out) const;
    //prints each element in the array (PriorityQueue) separated by a comma

};

#endif /* PriorityQueue_H_ */

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::heapify(int i){
	int left = get_left(i), right = get_right(i), maxI = i;
	if(left<=priorityQueue_size && get_element(left) > get_element(i)){
		maxI=left;
	}
	if(right<=priorityQueue_size && get_element(right) > get_element(maxI)){
		maxI=right;
	}
	if(i!=maxI){
		swap(priorityQueue->at(i),priorityQueue->at(maxI));
		heapify(maxI);
	}
}

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::PriorityQueue_increase_key(int i, PriorityQueuedata key){
	int parent = get_parent(i);
	if(i>=2 && get_element(parent) < key){
		swap(priorityQueue->at(i),priorityQueue->at(parent));
		PriorityQueue_increase_key(parent, key);
	}
}

/**Constructors*/

template <class PriorityQueuedata>
PriorityQueue<PriorityQueuedata>::PriorityQueue(vector<PriorityQueuedata> &v){
	priorityQueue_size = v.size()-1;
	priorityQueue = &v;
	build_PriorityQueue();
}

/**Manipulation Procedures*/

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::build_PriorityQueue(){
	for(int n=priorityQueue_size/2; n>=1; n--){		// integer division
		heapify(n);
	}
}

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::insert(PriorityQueuedata value){
	priorityQueue->push_back(value);
	priorityQueue_size++;
	PriorityQueue_increase_key(priorityQueue_size,value);
}

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::remove(int index){
	assert(1<=index && index<= get_size());
	swap(priorityQueue->at(index),priorityQueue->at(priorityQueue_size));
	priorityQueue->pop_back();
	priorityQueue_size--;
	if(index<=priorityQueue_size){heapify(index);}
}

template <class PriorityQueuedata>
vector<PriorityQueuedata> PriorityQueue<PriorityQueuedata>::sort(){
	vector<PriorityQueuedata> v;
	int size = priorityQueue_size;

	while(priorityQueue_size>1){
		v.push_back(get_max());
		swap(priorityQueue->at(1),priorityQueue->at(priorityQueue_size));
		priorityQueue_size--;		// make these elements "invisible"
		heapify(1);
	}
	v.push_back(get_max());

	priorityQueue_size = size;
	build_PriorityQueue();

	return v;
}

/**Access Functions*/

template <class PriorityQueuedata>
PriorityQueuedata PriorityQueue<PriorityQueuedata>::get_max() const{
	assert(priorityQueue_size>0);
	return priorityQueue->at(1);
}

template <class PriorityQueuedata>
int PriorityQueue<PriorityQueuedata>::get_parent(int i) const{
	assert(0<i && i<=priorityQueue_size);
	return i/2;
}

template <class PriorityQueuedata>
int PriorityQueue<PriorityQueuedata>::get_left(int i)  const{
	assert(0<i && i<=priorityQueue_size);
	return i*2;
}

template <class PriorityQueuedata>
int PriorityQueue<PriorityQueuedata>::get_right(int i)  const{
	assert(0<i && i<=priorityQueue_size);
	return i*2+1;
}

template <class PriorityQueuedata>
int PriorityQueue<PriorityQueuedata>::get_size() const{
	return priorityQueue_size;
}

template <class PriorityQueuedata>
PriorityQueuedata PriorityQueue<PriorityQueuedata>::get_element(int i) const{
	assert(0<i && i<=priorityQueue_size);
	return priorityQueue->at(i);
}

/**Additional Operations*/

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::displayPriorityQueue(ostream& out) const{
	int level = 0;
	for(int i=1; i<=priorityQueue_size; i++){
		if(floor(log2(i)+1)!=level){
			level++;
			out << "*************************************** Level " << level << " ***************************************" << endl;
		}
		out << (priorityQueue->at(i));

	}
	out << endl;
}

template <class PriorityQueuedata>
void PriorityQueue<PriorityQueuedata>::displayArray(ostream& out) const{
	for(int i=1; i<=priorityQueue_size; i++){
		out << (priorityQueue->at(i)) << endl;
	}
	out << endl;
}

template <class PriorityQueuedata>
int PriorityQueue<PriorityQueuedata>::search(PriorityQueuedata d){
	for(int i=1; i<=priorityQueue_size; i++){
		if(priorityQueue->at(i)==d){return i;}
	}
	return -1;
}
