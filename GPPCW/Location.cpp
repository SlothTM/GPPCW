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
		connections(cn),
		doorKey(dk)
	{
	for (Item* i : co) 
	{
		additem(i); //add item to collection in construction
	}
	}



	//gETTERS
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

	//Methods
	void Location::print()
	{
		cout << "You look around the room" << endl; //print location info
		cout << name << endl;
		cout << description << endl;
		cout << "Items in location are: " << endl;
		for (Item* i : contents) // loop through contents and print each item
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
		Location* moveto = getconnection(direction); //location to move to
		Item* keyneeded = getdoorkey(direction); //check if key needed

		if (moveto == nullptr) { //if no corresponding connection throw player error
			cout << "There is nowhere to go in that direction" << endl;
			return false;
		}

		if (keyneeded != nullptr && !player->hasItem(keyneeded)) { //if player doesnt have key and a key is really needed throw player error
			cout << "You do not have the required key go find a: " << keyneeded->getname() << endl;
			return false;
		}
		player->addsteps(); //add steps each movement
		player->setLocation(moveto); //change player location
		moveto->print(); //print new locations info
		return true;
	}

	void Location::addConnections(map<string, int>& connIds, map<int, Location*>& locationById) { //takes temp id and links to location ids
		for (auto& pair : connIds) { // for each pair in temp id
			string dir = pair.first; //in temp id take direction the first of pair
			int l_id = pair.second; // and id the second of pair

			auto iterator = locationById.find(l_id); //loops throufh yo find corresponding temp id and location real id (should use this logic for other code)

			if (iterator != locationById.end()) { //if the iterator isnt the end of map
				connections[dir] = iterator->second; //then set the direction of locations connection to the found id
			}
			else { //debug error means location connected to non existent location
				cout << "Warning: Location ID " << l_id << " not found for connection " << dir << endl;
			}
		}
	}