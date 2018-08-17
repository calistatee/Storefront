/*
 *	MAIN STORE FRONT
 *
 *	Combines all classes and data structures to build a online storefront
 *
 *	Team 5
 *
*/

#include "Dress.h"
#include "Customer.h"
#include "Employee.h"
#include "BST.h"				//Data Structure- For Dresses
#include "PriorityQueue.h"		//Data Structure- For Orders
#include "HashTable.h"			//Data Structure- For Customers
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cstddef>

using namespace std;

// Function Prototypes

void readInFile(const string filename, BST<Dress>  *bstID, BST<Dress> *bstBrand, vector<string>* brands);
	// Read into dressInput.txt and retrieve dress info to store into a vector
	// Two BST passed to populate with Dress objects
void loadCustomerOrderData(string f, unsigned* orderID, HashTable<Customer>* customers, vector<Order>* ords, BST<Dress>* b, vector<Dress>* r);
	// fills the customer HashTable and order PriorityQueue
bool empFound(vector<string> v[], string empID, string empPass);
	// Checks if employee ID is valid/ found in database of employees

void employee(BST<Dress> * byID, BST<Dress> * byBrand, PriorityQueue<Order>* ords, HashTable<Customer>* customers, vector<Dress>* r, vector<string>* brands, bool* cont);
	// Interface for Employee after Welcome screen
void displayEmployeeMenu();
	// displays all menu options for employees
void searchCustomer(HashTable<Customer>* cust);
	// Employee enters Customer's first and last name
	// Searches Customer Hash Table
	// Displays Customer information
void displayUnsorted(HashTable<Customer>* customers);
	//Uses Customer class and Hash to print all Customers
void viewOrdersPriority(PriorityQueue<Order>* ord, HashTable<Customer>* customers);
	//Uses Heap and Order class to retrieve all orders placed
void shipOrder(HashTable<Customer>* customers, PriorityQueue<Order>* ords);
	// Removes Order from Priority Queue
	// Changes Customer Order status to "Shipped"
void addDress(BST<Dress> * byID, BST<Dress> * byBrand, vector<string>* brands);
	// Adds a dress to both BSTs
void removeDress(BST<Dress> * byID, BST<Dress> * byBrand, HashTable<Customer> * customers, vector<Dress>* r, vector<string>* brands);
	// Removes a dress from both BSTs and
	// removes the dress from all cart orders

void customer(BST<Dress>  *byID, BST<Dress> *byBrand, PriorityQueue<Order>* orders, HashTable<Customer> * customers, unsigned* orderID, vector<string>* brands, bool* cont);
	// Interface for Customer after Welcome screen
void displayCustomerMenu(Customer** c);
	// displays all menu options for customer
void listAllDresses(BST<Dress> * byID, BST<Dress> * byBrand);
	// Uses BST and Dress class to print
	// Uses inOrderPrint and other Dress display options
void searchForDress(BST<Dress>  *byID, BST<Dress> *byBrand, Customer ** c, HashTable<Customer>* customers, unsigned* orderID, vector<string>* brands);
bool custFound(string id, Customer** c, HashTable<Customer>* customers);
void customerLogin(Customer** c, HashTable<Customer>* customers, unsigned* orderID);
void viewPastPurchases(Customer** c);
void placeOrder(Customer** c, PriorityQueue<Order>* orders, unsigned* orderID);
void newCustomer(Customer** c, HashTable<Customer>* customers, unsigned* orderID);
void viewCart(Customer** c, PriorityQueue<Order>* orders, unsigned* orderID);
void removeDress(Order* o);
void chooseAction(Customer** c, HashTable<Customer>* customers, unsigned* orderID, Dress* d, BST<Dress>  *byID, BST<Dress> *byBrand);
void readInRemoved(string removedFile, vector<Dress>* r);
void displayAboutPage();
bool errorCheck(string userInput, int numOfOptions);
	// Used for any screen that displays number of options for user
	// Accepts a numOfOption parameter to determine range

void saveFile(BST<Dress>  *byID, HashTable<Customer>* customers, unsigned* orderID, string customerFile, string productFile, vector<Dress>* r, string removedFile);

int main()
{

	BST<Dress> byID;
	BST<Dress> byBrand;
	vector<Dress> removed;
	byBrand.setUnique(false);
	bool cont=true;

	unsigned orderID;
	HashTable<Customer> customers;
	Order dummy;
	vector<Order> ords(1,dummy);
	vector<string> brands;

	string customerFile = "orderInput.txt";
	string productFile = "dressInput.txt";
	string removedFile = "removedDress.txt";
	string userType;	// Type of User: Employee or Customer

	readInFile(productFile, &byID, &byBrand, &brands);
	readInRemoved(removedFile, &removed);
	loadCustomerOrderData(customerFile, &orderID, &customers, &ords, &byID, &removed);

	PriorityQueue<Order> orders(ords);

	while(cont){
		cout << "Welcome to PARRISH & co." << endl;
		cout << "Who are you? (Please enter a number)" <<endl;
		cout << "1. Customer\n2. Employee\nEnter 0 to quit.\n";
		cout << ">> ";

		cin >> userType;
		cin.ignore(INT_MAX, '\n');
		if(userType=="0"){break;}

		while (!errorCheck(userType,2))
		{
			cout << "\nWho are you? (Please enter a number)" <<endl;
			cout << "1. Customer\n2. Employee\nEnter 0 to quit.\n";
			cout << ">> ";
			cin >> userType;
			cin.ignore(INT_MAX, '\n');
			if(userType=="0"){break;}
		}

		// Calls either interface
		if (userType == "1") { customer(&byID, &byBrand, &orders, &customers, &orderID, &brands, &cont); }
		else if (userType == "2") { employee(&byID, &byBrand, &orders, &customers, &removed, &brands, &cont);}
	}

	saveFile(&byID, &customers, &orderID, customerFile, productFile, &removed, removedFile);

	return 0;
}

