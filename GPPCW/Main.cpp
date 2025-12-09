#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;



#include "Item.h"
#include "Location.h"
#include "Player.h"

vector<Item*> createdItems;
vector<Location*> createdLocations;
map<int, map<string, int>> tempConnIds;
map<int, Location*> locationById;

Item* newItem(ifstream &f , string n) {
    string cline;
    string d;
    string c;
    list <Item*> tc;
    Item* k = nullptr;
    bool iscontainer = false;
    bool locked = false;


    while (getline(f, cline)) {
        if (cline.substr(0, cline.find(": ")) == "Item") { //done
            n = cline.substr(cline.find(": ") + 2);
        }
        else if (cline.substr(0, cline.find(": ")) == "Description") { //done
            d = cline.substr(cline.find(": ") + 2);
        }
        else if (cline.substr(0, cline.find(": ")) == "Contents") {
            iscontainer = true;
            size_t start = cline.find(": ") + 2;
            size_t end = cline.find(", ");


            while (end != string::npos) {
                c = cline.substr(start, end - start);
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == c) {
                        tc.push_back(i);
                        found = true;
                        break;
                    }

                }
                if (!found) {
                    std::cout << "Content item \"" << c << "\" not created yet or doesn't exist. Check game data structure!" << std::endl;
                    exit(EXIT_FAILURE);
                }

                start = end + 2;
                end = cline.find(", " , start);
            }

            bool found = false;
            c = cline.substr(start);
            for (Item* i : createdItems) {
                if (i->getname() == c) {
                    tc.push_back(i);
                    found = true;
                    break;
                }

            }
            if (!found) {
                std::cout << "Content item \"" << c << "\" not created yet or doesn't exist. Check game data structure!" << std::endl;
                exit(EXIT_FAILURE);
            }
        } 

        else if (cline.substr(0, cline.find(": ")) == "Keys") { //done
            locked = true;
            for (Item* i : createdItems) {
                if (i->getname() == cline.substr(cline.find(": ") + 2)) {
                    k = i;
                    break;
                }
            }

            if (!k) {
                cout << "key item " << c << " not created yet or doesn't exist check game data structure" << endl;
                exit(EXIT_FAILURE);
            }
        }

        else if (cline.empty()){
            break;
        }
    }

    Item* newItem = nullptr;

    if (iscontainer) {
        if (!locked) {
            k = nullptr; 
        }

        newItem =  new Container(n, d, k,tc);
    }
    else {
        newItem = new Item(n, d);
    }

    createdItems.push_back(newItem);
    return newItem;
    
}

