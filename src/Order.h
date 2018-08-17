#ifndef ORDER_H_
#define ORDER_H_

//#include "Dress.h"
//#include "List.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <ctime>

using namespace std;

const string month[]={"-","January","February","March","April","May","June","July","August","September","October","November","December"};
const string speed[]={"Overnight","Rush","Standard"};
const string stt[]={"Cart", "Confirmed", "Shipped"};
const int s[] = {1,3,10};

class Order{
private:
	unsigned id;
	unsigned dateOrdered;		// YYYYMMDD
	int shippingSpeed;
	unsigned dateToShip;
	enum State {CART, CONFIRMED, SHIPPED} state;
	string customer;
	string fname;
	string lname;
	vector<Dress> itemsOrdered;
	double totalPrice;

public:

	/** Constructors*/

	Order();

	Order(unsigned i, unsigned d, int ss, int sp, string c, string f, string l);

	Order(unsigned* i,string c, string f, string l);
	/* When a new customer is registered, they will be assigned an Order with state cart, where they can temporarily store orders. */

	Order(Order const &order);
	// Copy constructor
	/* When an order is confirmed, state change to confirmed and order is inserted into Heap */

	// Manipulation Procedures
	void setID(unsigned i);
	void confirmOrder();
	void setShippingSpeed(int s);
	void setState(int s);
	void setCustomer(string c);
	void updateShipDate();
	void addDress(Dress d);
	void removeDress(Dress d);
	void setFname(string f);
	void setLname(string l);

	// Access Functions
	unsigned getID() const;
	unsigned getDateOrdered() const;
	int getShippingSpeed() const;
	int getState() const;
	string getCustomer() const;
	unsigned getDateToShip() const;
	vector<Dress> getItemsOrdered() const;
	string getFname() const;
	string getLname() const;
	double getPrice() const;


	/**Additional Functions*/
	friend ostream& operator<<(ostream& os, const Order& order);
	//prints out an order to the designated stream in the following format
	//Order #<id>
	//Date Ordered        : <date>                    Shipping Speed      : <shippingSpeed>
	//Customer ID     	  : <c.id>
	//Shipping Address    : <c.address()>
	//Ordered Item(s)     : <itemsOrdered with size and ID>

	bool operator==(const Order& order);
	//compares two orders to determine if they are the same dateToShip

	bool operator<(const Order& order);
	//compares two orders to determine if one has lower dateToShip than the other
	//by using date and shipping speed
	//returns false if the two orders are the same dateToShip

	bool operator>(const Order& order);
	//compares two orders to determine if one has higher dateToShip than the other
	//by using date and shipping speed
	//returns false if the two orders are the same dateToShip

	void print(ostream& out) const;

};



#endif /* ORDER_H_ */

Order::Order(){
	id = 0;
	dateOrdered = 0;
	shippingSpeed = 0;
	state = State(0);
	customer= "";
	dateToShip = 0;
	fname = "";
	lname = "";
	totalPrice = 0;
}

Order::Order(unsigned i, unsigned d, int ss, int sp, string c, string f, string l){
	id = i;
	dateOrdered = d;
	shippingSpeed = ss;
	state = State(sp);
	customer=c;
	dateToShip = dateOrdered+s[shippingSpeed];
	fname = f;
	lname = l;
	totalPrice = 0;
}

Order::Order(unsigned* i,string c, string f, string l){
	*i += 1;
	id = *i;
	dateOrdered = 0;
	shippingSpeed = 0;
	state = CART;
	customer=c;
	dateToShip = dateOrdered+s[shippingSpeed];
	fname = f;
	lname = l;
	totalPrice = 0;
}

Order::Order(Order const &order){
	id = order.id;
	dateOrdered = order.dateOrdered;
	shippingSpeed = order.shippingSpeed;
	state = order.state;
	customer = order.customer;
	dateToShip = order.dateToShip;
	itemsOrdered = order.itemsOrdered;
	fname = order.fname;
	lname = order.lname;
	totalPrice = order.totalPrice;
}

void Order::setID(unsigned i){
	id = i;
}