void displayAboutPage()
{
	cout << endl;
	cout << setw(33) << setfill('|') << "" << "  PARRISH & CO.  " << setw(33) << setfill('|') << "" << endl << endl;
	cout << "By: Trang Van, Calista Tee, Thanh Nguyen, Vanessa Tiffany, Meta Novitia" <<endl;
	cout << "Call Us Now: (660) 882-7103" << endl << endl;
	cout << "About Our Company: " << endl;
	cout << "There are many clothing stores out there, but few sell high-end dresses.\n";
	cout << "We chose to create a storefront to sell designer dresses, such as those from \n";
	cout << "Alexander McQueen or Valentino. The focus of our store is on dresses and gowns " << endl;
	cout << "from multiple designers." << endl << endl;


	cout << "Our High End Developers: " << endl << endl;
	cout << "TRANG VAN" << endl;
	cout << "Currently a full-time student at De Anza College, pursuing a bachelor’s in " << endl <<
			"Computer Science with a minor in Design. I started coding in high school and " << endl <<
			"volunteered at my local Tech Museum to show people the exciting aspects of " << endl <<
			"science. Now, I hope to incorporate both art and technology in my work." << endl << endl;
	cout << "CALISTA TEE" << endl;
	cout << "A journaling enthusiast. Looking to digitize your daily journaling experience "<< endl <<
			"to increase your overall focus and productivity. "<< endl <<
			"Check out my projects: https://github.com/calistatee"<< endl << endl;
	cout << "THANH NGUYEN" << endl;
	cout << "Current full-time student majoring in Computer Science at De Anza College. Strong "<< endl <<
			"interest in programming and had a background in Economics in the past. Hoping to "<< endl <<
			"integrate financial field and tech field together in the future. "<< endl << endl;
	cout << "VANESSA TIFFANY" << endl;
	cout << "A full-time international student who is majoring computer science and will be " << endl <<
			"transferring this year. Technology has amazed me with their feature to ease " << endl <<
			"human’s life which makes me curious about the tech world." << endl << endl;
	cout << "META NOVITIA" << endl;
	cout << "Seventeen year old international student from Indonesia, majoring in Computer " << endl <<
			"Science. Loves competitive programming, competed in the ACM-ICPC last Fall " << endl <<
			"quarter, and currently participating in this year’s Google Code Jam." << endl << endl;

	cout << setw(83) << setfill('|') << "" << endl << endl;
}

void saveFile(BST<Dress>  *byID, HashTable<Customer>* customers, unsigned* orderID, string customerFile, string productFile, vector<Dress>* r, string removedFile){
	ofstream outC(customerFile), outP(productFile), outR(removedFile);

	byID->postOrderPrint(outP);

	outC << *orderID;
	for(int i=0; i<customers->getSize(); i++){
		customers->getBucket(i)->displayListData(outC);
	}

	for(int i=0; i<r->size(); i++){
		(r->at(i)).print(outR);
	}

	outC.close(); outP.close(); outR.close();
	cout << "+++" << endl;
}

void readInRemoved(string removedFile, vector<Dress>* r){
	ifstream in(removedFile);
	string data[8];

	getline(in,data[0]);
	while (!in.eof() && isdigit(data[0][0]))
	{
		for(int i = 1; i < 8; i++){getline(in, data[i]);}

		// Store Sizes
		stringstream ss(data[4]);
		vector<int> dressSizes;
		int num;
		while (ss >> num){ dressSizes.push_back(num);}

		stringstream ss2(data[6]);
		vector<float> ratings;
		while(ss2 >> num){ratings.push_back(num);}

		Dress d (stoi(data[0]), data[1], data[2],data[3], dressSizes, stof(data[5]), ratings);

		r->push_back(d);

		getline(in,data[0]);
	}

	in.close();
}

void readInFile(const string filename, BST<Dress> *bstID, BST<Dress> *bstBrand, vector<string>* brands)
{
	ifstream fin (filename);
	string data[8];
	bool t;

	getline(fin,data[0]);
	while (!fin.eof() && isdigit(data[0][0]))
	{
		t=true;
		for(int i = 1; i < 8; i++){getline(fin, data[i]);}

		// Store Sizes
		stringstream ss(data[4]);
		vector<int> dressSizes;
		int num;
		while (ss >> num){ dressSizes.push_back(num);}

		stringstream ss2(data[6]);
		vector<float> ratings;
		while(ss2 >> num){ratings.push_back(num);}

		Dress d (stoi(data[0]), data[1], data[2],data[3], dressSizes, stof(data[5]), ratings);

		bstID->insert(d);
		d.setKey("Brand");
		bstBrand->insert(d);
		for(int i=0; i<brands->size(); i++){
			if(brands->at(i)==data[2]){
				t=false;
				break;
			}
		}
		if(t){
			brands->push_back(data[2]);
		}

		getline(fin,data[0]);
	}

	fin.close();
}

