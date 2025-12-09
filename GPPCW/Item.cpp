#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;
#include "Item.h"
#include "Player.h"
#include "Location.h"


	//Constructor
Item::Item(string n, string de) :
		name(n),
		description(de)
	{
	}

	//destructor i think needed to make class checking work
Item::~Item() {}

	//Getters
string Item::getname() {
		return name;
	}
string Item::getdescription() {
		return description;
	}



	//Constructor
Container::Container(string n, string de, Item* k , list<Item*> cl) :
	Item(n, de),
	containerKey(k),
	isopen(false)

	{
		if (containerKey == nullptr) //No key container for like a character bag for example?
			isopen = true;

		for (Item* i : cl) {
			additem(i); //adds items to contents during constructor
		
		}

	}

	//Getters
	list<Item*> Container::getcontents() {
		return contents;
	}
	Item* Container::getkey() {
		return containerKey;
	}
	//Methods
	void Container::open(Player* p,Location* l)
	{
		isopen = true;
		vector<Item*> toMove; //List of all item to move needed to split up so i can remove later
		if (p->hasItem(containerKey)) { //check if you have key
			cout << "You opened the " << getname() << " and found: " << endl;

			for (Item* i : contents)
			{
				toMove.push_back(i); //add it to list 
			}

			for (Item* i : toMove)
			{
				cout << "    " << i->getname() << endl; 
				contents.remove(i); //item taken out of container
				l->additem(i); //adds item to location so player can take it
				p->takeItem(i); //Player takes item from location
				l->removeItem(this); //removes the container from location might remove this.
			}
			cout << endl;
		}
		else { //no key
			cout << "You need a: " << containerKey->getname() << " To open this!"; //throw player explanation 
		}
	}

	void Container::additem(Item* i)
	{
		//Check done before call
		contents.push_back(i); //adds to contents 
	}
