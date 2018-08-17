#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "List.h"
#include <iostream>
#include <assert.h>

using namespace std;

template <class hashdata>
class HashTable {
public:
    /**Constructors*/

    HashTable(){}
    //constructor

    ~HashTable(){}
    //destructor


    /**Access Functions*/

    int hash(string key) const;
    //returns the hash value for the given key
    //the hash value is the sum of
    //of the ASCII values of each char in the key
    //% the size the of the table
    //Key for this table: title + author

    int countBucket(int index) const;
    //counts the number of Dresss at this index
    //returns the count
    //pre: 0<= index < SIZE

    int search(hashdata d) const;
    //Searches for d in the table
    //returns the index at which d is located
    //returns -1 if d is not in the table

    /**Manipulation Procedures*/

    void insert(hashdata d);
    //inserts a new Dress into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(hashdata d);
    //removes d from the table
    //calls the hash function on the key to determine
    //the correct bucket
    //pre: d is in the table

    hashdata* get(hashdata d);

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;
    //Prints all the Dresss at index
    //pre: 0<= index < SIZE
    //Should print according to the following formula:
    //Prints each Dress at that index in the format:
    //<title> by <author>
    //$<X.XX>
    //ISBN#: <isbn>
    //followed by a blank line

    void printTable(ostream& out) const;
    //Prints the first Dress at each index
    //along with a count of the total Dresss
    //at each index by calling count_bucket
    //as a helper function
    //Prints in the format:
    //Dress in the Catalogue:
    //<new line>
    //Group <bucket>
    //<title> by <author>
    //$<X.XX>
    //ISBN: <isbn>
    //+<number of elements at this index> -1 more similar Dress(s)
    //<new line><new line><new line>

    int getSize();

    vector<hashdata> getAll(hashdata d);

    List<hashdata>* getBucket(int i);

private:
    static const int SIZE = 10;
    List<hashdata> Table[SIZE];
};

#endif /* HASHTABLE_H_ */

template <class hashdata>
int HashTable<hashdata>::getSize(){
    	return SIZE;
}

template <class hashdata>
int HashTable<hashdata>::hash(string key) const{
	int sum=0;
	for(int i=0; i<key.length();i++){sum+=(int)key[i];}
	return sum%SIZE;
}

template <class hashdata>
int HashTable<hashdata>::countBucket(int index) const{
	assert(index>=0 && index<SIZE);
	return Table[index].getLength();								// get length of bucket
}

template <class hashdata>
int HashTable<hashdata>::search(hashdata d) const{
	int h1=hash(d.getFirst()+d.getLast());
	if(countBucket(h1)==0 || Table[h1].linearSearch(d) == -1){return -1;}	// if index is empty or if the Dress is not found, use linear as not sorted
	return h1;															// return the hashed index if found
}

template <class hashdata>
void HashTable<hashdata>::insert(hashdata d){
	Table[hash(d.getFirst()+d.getLast())].insertStop(d);		// insert at back of list
}

template <class hashdata>
void HashTable<hashdata>::remove(hashdata d){
	int indexT = search(d);
	assert(indexT!=-1);												// if Dress not in table
	Table[indexT].moveToIndex(Table[indexT].linearSearch(d));			// move iterator to the Dress position in list, use linear as not sorted
	Table[indexT].removeIterator();									// remove the Dress pointed by iterator
}

template <class hashdata>
hashdata* HashTable<hashdata>::get(hashdata d){
	int indexT = search(d);
	assert(indexT!=-1);												// if Dress not in table
	Table[indexT].moveToIndex(Table[indexT].linearSearch(d));
	return Table[indexT].getIterator();
}

template <class hashdata>
vector<hashdata> HashTable<hashdata>::getAll(hashdata d){
	int indexT = hash(d.getFirst()+d.getLast());
	vector<hashdata> v;
	List<hashdata> c(Table[indexT]);
	if(c.isEmpty()){return v;}
	c.startIterator();
	while(!c.offEnd()){
		hashdata cus(*c.getIterator());
		if(cus.isSame(d)){v.push_back(cus);}
		c.moveIterNext();
	}
	return v;
}

template <class hashdata>
List<hashdata>* HashTable<hashdata>::getBucket(int i){
	return &Table[i];
}

template <class hashdata>
void HashTable<hashdata>::printBucket(ostream& out, int index) const{
	assert(index>=0 && index<SIZE);
	if(!(Table[index].isEmpty())){Table[index].displayList(cout);} // display the list (bucket) at index
}

template <class hashdata>
void HashTable<hashdata>::printTable(ostream& out) const{
	for(int i=0; i<SIZE; i++){
		if(countBucket(i)!=0){
			out << "Group " << i+1 << "\n" << Table[i].getStart() << "\n+" << countBucket(i)-1 << " more Customer(s)\n\n\n";
		}
	}
}