void employee(BST<Dress> * byID, BST<Dress> * byBrand, PriorityQueue<Order>* ords, HashTable<Customer>* customers, vector<Dress>* r, vector<string>* brands, bool* cont)
{
	ifstream fin;
	ofstream fout;
	vector<string> employees[2];	// to store employees

	string empIn; // for employees' choice of actions
	string empFile = "employee.txt";

	fin.open(empFile);

	if (fin.fail()) {
		cout << "Employee file failed to open.";
		exit(-1);
	}

	// Make vector of employees (string obj)
	while (!fin.eof()) {
		string line, pass;
		while (!fin.eof()) {
			fin >> line >> pass;
			employees[0].push_back(line);
			employees[1].push_back(pass);
		}
	}

	string empID;
	string empPass;

	cout << "\nPlease enter your employee information (Press '#' then enter to quit):\n\n";

	cout << ">> Employee ID: ";
	cin >> empID;
	if(empID=="#"){cout << endl;return;}
	cin.ignore(INT_MAX,'\n');
	cout << ">> Password: ";
	cin >> empPass;
	if(empPass=="#"){cout << endl;return;}

	/*
	for (int i = 0; i < empID.length(); i++) {
		while (isdigit(empID[i])) { //need to change to if empID != readin file
			cout << "Employee record not found. Please enter again.\n";
			cout << "Employee ID: ";
			cin >> empID;
			cout << "Password: ";
			cin >> empPass;
			cin.clear();
		}
	} //end of for loop
	*/

	while (!empFound(employees, empID, empPass)) {
		cout << "\nPlease enter your employee information (Press '#' then enter to quit):\n\n";
		cout << ">> Employee ID: ";
		cin >> empID;
		cin.ignore(INT_MAX, '\n');
		if(empID=="#"){cout << endl;return;}
		cout << ">> Password: ";
		cin >> empPass;
		cin.ignore(INT_MAX, '\n');
		if(empPass=="#"){cout << endl;return;}
	}
		//if emp found
		cout << "\nWelcome back, " << empID << "!\n";

		// EMPLOYEE ACTIONS
		do {
			displayEmployeeMenu();
			cout << ">> Enter your choice: ";
			cin >> empIn;
			cin.ignore(INT_MAX, '\n');

			if (empIn == "1") {
				searchCustomer(customers);
				//continue;
			} else if (empIn == "2") {
				displayUnsorted(customers);
			} else if (empIn == "3") {
				viewOrdersPriority(ords, customers);
			} else if (empIn == "4") {
				shipOrder(customers, ords);
			} else if (empIn == "5") {
				listAllDresses(byID, byBrand);
				cout << endl;
			} else if (empIn == "6") {
				addDress(byID, byBrand, brands);
				cout << endl;
			} else if (empIn == "7") {
				removeDress(byID, byBrand, customers, r, brands);
				cout << endl;
			} else if (empIn == "8") {
				cout << "Thank you for working with us at THE DRESS BOUTIQUE today!\n";
				cout << "We hope to see you soon!\nHave a great day!\n\n";
				cout << "***********************************************************";
				cout << endl;

				cout << "[END OF EMPLOYEE INTERFACE]\n" << endl;
				return;
			} else if (errorCheck(empIn, 9) != true) { continue;}

		} while (empIn != "9");
		*cont = false;

}

void searchCustomer(HashTable<Customer>* cust)
{
	string first, last;
	cout << "\n>> Enter customer first name: ";
	getline(cin,first);
	cout << ">> Enter customer last name: ";
	getline(cin,last);
	Customer c;
	c.setFirst(first); c.setLast(last);
	vector<Customer> vc = cust->getAll(c);
	if(vc.size()<1){cout << "Customer not found." << endl;return;}
	for(int i=0; i<vc.size(); i++){
		cout << "\n"<< setw(110) << setfill('|') << "" << "\n";
		vc[i].showAll(cout);
	}

}

void displayUnsorted(HashTable<Customer>* customers)
{
	cout << "\n" << setw(110) << setfill('|') << "" << "\n";
	for(int i=0; i<customers->getSize(); i++){customers->printBucket(cout, i);}
}

void viewOrdersPriority(PriorityQueue<Order>* ord, HashTable<Customer>* customers)
{
	cout << "\n\n\n";
	vector<Order> d = ord->sort();
	Customer c;
	if(d.size()<1){cout << "No orders to show" << endl; return;}

	cout << setw(110) << setfill('=') << "" << endl;
	for(int i=0; i<d.size(); i++){
		c.setID(d[i].getCustomer()); c.setFirst(d[i].getFname()); c.setLast(d[i].getLname());
		(customers->get(c))->show(cout);
		cout << d[i];
		cout << setw(110) << setfill('=') << "" << endl;
	}

}

