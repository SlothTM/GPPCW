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

	//Methods
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
			additem(i);
		
		}

	}

	//Methods
	list<Item*> Container::getcontents() {
		return contents;
	}
	Item* Container::getkey() {
		return containerKey;
	}

	void Container::open(Player* p, Location* l)
	{
		isopen = true;
		vector<Item*> toMove;
		if (p->hasItem(containerKey)) {
			cout << "You opened the " << getname() << " and found: " << endl;

			for (Item* i : contents)
			{
				toMove.push_back(i);
			}

			for (Item* i : toMove)
			{
				cout << "    " << i->getname() << endl;
				contents.remove(i); //item taken out of container
				l->additem(i);
				p->takeItem(i); //adds item to location to stop player from softlocking
				l->removeItem(this);
			}
			cout << endl;
		}
		else {
			cout << "You need a: " << containerKey->getname() << " To open this!";
		}
	}

	void Container::additem(Item* i)
	{
		//Check done before call
		contents.push_back(i);
	}
