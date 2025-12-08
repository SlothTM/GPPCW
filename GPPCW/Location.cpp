#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

#include "Item.h"
#include "Location.h"
#include "Player.h"

	//Constructor
Location::Location(int i, string n, string de, list <Item*> co, map <string, Location*> cn, map <string, Item*> dk) :
		id(i),
		name(n),
		description(de),
		contents(co),
		connections(cn),
		doorKey(dk)
	{
	}


	//Methods
	int Location::getnumber()
	{
		return id;
	}

	string Location::getname()
	{
		return name;
	}

	string Location::getdescription()
	{
		return description;
	}

	list<Item*>& Location::getcontents()
	{
		return contents;
	}

	Item* Location::getdoorkey(string& direction)
	{
		for (auto& dir : doorKey)
		{
			if (dir.first == direction) {
				return dir.second;
			}
		}
		return nullptr;
	}

	Location* Location::getconnection(string& direction)
	{
		for (auto& dir : connections)
		{
			if (dir.first == direction) {
				return dir.second;
			}
		}

		return nullptr;
	}

	void Location::print()
	{
		cout << "You look around the room" << endl;
		cout << name << endl;
		cout << description << endl;
		cout << "Items in location are: " << endl;
		for (Item* i : contents)
		{
			cout << "    " << i->getname() << endl;
		}
		cout << endl;
	}
	void Location::removeItem(Item* i) {
		//Check done before called
		list<Item*>& tempContents = getcontents();


		for (auto iterator = tempContents.begin(); iterator != tempContents.end(); ++iterator) //loops through the list looking for....
		{
			if ((*iterator)->getname() == i->getname()) { //... the item NAME
				tempContents.erase(iterator); //If it finds name takes it out of the list
				break; //Stops there
			}
		}

	}

	void Location::additem(Item* i) {
		//Check done before call
		contents.push_back(i);
	}

	bool Location::move(Player* player, string& direction)
	{
		Location* moveto = getconnection(direction);
		Item* keyneeded = getdoorkey(direction);

		if (moveto == nullptr) {
			cout << "There is nowhere to go in that direction" << endl;
			return false;
		}

		if (keyneeded != nullptr && !player->hasItem(keyneeded)) {
			cout << "You do not have the required key go find a: " << keyneeded->getname() << endl;
			return false;
		}
		player->addsteps();
		player->setLocation(moveto);
		moveto->print();
		return true;
	}
