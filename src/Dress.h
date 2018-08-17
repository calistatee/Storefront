#ifndef DRESS_H_
#define DRESS_H_
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

class Dress {
private:

	unsigned ID;
	string name;
	string brand;
	string description;
	vector<int> sizes;
	int chosenSize;
	double price;
	string key;
	vector<float> ratings;

public:

	/** Constructors*/
	Dress();

	Dress(unsigned id, string n, string b, string d, vector<int> s, double p, vector<float> r);

	// Access Functions
	unsigned getID() const;
	string getName() const;
	string getBrand() const;
	string getDescription() const;
	vector<int> getSizes() const;
	double getPrice() const;
	vector<float> getRatings() const;
	int getChosenSize();

	string getKey(){
		return key;
	}

	// Manipulation Procedures

	void setKey(string k);
	void setID(unsigned i);
	void setName(string n);
	void setBrand(string b);
	void setDescription(string d);
	void setSizes(vector<int> s);
	void setPrice(double p);
	void addRatings(float r);
	void setChosenSize(int s);

	/**Additional Functions*/
	friend ostream& operator<<(ostream& os, const Dress& dress);
	//prints out a dress to the designated stream in the following format
	//ID: <id>
	//<name> <rating>
	//<brand>
	//$<price>
	//<description>
	//<sizes>

    bool operator==(const Dress& dress);
    //compares two dresses to determine if they are the same dress

	bool operator<(const Dress& dress);
	//compares two dresses to determine if one comes before the other
	//by id, returns false if the two dresses are the same

	bool operator>(const Dress& dress);
	//compares two dresses to determine if one comes after the other
	//by id, returns false if the two dresses are the same

	bool isSame(const Dress& dress);

	void print(ostream& out);
	void printDetails(ostream& os);

};



#endif /* DRESS_H_ */

Dress::Dress(){
	ID=0;
	name="";
	brand="";
	description="";
	price=0;
	chosenSize= -2;
	key = "ID";
	ratings.push_back(0);
	ratings.push_back(0);
}

Dress::Dress(unsigned id, string n, string b, string d, vector<int> s, double p, vector<float> r){
	ID=id;
	name=n;
	brand=b;
	description=d;
	sizes = s;
	price=p;
	chosenSize= -2;
	key = "ID";
	ratings = r;
}

bool Dress::operator==(const Dress& dress){
	string b = brand;
	string b2 = dress.brand;
	if(key==dress.key){
		if(key=="ID"){return ID==dress.ID;}
		else{
			for(int i=0; i<b2.size(); i++){
				if(b[i]>='a' && b[i]<='z'){
					b[i]-=32;
				}
				if(b2[i]>='a' && b2[i]<='z'){
					b2[i]-=32;
				}
				if(b[i]!=b2[i]){
					return false;
				}
			}
			return true;
		}
	}
	cout << "ERROR: Keys do not match" << endl;
	return false;
}

bool Dress::isSame(const Dress& dress){
	return ID==dress.ID;
}

bool Dress::operator>(const Dress& dress){
	string b = brand;
	string b2 = dress.brand;
	if(key==dress.key){
		if(key=="ID"){return ID>dress.ID;}
		else{
			for(int i=0; i<b.size(); i++){
				if(b[i]>='a' && b[i]<='z'){
					b[i]-=32;
				}
			}
			for(int i=0; i<b2.size(); i++){
				if(b2[i]>='a' && b2[i]<='z'){
					b2[i]-=32;
				}
			}
			return (b>b2);
		}
	}
	cout << "ERROR: Keys do not match" << endl;
	return false;
}

bool Dress::operator<(const Dress& dress){
	string b = brand;
	string b2 = dress.brand;
	if(key==dress.key){
		if(key=="ID"){return ID<dress.ID;}
		else{
			for(int i=0; i<b.size(); i++){
				if(b[i]>='a' && b[i]<='z'){
					b[i]-=32;
				}
			}
			for(int i=0; i<b2.size(); i++){
				if(b2[i]>='a' && b2[i]<='z'){
					b2[i]-=32;
				}
			}
			return (b<b2);
		}
	}
	cout << "ERROR: Keys do not match" << endl;
	return false;
}

