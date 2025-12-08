#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;


#include "Player.h"

	//Constructor
Player::Player(Location* l, list<Item*> i) :
		steps(0),
		location(l),
		inventory(i)
	{
	}


	//Methods
	bool Player::hasItem(Item* i) //to check if an item is in the inventory
	{
		for (Item* c : getinventory())
		{
			if (c == i) {
				cout << "You have the required item" << endl;
				return true;
			}
		}

		cout << "You do not have the required item" << endl;
		return false;

	};

	bool Player::takeItem(Item* i) //to add an item to the inventory; returns true / false toindicate success / failure(because the item may not be here)
	{
		for (Item* c : location->getcontents())
		{
			if (c->getname() == i->getname()) {
				cout << "Item taken: " << i->getname() << endl;
				location->removeItem(i);
				inventory.push_back(i);
				cout << endl;
				return true;
			}
		}
		cout << "Item not at location" << endl;
		cout << endl;
		return false;
	};

	bool Player::dropItem(Item* i) //  to drop an item at the current location; returns true / false to indicate success / failure(because you may not have the item)
	{
		list<Item*>& tempinventory = getinventory();

		//Code from additem
		for (auto iterator = tempinventory.begin(); iterator != tempinventory.end(); ++iterator) //loops through the inventory list looking for....
		{
			if ((*iterator)->getname() == i->getname()) { //... the item NAME
				tempinventory.erase(iterator); //If it finds name takes it out of the list
				location->additem(i); //adds item to location to stop player from softlocking
				cout << "You dropped: " << i->getname() << " in: " << location->getname() << endl;
				cout << endl;
				return true; //Stops there
			}
		}

		cout << "You do not have that item" << endl;
		cout << endl;
		return false;

	};


	bool Player::openItem(Item* i)  //to open an item; returns true / false to indicate success / failure(e.g.because the item is not a container, its open method fails (see below))
	{
		Container* c = dynamic_cast<Container*>(i);

		if (c != nullptr) {
			c->open(this,location);
			return true;
		}

		else
		{
			cout << "Item is not a container" << endl;
			cout << endl;
			return false;
		}
	};

	void Player::printStatus()
	{
		cout << "Current Location: " << location->getname() << endl << "Steps Taken: " << getsteps() << endl;
		cout << "Current Inventory: " << endl;
		for (Item* i : inventory) {
			cout << "    " << i->getname() << endl;
		}
		cout << endl;
	}; // to display the current location, inventory, and number of steps

	void Player::addsteps() {
		steps = getsteps()+1;
	}


	//Getters
	int Player::getsteps() {
		return steps;
	}
	Location* Player::getlocation() {
		return location;
	}
	list <Item*>& Player::getinventory() {
		return inventory;
	}

	//Setters?
	void Player::setLocation(Location* l) {
		location = l;
	}

