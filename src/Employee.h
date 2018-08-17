#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>

using namespace std;

class Employee {
private:
	string firstName;
	string lastName;
	string password;
	int ID;

public:

	//access functions
	string getFirstName();
	string getLastName();
	string getPassword();
	int getID();

	//manipulation
	void setFirstName(string f);
	void setLastName(string l);
	void setPassword(string p);
	void setID(int i);

};



#endif /* EMPLOYEE_H_ */

string Employee::getFirstName(){
	return firstName;
}

string Employee::getLastName(){
	return lastName;
}

string Employee::getPassword(){
	return password;
}

int Employee::getID(){
	return ID;
}

void Employee::setFirstName(string f){
	firstName = f;
}

void Employee::setLastName(string l){
	lastName = l;
}

void Employee::setPassword(string p){
	password = p;
}

void Employee::setID(int i){
	ID = i;
}