void shipOrder(HashTable<Customer>* customers, PriorityQueue<Order>* ords)
{
	unsigned orderID;
	string inp;
	cout << "\nEnter order ID to be shipped: ";
	cin >> orderID;
	cin.ignore(INT_MAX, '\n');

	Order o;
	o.setID(orderID);
	int i=ords->search(o);
	if(i==-1){cout << "\nOrder does not exist." << endl; return;}

	Order o1(ords->get_element(i));

	Customer c;
	c.setFirst(o1.getFname()); c.setLast(o1.getLname()); c.setID(o1.getCustomer());

	Customer* cp = (customers->get(c));
	vector<Order>* v = cp->getOrders();

	int j=0;
	for(int i=0; i<v->size(); i++){
		if(v->at(i).getID()==orderID){
			j=i;
			break;
		}
	}


	cout << "\nAre you sure you want to ship this order (Enter 'y' to confirm) :\n";
	cout << setw(110) << setfill('=') << "" << endl;
	cp->show(cout);
	cout << v->at(j);
	cout << setw(110) << setfill('=') << "" << endl;
	cout << " >> ";
	cin >> inp;
	cin.ignore(INT_MAX, '\n');
	if(inp == "y"){

		v->at(j).setState(2);
		ords->remove(i);

		cout << "\nOrder #" << setw(7) << right << setfill('0') << orderID << " has been shipped.\n";
	}


}

void listAllDresses(BST<Dress> *byID, BST<Dress> *byBrand)
{
	int empIn;
	string in;

	// two display options: name/id
	cout << "\nChoose a key to the list by (Enter any other key to quit): " <<endl;

	cout << "1. Display by dress brand \n";
	cout << "2. Display by dress ID \n";
	cout << ">> Enter: ";
	cin >> empIn;
	cin.ignore(INT_MAX, '\n');

	if (empIn == 1) {
		cout << endl;
		byBrand->inOrderPrint(cout);		// Print ALL
		cout << "\nDisplay More Information? (Press 'y' and enter to confirm)\n>> ";
		cin >> in;
		cin.ignore(INT_MAX, '\n');
		if(in=="y"){
			byBrand->inOrderPrint2(cout);
		}

	} else if (empIn == 2) {
		cout << endl;
		byID->inOrderPrint(cout);		// Print ALL
		cout << "\nDisplay More Information? (Press 'y' and enter to confirm)\n>> ";
		cin >> in;
		cin.ignore(INT_MAX, '\n');
		if(in=="y"){
			byID->inOrderPrint2(cout);
		}
	}
}

// checks to see if rand int is already in BST of Dresses
// returns true if it already exists, false otherwise
bool checkDup(unsigned n, BST<Dress> * byID)
{
	Dress d;
	d.setID(n);
	if (!byID->search(d))
	{
		return false;		//not a dupe
	}
	return true;
}

void addDress(BST<Dress> * byID, BST<Dress> * byBrand, vector<string>* brands)
{
	string name, brand, description, price;
	unsigned id;
	vector<int> sizes;

	do {
		srand(time(0));
		id = rand() % 9000000 + 1000000;
	} while(checkDup(id,byID));

	cout << "Please enter dress details. Press '#' then enter to quit at anytime." <<endl;
	cout << "Enter the dress's name: " <<endl;
	getline(cin, name);
	if(name=="#"){return;}
	cout << "Enter the dress's brand: " <<endl;
	getline(cin, brand);
	if(brand=="#"){return;}
	cout << "Enter the dress's description: " <<endl;
	getline(cin, description);
	if(description=="#"){return;}
	cout << "Enter the dress's price: " << endl;
	getline(cin, price);
	if(price=="#"){return;}

	//generate size vector of 0-12 (even #s)
	for (int i = 0; i <= 12; i += 2) {sizes.push_back(i);}
	vector<float> f;
	f.push_back(0); f.push_back(0);
	Dress newDress(id, name, brand, description, sizes, stof(price), f);

	byID->insert(newDress);
	newDress.setKey("Brand");
	byBrand->insert(newDress);
	bool t=true;
	for(int i=0; i<brands->size(); i++){
		if(brands->at(i)==brand){
			t=false;
			break;
		}
	}
	if(t){
		brands->push_back(brand);
	}

	cout << "NEW DRESS HAS BEEN ADDED: " << newDress << endl;


}

