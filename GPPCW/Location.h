#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
using namespace std;

class Player;
class Item;

class Location {
private:

	//Attributes
	int id; //Location Id (Number in cw brief)
	string name;
	string description;
	list <Item*> contents; //What items are in location
	map<string, Location*> connections; // Where can you go 
	map<string, Item*> doorKey; //Key needed for each exit

public:
	//Constructor
	Location(int i, string n, string de, list <Item*> co, map <string, Location*> cn, map <string, Item*> dk);


		//Methods
		int getnumber();

		string getname();

		string getdescription();

		list<Item*>& getcontents();

		Item* getdoorkey(string& direction);
		Location* getconnection(string& direction);

		void print();
		void removeItem(Item* i);

		void additem(Item* i);

		bool move(Player* player, string& direction);
};