Location* newLocation(ifstream& f, int i) {
    string cline;
    string n;
    string d;
    string co;
    int cn;
    Item* cd = nullptr;
    list <Item*> tc;
    map <string, Item*> dk;

    while (getline(f, cline)) {

        if (cline.substr(0, cline.find(": ")) == "Name") {
            n = cline.substr(cline.find(": ") + 2);
        }

        else if (cline.substr(0, cline.find(": ")) == "Description") {
            d = cline.substr(cline.find(": ") + 2);
        }

        else if (cline.substr(0, cline.find(": ")) == "Contents") {
            size_t start = cline.find(": ") + 2;
            size_t end = cline.find(", ");


            while (end != string::npos) {
                co = cline.substr(start, end - start);
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == co) {
                        tc.push_back(i);
                        found = true;
                        break;
                    }

                }
                if (!found) {
                    std::cout << "Content item \"" << co << "\" not created yet or doesn't exist. Check game data structure!" << std::endl;
                    exit(EXIT_FAILURE);
                }

                start = end + 2;
                end = cline.find(", ", start);
            }

            bool found = false;
            co = cline.substr(start);
            for (Item* i : createdItems) {
                if (i->getname() == co) {
                    tc.push_back(i);
                    found = true;
                    break;
                }

            }
            if (!found) {
                std::cout << "Content item \"" <<co<< "\" not created yet or doesn't exist. Check game data structure!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        else if (cline.substr(0, cline.find(" ")) == "NORTH") {
            size_t start =  cline.find(" ") + 1;
            size_t end = cline.find(", ");

            if (end != string::npos) {
                cn = stoi(cline.substr(start, end - start));


                string keyCheck = cline.substr(end + 2);
                

                cd = nullptr;
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == keyCheck) {
                        cd = i;
                        dk["NORTH"] = cd;

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "key item " << keyCheck << " not created yet or doesn't exist check game data structure" << endl;
                    exit(EXIT_FAILURE);
                }
            }

            else {
                cn = stoi(cline.substr(start));
            }
            
            tempConnIds[i]["NORTH"] = cn;
        }
        else if (cline.substr(0, cline.find(" ")) == "EAST") {
            size_t start = cline.find(" ") + 1;
            size_t end = cline.find(", ");

            if (end != string::npos) {
                cn = stoi(cline.substr(start, end - start));


                string keyCheck = cline.substr(end + 2);
                

                cd = nullptr;
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == keyCheck) {
                        cd = i;
                        dk["EAST"] = cd;

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "key item " << keyCheck << " not created yet or doesn't exist check game data structure" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else {
                cn = stoi(cline.substr(start));


            }
            tempConnIds[i]["EAST"] = cn;
        }

        else if (cline.substr(0, cline.find(" ")) == "SOUTH") {
            size_t start = cline.find(" ") + 1;
            size_t end = cline.find(", ");

            if (end != string::npos) {
                cn = stoi(cline.substr(start, end - start));


                string keyCheck = cline.substr(end + 2);
                

                cd = nullptr;
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == keyCheck) {
                        cd = i;
                        dk["SOUTH"] = cd;

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "key item " << keyCheck << " not created yet or doesn't exist check game data structure" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else {
                cn = stoi(cline.substr(start));


            }
            tempConnIds[i]["SOUTH"] = cn;
        }

        else if (cline.substr(0, cline.find(" ")) == "WEST") {
            size_t start = cline.find(" ") + 1;
            size_t end = cline.find(", ");

            if (end != string::npos) {
                cn = stoi(cline.substr(start, end - start));

                string keyCheck = cline.substr(end + 2);
                

                cd = nullptr;
                bool found = false;

                for (Item* i : createdItems) {
                    if (i->getname() == keyCheck) {
                        cd = i;
                        dk["WEST"] = cd;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "key item " << keyCheck << " not created yet or doesn't exist check game data structure" << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else {
                cn = stoi(cline.substr(start));
            }
            tempConnIds[i]["WEST"] = cn;
        }


        else if (cline.empty()) {
            break;
        }
    }


    Location* newLocal = new Location(i, n, d, tc, {}, dk);
    createdLocations.push_back(newLocal);
    locationById[i] = newLocal;

    return newLocal;

}



void readData() 
{
    ifstream worldData("gameData.txt");
    string classmarker;

    while (getline(worldData, classmarker)) {

        if (classmarker.substr(0,classmarker.find(": ")) == "Item") {
            string itemname;
            itemname = classmarker.substr(classmarker.find(": ") + 2);
            newItem(worldData,itemname);
        }
        else if (classmarker.substr(0, classmarker.find(": ")) == "Location") {
            int localid;
            localid = stoi(classmarker.substr(classmarker.find(": ") + 2));
            newLocation(worldData ,localid);
        }
        else if (classmarker.empty()) {
            cout << "\n";
        }
        else {
            cout << "attribute" << endl;
        }

    }
    string north = "NORTH";

    worldData.close();
    cout << "Items succesfully created: " << endl;
    for (Item* i : createdItems) {
        cout << "    " << i->getname() << endl;
    }
    cout << "Locations succesfully created: " << endl;
    for (Location* l : createdLocations) {
        cout << "    " << l->getname() << endl;
    }
}

void fixConnections() {
    for (Location* l : createdLocations) {
        int l_Id = l->getnumber();
        if (tempConnIds.count(l_Id)) {
            l->addConnections(tempConnIds[l_Id], locationById);
        }
    }
}


int main() {

    readData();

    fixConnections();

    list<Item*> playerInventory = {};
    Player player(createdLocations[0], playerInventory);

    bool quit = false;

        while (!quit) {
            string fullaction;

            cout << "Take an action" << endl;
            getline(cin, fullaction);
            for (int i = 0; i < fullaction.length(); i++) {
                fullaction[i] = toupper(fullaction[i]);
            }

            string action;
            string target;

            istringstream stream(fullaction);
            stream >> action;

            getline(stream, target);

            auto currentlocal = player.getlocation();

            cout << "Action is : " << action << endl;
            cout <<"Target is: " <<  target << endl;
           
            
            if (action == "LOOK") {
                currentlocal->print();
            }

            else if (action == "TAKE") {

                bool found = false;

                for (Item* i : currentlocal->getcontents()) {

                    string temp = i->getname();

                    for (char& c : temp) {
                        c = toupper(c);
                    }
                    cout << "DEBUG comparing: " << target << " to item: " << temp << endl;


                    if ((" " + temp) == target) {
                        player.takeItem(i);
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item not found" << endl;
                }
                
            }

            else if (action == "DROP") {
                bool found = false;

                for (Item* i : player.getinventory()) {

                    string temp = i->getname();

                    for (char& c : temp) {
                        c = toupper(c);
                    }
                    cout << "DEBUG comparing: " << target << " to item: " << temp << endl;


                    if ((" " + temp) == target) {
                        player.dropItem(i);
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item not found" << endl;
                }
            }


            else if (action == "OPEN") {
                bool found = false;

                for (Item* i : currentlocal->getcontents()) {

                    string temp = i->getname();

                    for (char& c : temp) { //converting to upper case
                        c = toupper(c);
                    }
                    cout << "DEBUG comparing: " << target << " to item: " << temp << endl; //cehck for item


                    if ((" " + temp) == target) { 
                        player.openItem(i);
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item not found" << endl;
                }
            }
            
            else if (action == "QUIT") {
                quit = true;
            }
            else if (action == "NORTH") {
                string NORTH = "NORTH";
                currentlocal->move(&player, NORTH);
            }
            else if (action == "EAST") {
                string EAST = "EAST";
                currentlocal->move(&player, EAST);
            }
            else if (action == "SOUTH") {
                string SOUTH = "SOUTH";
                currentlocal->move(&player,SOUTH );
            }
            else if (action == "WEST") {
                string WEST = "WEST";
                currentlocal->move(&player, WEST);
            }

            else if (action == "INVENTORY") {
                cout << "ITEMS IN BAG ARE: " << endl;
                for (Item* i : player.getinventory()) {
                    cout << "    " << i->getname() << endl;
                }
                cout << endl;
            }

            else if (action == "WHAT") {
                bool found = false;

                for (Item* i : createdItems) {

                    string upper = i->getname();
                    for (char& c : upper) {
                        c = toupper(c);
                    }
                    if ((" " + upper) == target) {
                        cout << "Item description: " << endl;
                        cout << "    " << i->getdescription() << endl;
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item doesnt exist" << endl;
                }
                
                cout << endl;
            }
            else if (action == "HELP") {
                cout << "// --------------------------" << endl;
                cout << "//  Usable Commands " << endl;
                cout << "// --------------------------" << endl;
                cout << endl;

                cout << "(Be careful of spaces with target item)" << endl;
                cout << " RedKey != Red Key" << endl;
                cout << endl;

                // 1. Look
                cout << "1. Look" << endl;
                cout << "   Action: Shows the name and description of your current location and lists all items in location." << endl;
                cout << "   Example: Look" << endl;
                cout << endl;

                // 2. Take [Item Name]
                cout << "2. Take [Item Name]" << endl;
                cout << "   Action: Picks up the item from the location and adds it to your inventory." << endl;
                cout << "   Example: Take red key" << endl;
                cout << endl;

                // 3. Drop [Item Name]
                cout << "3. Drop [Item Name]" << endl;
                cout << "   Action: Removes the specified item from your inventory and drops it at location." << endl;
                cout << "   Example: Drop red key" << endl;
                cout << endl;

                // 4. Open [Item Name]
                cout << "4. Open [Item Name]" << endl;
                cout << "   Action: Opens a container. Its contents are added to the location and the container dissapears." << endl;
                cout << "   Example: Open chest" << endl;
                cout << endl;

                // 5. Quit
                cout << "5. Quit" << endl;
                cout << "   Action: Exits the game." << endl;
                cout << "   Example: Quit" << endl;
                cout << "// --------------------------" << endl;
    
            }

            else {
                cout << "Unknown Input" << endl;
            };
    }

    return 0;
}