void removeDress(BST<Dress> * byID, BST<Dress> * byBrand, HashTable<Customer> * customers, vector<Dress>* r, vector<string>* brands)
{
	Dress removeDress;
	string empIn;
	unsigned id;
	do
	{
		cout << "\nRemove a dress by:\n1. ID\n2. Brand\n>> Enter your choice: ";
		cin >> empIn;
		cin.ignore(INT_MAX, '\n');
	} while (errorCheck(empIn,2) != true);

	if (empIn == "1"){
		cout << "\n>> Enter ID of the dress to remove: ";
		if(!(cin >> id)){
			cin.ignore(INT_MAX, '\n');
			cout << "\nINVALID ID";
			return;
		}
		cin.ignore(INT_MAX, '\n');
		removeDress.setID(id);
		if(!byID->search(removeDress)){cout << "Dress not found.\n"; return;}
		Dress d = (byID->getKeyItems(removeDress))[0];

		while(1){

			cout << "\nAre you sure you want to remove " << d.getName() + " by " + d.getBrand() << "?" << endl;
			cout << "1. Yes\n2. No\n>> ";
			cin >> empIn;
			cin.ignore(INT_MAX, '\n');

			if(empIn == "1")
			{
				byID->remove(d);
				for(int i=0; i < customers->getSize(); i++){
					List<Customer>* l = customers->getBucket(i);
					if(!l->isEmpty()){
						l->startIterator();
						while(!l->offEnd()){
							l->getIterator()->getCart()->removeDress(removeDress);
							l->moveIterNext();
						}
					}
				}
				d.setKey("Brand");
				byBrand->remove(d);
				r->push_back(d);
				cout << "\nDress is successfully removed!";
				return;
			}else if (empIn == "2")
			{
				return;
			}
		}


	} else if (empIn == "2")
	{
		cout << "\nBRANDS AVAILABLE: ";
		for(int i=0; i<brands->size(); i++){cout << endl << brands->at(i);}
		cout << "\n>> Enter brand of the dress to remove: ";
		getline(cin, empIn);
		removeDress.setKey("Brand");
		removeDress.setBrand(empIn);
		vector<Dress> v = byBrand->getKeyItems(removeDress);	// store all dresses of that brand into a vector
		if(v.size()==0){cout << "Brand not found.\n"; return;}

		if (v.size() > 0)
		{
			// Print contents of vector, now storing all dresses by brand
			cout << endl;
			for (int i = 0; i < v.size(); i++) {cout << i + 1 << "." << v[i] << endl;}

			cout << ">> Choose a dress: ";
			cin >> empIn;
			cin.ignore(INT_MAX, '\n');

			while (errorCheck(empIn, v.size()) != true) {
				for (int i = 0; i < v.size(); i++) {cout << i + 1 << "." << v[i] << endl;}
				cout << ">> Choose a dress: ";
				cin >> empIn;
				cin.ignore(INT_MAX, '\n');
			}
			removeDress = v[stoi(empIn) - 1];
			while(1){


			cout << "\nAre you sure you want to remove " << removeDress.getName() + " by " + removeDress.getBrand() << "?" << endl;
				// index has to be n-1 b/c customer sees dresses displayed at n+1
			cout << "1. Yes\n2. No\n>> ";
			cin >> empIn;
			cin.ignore(INT_MAX, '\n');

			if(empIn == "1")
			{
				byBrand->remove(removeDress);
				if(!(byBrand->search(removeDress))){
					for(int i=0; i<brands->size(); i++){
						if(brands->at(i)==removeDress.getBrand()){
							brands->erase(brands->begin()+i);
							break;
						}
					}
				}
				removeDress.setKey("ID");
				for(int i=0; i < customers->getSize(); i++){
					List<Customer>* l = customers->getBucket(i);
					if(!l->isEmpty()){
						l->startIterator();
						while(!l->offEnd()){
							l->getIterator()->getCart()->removeDress(removeDress);
							l->moveIterNext();
						}
					}
				}
				byID->remove(removeDress);
				r->push_back(removeDress);

				cout << "\nDress is successfully removed!";
				return;
			}else if (empIn == "2")
			{
				return;
			}}
		}
	}
}

void displayEmployeeMenu()
{
	cout << "\nPlease select an action: \n";
	cout << "1. Search for customer by name\n";
	cout << "2. Display unsorted customer information\n";
	cout << "3. View orders by priority\n";
	cout << "4. Ship an order\n";
	cout << "5. List database of dresses\n";
	cout << "6. Add a dress to database\n";
	cout << "7. Remove a dress from database\n";
	cout << "8. Log out\n";
	cout << "9. Quit\n\n";
}

bool empFound(vector<string> v[], string empID, string empPass)
{
	// Search for employee, proceed if found
	for (int i = 0; i < v[0].size(); i++)
	{
		if (empID == v[0][i]){
			if(empPass==v[1][i]){return true;}
			cout << "Invalid Password" << endl;
			return false;
		}
	}
	cout <<"Employee record not found" << endl;
	return false;
}

void customer(BST<Dress>  *byID, BST<Dress> *byBrand, PriorityQueue<Order>* orders, HashTable<Customer> * customers, unsigned* orderID, vector<string>* brands, bool* cont)
{
	string custIn; // for customers' choice of actions
	Customer* c=NULL;

	do {
		displayCustomerMenu(&c);
		cout << ">> Enter your choice: ";
		cin >> custIn;
		cin.ignore(INT_MAX, '\n');

		if (custIn == "1") {
			searchForDress(byID, byBrand, &c, customers, orderID, brands);
		} else if (custIn == "2") {
			listAllDresses(byID, byBrand);
		} else if (custIn == "3") {
			if(c==NULL){customerLogin(&c, customers, orderID);}
			if(c!=NULL){viewCart(&c, orders, orderID);}
		} else if (custIn == "4") {
			if(c==NULL){customerLogin(&c, customers, orderID);}
			if(c!=NULL){viewPastPurchases(&c);}
		} else if (custIn == "5") {
			displayAboutPage();
		} else if (custIn == "6") {
			cout << "Thank you for shopping with us at THE DRESS BOUTIQUE!\n";
			cout << "We hope to see you soon!\nHave a great day!\n";
			cout << endl;

			cout << "[END OF CUSTOMER INTERFACE]\n" <<endl;
			return;
		} else if (errorCheck(custIn, 7) != true) {
			continue;
		}

	} while (custIn != "7");

	*cont = false;
}

