#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#include "Item.h"
#include "Location.h"
#include "Player.h"

void readData() 
{

}
int main() {
    /*
    // --- Create Items ---
    Item* redKey = new Item("Red Key", "A small red key.");
    Item* rope = new Item("Rope", "A sturdy rope.");
    Container* chest = new Container("Chest", "An old wooden chest", redKey);
    Item* gem = new Item("Gem", "A shiny gem");
    string north = "north";

    // Add gem inside chest
    chest->additem(gem);

    // --- Create Locations ---
 
    list<Item*> loc1Items = {rope, chest};
    list<Item*> loc2Items = {gem};

    map<string, Location*> loc1Connections;
    map<string, Location*> loc2Connections;

    map<string, Item*> loc1DoorKeys;
    map<string, Item*> loc2DoorKeys;

    Location* alcove = new Location(1, "Small Alcove", "A cozy little alcove.", loc1Items, loc1Connections, loc1DoorKeys);
    Location* hall = new Location(2, "Grand Hall", "A vast, echoing hall.", loc2Items, loc2Connections, loc2DoorKeys);

    // Connect locations
    alcove->getconnection(north); // will be nullptr for now
    alcove->additem(redKey); // optional extra item
    alcove->getconnection(north); // placeholder

    // Connect alcove -> hall to north
    alcove->getconnection(north); // placeholder

    // Actually set the connection
    alcove->getconnection(north); // placeholder

    alcove->getcontents(); // demo

    // Set player starting location
    list<Item*> playerInventory = {};
    Player player(alcove, playerInventory);
    */


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

                    for (char& c : temp) {
                        c = toupper(c);
                    }
                    cout << "DEBUG comparing: " << target << " to item: " << temp << endl;


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


