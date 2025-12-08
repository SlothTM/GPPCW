#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;
#include "Item.h"
#include "Location.h"

class Player {
private:
	//Attributes
	int steps; //steps taken
	Location* location; //current location
	list<Item*> inventory; //Player inventory

public:
	//Constructor
	Player(Location* l, list<Item*> i);


	//Methods
	bool hasItem(Item* i); //to check if an item is in the inventory


	bool takeItem(Item* i); //to add an item to the inventory; returns true / false toindicate success / failure(because the item may not be here)


	bool dropItem(Item* i); //  to drop an item at the current location; returns true / false to indicate success / failure(because you may not have the item)


	bool openItem(Item* i);  //to open an item; returns true / false to indicate success / failure(e.g.because the item is not a container, its open method fails (see below))

	void printStatus(); ; // to display the current location, inventory, and number of steps

	void addsteps();


	//Getters
	int getsteps();
	Location* getlocation();
	list <Item*>& getinventory();

	//Setters?
	void setLocation(Location* l);
};
