#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

#include "Item.h"
#include "Player.h"
#include "Location.h"

class Item {
protected:
	//Attributes
	string name;
	string description;

public:
	//Constructor
	Item(string n, string de);

	//destructor i think needed to make class checking work
	virtual ~Item();

	//Methods
	string getname();

	string getdescription();

};

class Container : public Item {
private:
	//Attributes
	list<Item*> contents; //Inside Container
	Item* containerKey; //Item to open it
	bool isopen; //Container open or not

public:
	//Constructor
	Container(string n, string de, Item* k = nullptr , list <Item*> cl = list<Item*>());
	//Methods
	list<Item*> getcontents();
	Item* getkey();
	void open(Player* p,Location* location);
	void additem(Item* i);

};