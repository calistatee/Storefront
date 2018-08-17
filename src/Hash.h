#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#include "List.h"
#include "Dress.h"
#include "Employee.h"
#include <iostream>
#include <assert.h>
using namespace std;

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
    //counts the number of Dresses at this index
    //returns the count
    //pre: 0<= index < SIZE

    int search(Dress b) const;
    //Searches for b in the table
    //returns the index at which b is located
    //returns -1 if b is not in the table

    /**Manipulation Procedures*/

    void insert(Dress b);
    //inserts a new dress into the table
    //calls the hash function on the key to determine
    //the correct bucket

    void remove(Dress b);
    //removes b from the table
    //calls the hash function on the key to determine
    //the correct bucket
    //pre: b is in the table

    /**Additional Functions*/

    void printBucket(ostream& out, int index) const;
    //Prints all the dress at index
    //pre: 0<= index < SIZE
    //Should print according to the following formula:
    //Prints each dress at that index in the format:
    //<Dress ID>
    //<Dress Name>
    //<Dress Brand>
    //$<XX.XX>
    //followed by a blank line

    void printTable(ostream& out) const;
    //Prints the first dress at each index
    //along with a count of the total dress
    //at each index by calling count_bucket
    //as a helper function
    //Prints in the format:
    //Dress in the Catalogue:
    //<new line>
    //Group <bucket>
    //<Dress ID>
    //<Dress Name>
    //<Dress Brand>
    //$<XX.XX>
    //+<number of elements at this index> -1 more similar dress(es)
    //<new line><new line><new line>

private:
    static const int SIZE = 10;
    List<Dress> Table[SIZE];
};

#endif /* HASHTABLE_H_ */