ostream& operator<<(ostream& os, const Dress& d){
	os << "[" << setw(7) << setfill('0') << d.ID << "] " << setfill(' ') << left << setw(65) << d.brand + ": " + d.name << fixed << setprecision(2) << " || Price: $" << right << setw(9)  << d.price;
	return os;
}

unsigned Dress::getID() const{
	return ID;
}

string Dress::getName() const{
	return name;
}
string Dress::getBrand() const{
	return brand;
}

string Dress::getDescription() const{
	return description;
}

vector<int> Dress::getSizes() const{
	return sizes;
}

double Dress::getPrice() const{
	return price;
}

vector<float> Dress::getRatings() const{
	return ratings;
}

int Dress::getChosenSize(){
	return chosenSize;
}

void Dress::setKey(string k){
	if(k=="ID" || k=="Brand"){key = k;}
	else{cout << "ERROR: Key not valid" << endl;}
}

void Dress::setID(unsigned i){
	ID = i;
}

void Dress::setName(string n){
	name = n;
}

void Dress::setBrand(string b){
	brand = b;
}

void Dress::setDescription(string d){
	description = d;
}

void Dress::setSizes(vector<int> s){
	sizes = s;
}

void Dress::setPrice(double p){
	price = p;
}

void Dress::addRatings(float r){
	ratings[0]+=r;
	ratings[1]++;
}

void Dress::setChosenSize(int s){
	chosenSize = s;
}

void Dress::print(ostream& out){
	out << ID << endl << name << endl << brand << endl << description << endl;
	for(int i=0; i<sizes.size(); i++){
		out << sizes[i] << " ";
	}
	out << endl << price << endl << ratings[0] << " " << ratings[1] << endl << endl;
}

void Dress::printDetails(ostream& os){
	const int SIZE = sizes.size();
	os << setw(68) << setfill('~') << "" << endl;
	os << "::  ======================= ID: #" << ID << " =======================  ::\n"
	   << "::  " << name << right << setfill(' ') << setw(65-name.length()) << "::\n"
	   << "::  by " << brand << right << setfill(' ') << setw(62-brand.length()) << "::\n"
	   << "::  $" << fixed << setprecision(2)<< price << right << setfill(' ') << setw(68-(to_string(price)).length()) << "::\n"
	   << "::  Ratings : ";


	int k=0;

	if(ratings[1]>0){
		for(int i=0; i< int(round( (ratings[0]/ratings[1])* 2 )) ; i++){
				if(i%2==0){
					os << "<";
					k++;
				}else{
					os << "> ";
					k+=2;
				}
			}

		os << "  ( " << fixed << setprecision(1) << ratings[0]/ratings[1] << " / 5.0 )";
	}else{
		os << "No ratings yet";
		k = -1;
	}
	os << right << setfill(' ') << setw(64 - k - 25) << "::";
	os << "\n::  Sizes   : ";
	k=0;
	for(int i = 0; i < SIZE; i++)
	{
		os << sizes[i] << " ";
		k+= (to_string(sizes[i])).length() + 1;
	}
	os << right << setfill(' ') << setw(64 - k - 10) << "::";

	string str = description;
	os << "\n::  " << right << setfill(' ') << setw(64) << "::"
	   << "\n::  Description:" << right << setfill(' ') << setw(52) << "::";

	while(str.length()>0){
		k=60;
		if(k>=str.length()){
			os << "\n::  " << str << right << setfill(' ') << setw(64-str.length()) << "::";
			break;
		}
		while(str[k] != ' '){
			k--;
		}
		os << "\n::  " << str.substr(0,k) << right << setfill(' ') << setw(60-k+4) << "::";
		str = str.substr(k+1);
	}

	os << endl << setw(68) << setfill('~') << "" << endl;
}