void displayCustomerMenu(Customer** c)
{
	string prompt[] = {"6. Back to main menu\n", "6. Log out\n"};
	int i=0;
	if((*c)!=NULL){
		i=1;
	}
	cout << "\nPlease select an action: \n";
	cout << "1. Search for a dress\n";
	cout << "2. List all dresses\n";
	cout << "3. View cart\n";
	cout << "4. View your orders\n";
	cout << "5. About us\n";
	cout << prompt[i];
	cout << "7. Quit\n\n";
}

void displayShipmentMenu(){
	cout << "\nPlease select a shipping speed:\n"
		 << "  1. Overnight (Next Day Delivery)\n"
		 << "  2. Rush (3-5 days arrival)\n"
		 << "  3. Standard (5-10 days arrival)\n"
		 << ">> Enter your choice (press '#' then enter to quit): ";
}

void viewCart(Customer** c, PriorityQueue<Order>* orders, unsigned* orderID){
	Order* o = (*c)->getCart();
	string input;

	while(1){
		cout << endl << *o;
		cout << setw(110) << setfill('-') << "" << "\n";
		cout << "\nWhat would you like to do?\n"
			 << "1. Remove a dress\n"
			 << "2. Place order\n"
			 << "3. Back to main menu\n>> ";
		cin >> input;
		cin.ignore(INT_MAX, '\n');
		while(!errorCheck(input, 3)){
			cout << "\nWhat would you like to do?\n"
				 << "1. Remove a dress\n"
				 << "2. Place order\n"
				 << "3. Back to main menu\n>> ";
			cin >> input;
			cin.ignore(INT_MAX, '\n');
		}
		if(input=="1"){
			removeDress(o);
		}else if(input == "2"){
			placeOrder(c,orders,orderID);
			break;
		}else{
			return;
		}
	}
}

void removeDress(Order* o){
	vector<Dress> vd = o->getItemsOrdered();
	string input;
	if(vd.size()==0){cout << "No dresses in cart." << endl; return;}
	for(int i=0; i<vd.size(); i++){cout << endl << i+1 << ". " << vd[i];}
	cout << "\nWhich dress number would you like to remove?\n>> ";
	cin >> input;
	cin.ignore(INT_MAX, '\n');
	while(!errorCheck(input, vd.size())){
		for(int i=0; i<vd.size(); i++){cout << endl << i+1 << ". " << vd[i];}
		cout << "\nWhich dress number would you like to remove?\n>> ";
		cin >> input;
		cin.ignore(INT_MAX, '\n');
	}
	Dress d =  vd[stoi(input)-1];
	cout << "\nAre you sure you want to remove : " << d << "?\n";
	cout << ">> Press 'y' and enter to confirm: ";
	cin >> input;
	cin.ignore(INT_MAX, '\n');
	if(input=="y"){
		o->removeDress(d);
	}
}

void placeOrder(Customer** c, PriorityQueue<Order>* orders, unsigned* orderID){
	string input, in="";
	Order* cart = (*c)->getCart();
	if((cart->getItemsOrdered()).size()==0){cout << "No dresses in cart." << endl; return;}
	while(in!="y"){
		displayShipmentMenu();
		cin >> input;
		cin.ignore(INT_MAX, '\n');
		if(input=="#"){return;}
		while(!errorCheck(input, 3)){
			displayShipmentMenu();
			cin >> input;
			cin.ignore(INT_MAX, '\n');
			if(input=="#"){return;}
		}
		cout << "\nConfirm Order? (Press 'y' then enter to confirm)\n" << ">> ";
		cin >> in;
		cin.ignore(INT_MAX, '\n');
	}
	cart->setShippingSpeed(stoi(input)-1);
	cart->confirmOrder();
	vector<Dress> vd = cart->getItemsOrdered();
	Order newCart(orderID, (*c)->getID(), (*c)->getFirst(), (*c)->getLast());
	(*c)->addOrder(newCart);
	cout << "\nCongratulations! Your order has been confirmed." << endl;
	cout << "Your total spending is: $" << cart->getPrice() << endl;
}

bool custFound(string id, Customer** c, HashTable<Customer>* customers){
	for(int i=0; i<customers->getSize(); i++){
		List<Customer>* l = customers->getBucket(i);
		if(!(l->isEmpty())){
			l->startIterator();
			while(!(l->offEnd())){
				*c=l->getIterator();
				if((*c)->getID() == id){
					return true;
				}
				l->moveIterNext();
			}
		}
	}
	return false;
}

bool loginSucceed(string pass, Customer** c){
	if((*c)->getPass()==pass){
		return true;
	}
	return false;
}

void customerLogin(Customer** c, HashTable<Customer>* customers, unsigned* orderID){
	string custIn, pass, id;
	cout << "\nAre you a new customer?\n1.Yes\n2.No\n>> ";

	cin >> custIn;
	cin.ignore(INT_MAX, '\n');
	while (errorCheck(custIn,2) != true)
	{
		cout << "\nAre you a new customer?\n1.Yes\n2.No\nPress '#' and enter to quit\n>> ";
		cin >> custIn;
		cin.ignore(INT_MAX, '\n');
		if(custIn=="#"){return;}
	}
	if(custIn=="1"){
		newCustomer(c,customers,orderID);
	}else{
		while(1){
			(*c) = NULL;
			cout << "\nLOGIN (Press '#' then enter to quit)\n";
			cout << ">> Enter username(e-mail) : ";
			cin >> id;
			cin.ignore(INT_MAX, '\n');
			if(id=="#"){return;}
			cout << ">> Enter password : ";
			cin >> pass;
			cin.ignore(INT_MAX, '\n');
			for(int i=0; i<id.length(); i++){id[i]=tolower(id[i]);};
			if(custFound(id, c, customers)){
				if(loginSucceed(pass, c)){
					cout << "Welcome back " << (*c)->getFirst() << " " << (*c)->getLast() << "!\n";
					break;
				}else{
					cout << "INVALID PASSWORD\n\n";
				}
			}else{
				cout << "USERNAME NOT FOUND\n\n";
			}
		}
	}
}

