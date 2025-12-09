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
		for (Item* c : getinventory()) //checks inventory for item
		{
			if (c == i) {
				cout << "You have the required item" << endl; //dont think i even need this
				return true;
			}
		}

		return false;

	};

	bool Player::takeItem(Item* i) //to add an item to the inventory; returns true / false toindicate success / failure(because the item may not be here)
	{
		for (Item* c : location->getcontents()) //Loop through location contents
		{
			if (c->getname() == i->getname()) { //once found
				cout << "Item taken: " << i->getname() << endl; //throw plaeyer confirmation
				location->removeItem(i); //remove item from location
				inventory.push_back(i); //add to player inventory
				cout << endl;
				return true;
			}
		}
		cout << "Item not at location" << endl; //if gone through whole loop throw player error
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
		Container* c = dynamic_cast<Container*>(i); //makes sure item is container

		if (c != nullptr) {
			c->open(this,location); //opens container
			return true;
		}

		else
		{
			cout << "Item is not a container" << endl; //if player tries to open reg item throw player error
			cout << endl;
			return false;
		}
	};

	void Player::printStatus()
	{
		cout << "Current Location: " << location->getname() << endl << "Steps Taken: " << getsteps() << endl; //displays location name and steps taken
		cout << "Current Inventory: " << endl; //displays current inventory list
		for (Item* i : inventory) {
			cout << "    " << i->getname() << endl;
		}
		cout << endl;
	}; // to display the current location, inventory, and number of steps
	
	void Player::addsteps() {
		steps++; //increases steps
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

