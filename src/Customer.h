#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <iostream>
#include <vector>
#include <iomanip>
#include "Order.h"

using namespace std;

class Customer {
private:
	string id;
	string password;
    string first_name;
    string last_name;
    string address;
    long long phoneNumber;
    vector<Order> orders;

public:

    Customer();
    Customer(string i, string pass, string f, string l, string a, long long p);
    Customer(Customer const &c);

    //access
    string getID();
    string getPass();
    string getFirst();
    string getLast();
    string getAddress();
    long long getPhone();
    vector<Order>* getOrders();
    Order* getCart();

    //manipulation
    void setFirst(string f);
    void setLast(string l);
    void setAddress(string a);
    void setPhone(long long p);
    void addOrder(Order o);
    void setID(string i);
    void setPass(string p);

    friend ostream& operator<<(ostream& os, const Customer& order);
    bool operator==(const Customer& c);
    bool isSame(const Customer& c);
    void show(ostream& out);
    void showAll(ostream& out);
    string getP(long long pN);

};


#endif /* CUSTOMER_H_ */

bool Customer::operator==(const Customer& c){
    return ((id==c.id));
}

bool Customer::isSame(const Customer& c){
	string s[4] = {first_name, c.first_name, last_name, c.last_name};

	for(int i=0;i<4; i++){
		for(int j=0; j<s[i].length(); j++){
			s[i][j] = tolower(s[i][j]);
		}
	}

    return ((s[0]==s[1]) && (s[2] == s[3]));
}

Customer::Customer(){
	id = "";
	password = "";
	first_name = "";
	last_name = "";
	address = "";
	phoneNumber = 0;
}

Customer::Customer(string i, string pass, string f, string l, string a, long long p){
	id = i;
	password = pass;
	first_name = f;
	last_name = l;
	address = a;
	phoneNumber = p;
}

Customer::Customer(Customer const &c){
	id = c.id;
	password = c.password;
	first_name = c.first_name;
	last_name = c.last_name;
	address = c.address;
	phoneNumber = c.phoneNumber;
	orders = c.orders;
}

vector<Order>* Customer::getOrders(){
	return &orders;
}

Order* Customer::getCart(){
	return &orders[orders.size()-1];
}

string Customer::getPass(){
	return password;
}

string Customer::getID(){
	return id;
}

string Customer::getFirst(){
	return first_name;
}

string Customer::getLast(){
	return last_name;
}

string Customer::getAddress(){
	return address;
}

long long Customer::getPhone(){
	return phoneNumber;
}

void Customer::setID(string i){
	id=i;
}

void Customer::setPass(string p){
	password = p;
}

void Customer::setFirst(string f){
	first_name = f;
}

void Customer::setLast(string l){
	last_name = l;
}

void Customer::setAddress(string a){
	address = a;
}

void Customer::setPhone(long long p){
	phoneNumber = p;
}

void Customer::addOrder(Order o){
	orders.push_back(o);
}

ostream& operator<<(ostream& os, const Customer& c){
	os << endl << endl << c.id << endl << c.password << endl << c.first_name << endl << c.last_name << endl << c.address << endl << c.phoneNumber << endl << c.orders.size() << endl;
	for(int i=0; i<c.orders.size(); i++){c.orders[i].print(os);}
	return os;
}

void Customer::show(ostream& out){

	out << "Name                : " << setfill(' ') << left << setw(33) << first_name + " " + last_name << endl
		<< "Email               : " << setfill(' ') << left << setw(33) << id << "Phone               : " << getP(phoneNumber) << endl;
	out << "Address             : " << address << endl;

}

void Customer::showAll(ostream& out){
	out << "Name                : " << setfill(' ') << left << setw(33) << first_name + " " + last_name << endl
		<< "Email               : " << setfill(' ') << left << setw(33) << id << "Phone               : " << getP(phoneNumber) << endl
		<< "Address             : " << address << "\n\n";
	for(int i=0; i<orders.size(); i++){out<<orders[i];}
	out << setw(110) << setfill('|') << "" << "\n";

}

string Customer::getP(long long pN){
	return ("(" + to_string(pN/10000000) + ") "+ to_string((pN/10000)%1000)  + "-" + to_string(pN%10000) );
}