void viewPastPurchases(Customer** c){
	cout << "\n" << setw(110) << setfill('|') << "" << "\n";
	(*c)->showAll(cout);
}

void searchForDress(BST<Dress>  *byID, BST<Dress> *byBrand, Customer ** c, HashTable<Customer>* customers, unsigned* orderID, vector<string>* brands) {
	Dress searchD;	// dress customer wants to search for
	string custIn, in2;

	cout << "\n**SEARCH FOR A DRESS**" << endl;
	cout << "1. Search by ID." << endl;
	cout << "2. Search by Brand." << endl;
	cout << ">> Enter your choice: ";

	cin >> custIn;
	cin.ignore(INT_MAX, '\n');

	while (errorCheck(custIn, 2) != true) {
		cout << "\n**SEARCH FOR A DRESS**" << endl;
		cout << "1. Search by ID." << endl;
		cout << "2. Search by Brand." << endl;
		cout << ">> Enter your choice: ";
		cin >> custIn;
		cin.ignore(INT_MAX, '\n');
	}

	if (custIn == "1") {	// By ID
		cout << "\n>> Enter the dress's ID: ";

		cin >> custIn;
		cin.ignore(INT_MAX, '\n');
		while(!errorCheck(custIn,9999999)){
			cout << "\n>> Enter the dress's ID: ";
			cin >> custIn;
			cin.ignore(INT_MAX, '\n');
		}
		searchD.setID(stoi(custIn));	// set the ID to retrieve from tree
		if(!(byID->search(searchD))){cout << "Dress Not Found\n"; return;}
		// default key is ID
		vector<Dress> v = byID->getKeyItems(searchD);// ID is unique so only one will be pushed back

		cout << "\nYour dress: " << v[0] << endl;

		cout << "\nPress Enter to View Dress Description >>>" << endl;
		cin.get();		// allows user to press enter to continue

		v[0].printDetails(cout);
		chooseAction(c, customers, orderID, &v[0], byID, byBrand);

	} else if (custIn == "2") {
		searchD.setKey("Brand");
		cout << "\nBRANDS WE OFFER:";
		for(int i=0; i<brands->size(); i++){cout << endl << brands->at(i);}

		cout << "\n>> Enter the dress's brand: ";
		getline(cin, custIn);
		searchD.setBrand(custIn);
		if(!(byBrand->search(searchD))){cout << "Dress Not Found\n"; return;}
		vector<Dress> v = byBrand->getKeyItems(searchD);	// store all dresses of that brand into a vector

		// Print contents of vector, now storing all dresses by brand
		for (int i = 0; i < v.size(); i++) {cout << "\n" << i + 1 << "." << v[i];}

		cout << "\n>> Choose a dress: ";
		cin >> custIn;
		cin.ignore(INT_MAX, '\n');

		while (errorCheck(custIn, v.size()) != true) {
			for (int i = 0; i < v.size(); i++) {cout << "\n" << i + 1 << "." << v[i];}
			cout << "\n>> Choose a dress: ";
			cin >> custIn;
			cin.ignore(INT_MAX, '\n');
		}

		cout << "\nYour dress: " << v[stoi(custIn) - 1] << endl;
			// index has to be n-1 b/c customer sees dresses displayed at n+1

		cout << "\nPress Enter to View Dress Description >>>" << endl;
		cin.get();		// allows user to press enter to continue

		v[stoi(custIn) - 1].printDetails(cout);
		chooseAction(c, customers, orderID, &v[stoi(custIn) - 1], byID, byBrand);
	}

}

