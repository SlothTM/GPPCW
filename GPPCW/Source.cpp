#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

/*
Classes:

Player:

	Attributes:
		Location
		Inventory
		Steps

	Functions:
		-bool hasItem(Item *i) to check if an item is in the inventory

		bool takeItem(Item *i) to add an item to the inventory; returns true/false to
		indicate success/failure (because the item may not be here)

		 bool dropItem(Item *i) to drop an item at the current location; returns
		true/false to indicate success/failure (because you may not have the item)

		bool openItem(Item *i) to open an item; returns true/false to indicate
		success/failure (e.g. because the item is not a container, its open method fails
		(see below))

		void printStatus() to display the current location, inventory, and number of
		steps

Item:	
	Attributes:
		Name
		Description

	Container Subclass:
		Attributes:
			Contents
			ContainerKey
			Opened

		Functions:
			Bool Open - returns false if you don’t have the necessary key item, or it is already open
						- adds the contents to your inventory and returns true if you d



Location:
	Attributes:
		Number
		Name
		Description
		Contents
		doorKey
		connections

	Function:
		void print() which displays the location’s description and the current list of
		items

		bool removeItem(Item *i) to remove an item from the location; returns
		true/false for success/failure (because the item may not be here)

		void addItem(Item *i) to add an item to the location

		bool move(string &direction) to head in the given direction. This prints a
		suitable message and returns false if there is no connection in that direction, or if
		it requires a key item which the player does not have. Otherwise, it changes the
		current location and returns true
*/



class Player {
private:
	//Attributes
	int steps; //steps taken
	Location* location; //current location
	vector <Item*> inventory; //Player inventory

public:
	//Constructor
	Player(Location* l, vector <Item*> i) :
		steps(0),
		location(l),
		inventory(i)
	{}


	//Methods
	bool hasItem(Item* i) //to check if an item is in the inventory
	{
		for (Item* c : getinventory())
		{
			if (c== i) {
				cout << "You have the required item" << endl;
				return true;
			}
		}

		cout << "You do not have the required item" << endl;
		return false;

	};

	bool takeItem(Item* i) //to add an item to the inventory; returns true / false toindicate success / failure(because the item may not be here)
	{
		for (Item* c : location->getcontents())
		{
			if (c->getname() == i->getname()) {
				cout << "Item taken" << endl;
				location->removeItem(i);
				inventory.push_back(i);
				return true;
			}
		}
		cout << "Item not at location" << endl;
		return false;
	}; 

	bool dropItem(Item* i) //  to drop an item at the current location; returns true / false to indicate success / failure(because you may not have the item)
	{

	}; 
	bool openItem(Item* i) {};  //to open an item; returns true / false to indicate success / failure(e.g.because the item is not a container, its open method fails (see below))

	void printStatus() 
	{
		cout << "Current Location" << location->getname() << endl << "Steps Taken" << getsteps() << endl;
		for (Item* i : inventory) {
			cout << i->getname() << endl;
		}
	
	}; // to display the current location, inventory, and number of steps


	//Getters
	int getsteps() {
		return steps;
	}
	Location* getlocation() {
		return location;
	}
	vector <Item*>& getinventory() {
		return inventory;
	}

	//Setters?
	void setLocation(Location* l) {
		location = l;
	}

};

class Item {
protected:
	//Attributes
	string name; 
	string description;

public:
	//Constructor
	Item(string n, string de) : 
		name(n), 
		description(de) 
	{}

	//Methods
	string getname() {
		return name;
	}
	string getdescription() {
		return description;
	}
};

class Container : public Item {
private:
	//Attributes
	list<Item*> contents; //Inside Container
	Item* containerKey; //Item to open it
	bool isopen; //Container open or not

public:
	//Constructor
	Container(string n, string de, Item* k) :
		Item(n, de),
		containerKey(k),
		isopen(false)
	{
		if (containerKey == nullptr) //No key container for like a character bag for example?
			isopen = true;
	}

	//Methods
	list<Item*> getcontents() {
		return contents;
	}
	Item* getkey() {
		return containerKey;
	}
};


class Location {
private:

	//Attributes
	int id; //Location Id (Number in cw brief)
	string name; 
	string description;
	list <Item*> contents; //What items are in location
	list<Location*> connections; // Where can you go 
	list<Item*> doorKey; //Key needed for each exit

public:
	//Constructor
	Location(int i, string n, string de, list <Item*> co, list <Location*> cn, list <Item*> dk) :
		id(i),
		name(n), 
		description(de), 
		contents(co), 
		connections(cn), 
		doorKey(dk) 
	{}

	
	//Methods
	int getnumber() 
	{
		return id;
	}

	string getname()
	{
		return name;
	}

	string getdescription() 
	{
		return description;
	}

	list<Item*>& getcontents()
	{
		return contents; 
	}

	Item* getdoorkey(string& direction) 
	{
	}

	Location* getconnection(const std::string& direction) 
	{
	}

	void removeItem(Item* i) {
		list<Item*>& tempContents = getcontents();


		for (auto iterator = tempContents.begin(); iterator != tempContents.end(); ++iterator)
		{
			if ((*iterator)->getname() == i->getname()) {
				tempContents.erase(iterator);
				break;
			}
		}

	}

};