void Order::confirmOrder(){
	if(state!=CART){
		cout << "ERROR: Not a cart" << endl;
	}
	else if(!(itemsOrdered.size()==0)){
		time_t tt;
		time( &tt );
		tm TM = *localtime( &tt );
		dateOrdered    = (TM.tm_year + 1900)*10000 + (TM.tm_mon + 1)*100 + TM.tm_mday;
		state = CONFIRMED;
		updateShipDate();
	}else{
		cout << "ERROR: Cart is empty" << endl;
	}

}

void Order::setShippingSpeed(int s){
	shippingSpeed = s;
	updateShipDate();
}

void Order::setState(int s){
	state = State(s);
}

void Order::setCustomer(string c){
	customer = c;
}

void Order::setFname(string f){
	fname = f;
}

void Order::setLname(string l){
	lname = l;
}

void Order::addDress(Dress d){
	itemsOrdered.push_back(d);
	totalPrice += d.getPrice();
}

void Order::removeDress(Dress d){
	for(int i=0; i<itemsOrdered.size(); i++){
		if(d.isSame(itemsOrdered[i])){
			totalPrice -= itemsOrdered[i].getPrice();
			itemsOrdered.erase(itemsOrdered.begin()+i);
			return;
		}
	}
}

void Order::updateShipDate(){
	dateToShip = dateOrdered+s[shippingSpeed];
}

unsigned Order::getID() const{
	return id;
}

double Order::getPrice() const{
	return totalPrice;
}

unsigned Order::getDateOrdered() const{
	return dateOrdered;
}

int Order::getShippingSpeed() const{
	return shippingSpeed;
}

int Order::getState() const{
	return state;
}

string Order::getCustomer() const{
	return customer;
}

string Order::getFname() const{
	return fname;
}

string Order::getLname() const{
	return lname;
}

unsigned Order::getDateToShip() const{
	return dateToShip;
}

vector<Dress> Order::getItemsOrdered() const{
	return itemsOrdered;
}

ostream& operator<<(ostream& os, const Order& order){
	os << setw(47) << setfill('-') << "" << " Order #" << setfill('0') << setw(7) << right << order.id << setw(47) << left << setfill('-') << " "<< endl
	   << "State               : " << setfill(' ') << left << setw(33) << stt[order.state];
	if(order.state!=0){
	   os << "Expected Arrival    : " << month[(order.dateToShip/100)%100] + " " + to_string(order.dateToShip%100) + ", " + to_string(order.dateToShip/10000);
	   os << "\nDate Ordered        : " << setfill(' ') << left << setw(33) << month[(order.dateOrdered/100)%100] + " " + to_string(order.dateOrdered%100) + ", " + to_string(order.dateOrdered/10000) << "Shipping Speed      : " << speed[order.shippingSpeed];
	}
	   os << "\n<Item(s) Ordered>";
	for(int i=0; i< order.itemsOrdered.size(); i++){
		Dress d = order.itemsOrdered[i];
		int cs = d.getChosenSize();
		os  << endl << i+1 << ". " <<  d << " || Size: " <<  cs;
	}
	os << fixed << setprecision(2) << endl << "TOTAL PRICE: $" << order.totalPrice << endl;
	return os;
}

bool Order::operator==(const Order& order){
	return (id==order.id);
}

bool Order::operator>(const Order& order){
	if(dateToShip==order.dateToShip){
		return (shippingSpeed<order.shippingSpeed);		// if same, then look at shipping speed
	}
	return (dateToShip<order.dateToShip);		// higher priority means 'lower' or sooner ship date
}

bool Order::operator<(const Order& order){
	if(dateToShip==order.dateToShip){
		return (shippingSpeed>order.shippingSpeed);		// if same, then look at shipping speed
	}
	return (dateToShip>order.dateToShip);		// lower priority means 'higher' or later ship date
}

void Order::print(ostream& out) const{
	out << id << endl << dateOrdered << endl << shippingSpeed << endl << state << endl << itemsOrdered.size() << endl;
	for(int i=0; i< itemsOrdered.size(); i++){
		Dress d = itemsOrdered[i];
		out << d.getID() << " " << d.getChosenSize() << endl;
	}
}