void chooseAction(Customer** c, HashTable<Customer>* customers, unsigned* orderID, Dress* d, BST<Dress>  *byID, BST<Dress> *byBrand){
	string in;
	cout << "\nWhat would you like to do?\n"
		 << "1. Add dress to cart\n"
		 << "2. Rate dress\n"
		 << "3. Back to main menu\n"
		 << ">> ";
	cin >> in;
	cin.ignore(INT_MAX, '\n');
	while(!errorCheck(in,3)){
		cout << "\nWhat would you like to do?\n"
			 << "1. Add dress to cart\n"
			 << "2. Rate dress\n"
			 << "3. Back to main menu\n"
			 << ">> ";
		cin >> in;
		cin.ignore(INT_MAX, '\n');
	}
	if(in=="1"){
		if((*c)==NULL){customerLogin(c, customers, orderID);}
		if((*c)!=NULL){

			vector<int> sz = d->getSizes();
			int cs;
			cout << "\nChoose a size:";
			for(int i=0; i<sz.size(); i++){
				cout << " " << sz[i];
			}
			cout << endl << ">> ";
			cin >> cs;
			cin.ignore(INT_MAX, '\n');
			while(cs%2!=0 || cs < 0 || cs > 12){
				cout << "Invalid input.\n\nChoose a size:";
				for(int i=0; i<sz.size(); i++){
					cout << " " << sz[i];
				}
				cout << endl << ">> ";
				cin >> cs;
				cin.ignore(INT_MAX, '\n');
			}
			d->setChosenSize(cs);
			(*c)->getCart()->addDress(*d);
			cout << "Dress has been added to cart!" << endl;
		}
		else{cout << "Failed to log in." << endl;}
	}else if(in=="2"){
		cout << "\nRate this dress from a scale of 1-5: ";
		cin >> in;
		cin.ignore(INT_MAX, '\n');
		while(!errorCheck(in,5)){
			cout << "\nRate this dress from a scale of 1-5: ";
			cin >> in;
			cin.ignore(INT_MAX, '\n');
		}
		d->addRatings(stof(in));
		d->setKey("ID");
		byID->remove(*d);
		byID->insert(*d);
		d->setKey("Brand");
		byBrand->remove(*d);
		byBrand->insert(*d);
		cout << "Thanks for rating this dress!\n";
	}
}

// Check if user inputs are in the correct range & if it's valid
bool errorCheck(string userInput, int numOfOptions)
{
	int n;
	stringstream ss(userInput);
	if (!(ss >> n)) {
		cout << "!! Please enter numbers not letters !!" << endl;
		return false;

	} else if (stoi(userInput) < 1 || stoi(userInput) > numOfOptions)
	{
		// PROBLEM: diff slides have diff # of options
		cout << "!! Invalid input. !!" << endl;
		return false;
	}

	return true;

}

void newCustomer(Customer** c, HashTable<Customer>* customers, unsigned* orderID)
{
	 string custIn;
	 Customer newC;
	 cout << "\nWelcome! Please fill out your information. Press '#' and enter to quit at anytime." << endl;

	 cout << "\nEmail (Login ID, case insensitive): ";
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 for(int i=0; i<custIn.length(); i++){custIn[i]=tolower(custIn[i]);}
	 while(custFound(custIn, c, customers)){
		 (*c)=NULL;
		 cout << "ID has been used." << endl;
		 cout << "\nEmail (Login ID, case insensitive): ";
		 getline(cin, custIn);
		 for(int i=0; i<custIn.length(); i++){custIn[i]=tolower(custIn[i]);}
	 }
	 newC.setID(custIn);

	 cout << "\nPassword: " ;
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 newC.setPass(custIn);

	 cout << "\nEnter your first name: ";
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 newC.setFirst(custIn);

	 cout << "\nEnter your last name: ";
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 newC.setLast(custIn);

	 cout << "\nEnter your shipping address: ";
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 newC.setAddress(custIn);

	 cout << "\nEnter your phone number: ";
	 getline(cin, custIn);
	 if(custIn=="#"){return;}
	 newC.setPhone(stoll(custIn));

	 cout << "\nYour info:\n";
	 newC.show(cout);
	 cout << "\nConfirm your data? (Press 'y' then enter to confirm)\n>> ";
	 cin >> custIn;
	 cin.ignore(INT_MAX, '\n');
	 if(custIn=="y"){
		 customers->insert(newC);
		 (*c) = customers->get(newC);
		 Order o(orderID, (*c)->getID(), (*c)->getFirst(), (*c)->getLast());
		 (*c)->addOrder(o);
	 }else{customerLogin(c, customers, orderID);}

}

void loadCustomerOrderData(string f, unsigned* orderID, HashTable<Customer>* customers, vector<Order>* ords, BST<Dress>* b, vector<Dress>* r){
	ifstream in(f);
	string data[8];
	Dress d;
	int data2[5], id, cs;
	in >> *orderID;
	in.ignore(2);
	getline(in,data[1]);
	while(!in.eof() && data[1]!="\n"){
		for(int i=2; i<8; i++){getline(in,data[i]);}	// 5 blocks of data: password, fname, lname, address, phone, numberOfOrders
		Customer c(data[1], data[2], data[3], data[4], data[5], stoll(data[6]));
		vector<Order> o;
		for(int i=0; i<stoi(data[7]); i++){
			for(int j=0; j<5; j++){in>>data2[j];} // 5 blocks of data: id, dateOrdered, shippingSpeed, state, numberOfItems
			Order o1(data2[0], data2[1], data2[2], data2[3], data[1], data[3], data[4]);
			for(int j=0; j<data2[4]; j++){
				in>>id;
				in>>cs;
				d.setID(id);
				vector<Dress> vd;
				if(!(b->search(d))){
					for(int i=0; i<r->size(); i++){
						if(d.isSame(r->at(i))){
							vd.push_back(r->at(i));
							break;
						}
					}
				}else{
					vd = b->getKeyItems(d);
				}
				vd[0].setChosenSize(cs);
				o1.addDress(vd[0]);
			}
			if(data2[3]==1){ords->push_back(o1);}
			c.addOrder(o1);
		}
		customers->insert(c);
		if(stoi(data[7])>0){in.ignore(1);}
		getline(in,data[0]); getline(in,data[0]); getline(in,data[1]);
	}

	in.close();
}
