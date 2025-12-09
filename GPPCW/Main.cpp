#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;


//include all header files
#include "Item.h"
#include "Location.h"
#include "Player.h"
//global variables
vector<Item*> createdItems; //ALL items created after read data is run
vector<Location*> createdLocations; //same as above but for locations
map<int, map<string, int>> tempConnIds; //temporarily stores connected IDs for use later
map<int, Location*> locationById; // temp stores each location by its id (may not need this)

Item* newItem(ifstream &f , string n) {
    string cline; //current line
    string d; //description
    string c; // contents
    list <Item*> tc; //temp contents 
    Item* k = nullptr; // default to nullptr if i want auto open (prob wont use)
    bool iscontainer = false; 
    bool locked = false;


    while (getline(f, cline)) {
        if (cline.substr(0, cline.find(": ")) == "Description") { //Check for description tag
            d = cline.substr(cline.find(": ") + 2); //assign contents after tag to variable
        }
        else if (cline.substr(0, cline.find(": ")) == "Contents") { //Check for contents tag
            iscontainer = true;
            size_t start = cline.find(": ") + 2; //start after tag
            size_t end = cline.find(", "); //end after first comma


            while (end != string::npos) { //if there is a comma do this
                c = cline.substr(start, end - start); // inbetween current space and comma
                bool found = false;

                for (Item* i : createdItems) { // makes sure items exist before adding them
                    if (i->getname() == c) { //if item exists find it and add it to contents tc
                        tc.push_back(i);
                        found = true;
                        break;
                    }

                }
                if (!found) {
                    cout << "Content item \"" << c << "\" not created yet or doesn't exist. Check game data structure! " << n << endl; //for debug if items arent in correct order will fail
                    exit(EXIT_FAILURE);
                }

                start = end + 2;
                end = cline.find(", " , start);
            }
            // loop above stops before last item this final loop completes it code is same as above
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
                cout << "Content item \"" << c << "\" not created yet or doesn't exist. Check game data structure!" << endl;
                exit(EXIT_FAILURE);
            }
        } 

        else if (cline.substr(0, cline.find(": ")) == "Keys") { //check for key tag
            locked = true;
            for (Item* i : createdItems) { //looks through all items to make sure it exists 
                if (i->getname() == cline.substr(cline.find(": ") + 2)) { // finds it 
                    k = i; // sets key to item if its found
                    break;
                }
            }

            if (!k) {
                cout << "key item " << c << " not created yet or doesn't exist check game data structure" << endl; // if the item is definitly locked but key isnt found throw error to make sure its in right order
                exit(EXIT_FAILURE);
            }
        }

        else if (cline.empty()){ //One a linebreak is reacched stop looping and start return sequence
            break;
        }
    }

    Item* newItem = nullptr; //temp item

    if (iscontainer) { //if its container
        if (!locked) { //and not locked
            k = nullptr;  //no key needed
        }

        newItem =  new Container(n, d, k,tc); //create container
    }
    else {
        newItem = new Item(n, d); //if its not a container just make a regular item
    }

    createdItems.push_back(newItem); //adds it to big list of items
    return newItem; //return the item to read data
    
}

Location* newLocation(ifstream& f, int i) {
    string cline; //current line
    string n; //name
    string d; //desc
    string co; //collection
    int cn; //connection numb
    Item* cd = nullptr; //key for door
    list <Item*> tc; //temporary collection
    map <string, Item*> dk; //map for doorkey 

    while (getline(f, cline)) {

        if (cline.substr(0, cline.find(": ")) == "Name") { //tag check
            n = cline.substr(cline.find(": ") + 2); //assign
        }

        else if (cline.substr(0, cline.find(": ")) == "Description") {//tag check
            d = cline.substr(cline.find(": ") + 2); //assign
        }

        else if (cline.substr(0, cline.find(": ")) == "Contents") {//tag check
            size_t start = cline.find(": ") + 2; //start after tag
            size_t end = cline.find(", "); //end after first comma


            while (end != string::npos) { //if there is comma
                co = cline.substr(start, end - start); //inbetween current item and next comma
                bool found = false;

                for (Item* i : createdItems) { //check item is in list
                    if (i->getname() == co) {
                        tc.push_back(i); //if it is add it to temp contents
                        found = true;
                        break;
                    }

                }
                if (!found) {
                    cout << "Content item \"" << co << "\" not created yet or doesn't exist. Check game data structure!" << endl; //Debug again
                    exit(EXIT_FAILURE); 
                }

                start = end + 2;
                end = cline.find(", ", start); //itterating changing the start and end to the start and end for next item
            }
            //Final item again
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
                cout << "Content item \"" <<co<< "\" not created yet or doesn't exist. Check game data structure!" << endl; //debugg
                exit(EXIT_FAILURE);
            }
        }

        //DIRECTION CODE ALL THE SAME ONLY DIFF IS CHANGING NORTH TO EAST ETC...

        else if (cline.substr(0, cline.find(" ")) == "NORTH") { //tag check
            size_t start =  cline.find(" ") + 1; //check between space just after direction to get its connection
            size_t end = cline.find(", "); //ends at ccomma

            if (end != string::npos) { //check if there is something after space
                cn = stoi(cline.substr(start, end - start)); //if there is convert the string number to an int number


                string keyCheck = cline.substr(end + 2); //another check to see if there is more after number(connection id) thus giving us the key item
                

                cd = nullptr; //reset cd item
                bool found = false; //found flag

                for (Item* i : createdItems) { //checking all items and looking for the item after connection id
                    if (i->getname() == keyCheck) { 
                        cd = i; 
                        dk["NORTH"] = cd; //assines door key to each direction (The north here will change to each corresponding direction)

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "key item " << keyCheck << " not created yet or doesn't exist check game data structure" << endl; //Debugging for game data order
                    exit(EXIT_FAILURE);
                }
            }

            else { //if there is no comma it will simply take the number right after space
                cn = stoi(cline.substr(start)); // can take rest of the line allowing for expansion
            }
            
            tempConnIds[i]["NORTH"] = cn; //Finally adds the connection id , first location id then direction and finally target id.
        }
        else if (cline.substr(0, cline.find(" ")) == "EAST") { //tag check
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

        else if (cline.substr(0, cline.find(" ")) == "SOUTH") { //tag check
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

        else if (cline.substr(0, cline.find(" ")) == "WEST") { //tag check
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
#
        else if (cline.substr(0, cline.find(" ")) == "IN") { //tag check
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
                        dk["IN"] = cd;
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
            tempConnIds[i]["IN"] = cn;
            }

        else if (cline.substr(0, cline.find(" ")) == "OUT") { //tag check
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
                        dk["OUT"] = cd;
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
            tempConnIds[i]["OUT"] = cn;
        }

        else if (cline.empty()) { //One a linebreak is reacched stop looping and start return sequence
            break;
        }
    }


    Location* newLocal = new Location(i, n, d, tc, {}, dk); //creates location with empty connections to stop things not created yet from breaking game
    createdLocations.push_back(newLocal); //adds to big list of locations
    locationById[i] = newLocal; //adds to list for id reffering (may not need)

    return newLocal; // returns location to readata

}



void readData() 
{
    ifstream worldData("gameData.txt"); //open and read gamedata txt
    string classmarker; //holds current line

    while (getline(worldData, classmarker)) { //while there are lines to read in gameData.txt

        if (classmarker.substr(0,classmarker.find(": ")) == "Item") { //if the characters before the colon are item do this
            string itemname; //first line contains items name
            itemname = classmarker.substr(classmarker.find(": ") + 2); //after the colon is item name
            newItem(worldData,itemname);//pass in item name
        }
        else if (classmarker.substr(0, classmarker.find(": ")) == "Location") { //if the characters before the colon are location do this
            int localid; //first line contains locations id
            localid = stoi(classmarker.substr(classmarker.find(": ") + 2)); //after colon is location id
            newLocation(worldData ,localid); //pass in location id to item
        }
    }

    worldData.close(); //close file 
    
    //Debugging making sure every item and location are created
    cout << "Items succesfully created: " << endl;
    for (Item* i : createdItems) {
        cout << "    " << i->getname() << endl;
    }
    cout << "Locations succesfully created: " << endl;
    for (Location* l : createdLocations) {
        cout << "    " << l->getname() << endl;
    }
}

void fixConnections() { //After everything is created locations can now be linked
    for (Location* l : createdLocations) { //for every location
        int l_Id = l->getnumber(); //get its id
        if (tempConnIds.count(l_Id)) { //checks key actually exists
            l->addConnections(tempConnIds[l_Id], locationById);
        }
        else { //debugging making sure you can get out of each room
            cout << "Location doesnt have links go fix that";
        }
    }
}


int main() {

    readData(); //call read data before connections to make sure eveything exists first

    fixConnections();

    list<Item*> playerInventory = {}; // create player inventory so you can...
    Player player(createdLocations[0], playerInventory); //create the player at the first location in location list

    bool quit = false; //to stop game loop 

    cout << "Yokoso! If you need any help just type help in the consol and a command list will appear" << endl << "Enjoy the game!" << endl << endl << endl << endl; //Intro

        while (!quit) { //While player hasnt quit run game loop
            string fullaction;

            cout << "What will you do next?..." << endl;
            cout << endl;//Player Prompt
            getline(cin, fullaction); //take the line
            for (int i = 0; i < fullaction.length(); i++) {
                fullaction[i] = toupper(fullaction[i]); //take every character and change it to uppercase for normalisation
            }

            string action; //need to split target and action
            string target;

            istringstream stream(fullaction); //split by spaces
            stream >> action; //everything before first space goes into action

            getline(stream, target); //everything else goes into target this allows for items like "Red Key" which have a space

            auto currentlocal = player.getlocation(); //players current location

            
            if (action == "LOOK") { //if action is ...
                currentlocal->print(); //do look function 
            }

            if (action == "STATUS") { //if action is ...
                player.printStatus(); //do look function 
            }

            else if (action == "TAKE") { //if action is ...

                bool found = false;

                for (Item* i : currentlocal->getcontents()) { //loop thrugh items in local and find the target item

                    string temp = i->getname();

                    for (char& c : temp) { //normalisation
                        c = toupper(c);
                    }


                    if ((" " + temp) == target) { //added space for normalisation trimming felt complicated this works
                        player.takeItem(i); //calls take item after all checks done
                        found = true;
                        break;
                    }

                }

                if (!found) { //if item not found throw player error
                    cout << "Item not found" << endl;
                }

                cout << endl;
            }

            else if (action == "DROP") { //if action is ...
                bool found = false;

                for (Item* i : player.getinventory()) { //Essentially same as above

                    string temp = i->getname();

                    for (char& c : temp) {
                        c = toupper(c);
                    }


                    if ((" " + temp) == target) {
                        player.dropItem(i);
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item not found" << endl;
                }
                cout <<  endl;
            }


            else if (action == "OPEN") {//if action is ...
                bool found = false;

                for (Item* i : currentlocal->getcontents()) { //Same as above

                    string temp = i->getname();

                    for (char& c : temp) { //converting to upper case
                        c = toupper(c);
                    }


                    if ((" " + temp) == target) { 
                        player.openItem(i);
                        found = true;
                        break;
                    }

                }

                if (!found) {
                    cout << "Item not found" << endl;
                }
                cout << endl;
            }
            
            else if (action == "QUIT") {//if action is ...
                quit = true; //quit gameloop
            }

            else if (action == "NORTH") {//if action is ...
                string NORTH = "NORTH";
                currentlocal->move(&player, NORTH); //move player in location
            }
            else if (action == "EAST") { //if action is ...
                string EAST = "EAST";
                currentlocal->move(&player, EAST);//move player in location
            }
            else if (action == "SOUTH") {//if action is ...
                string SOUTH = "SOUTH";
                currentlocal->move(&player,SOUTH );//move player in location
            }
            else if (action == "WEST") {//if action is ...
                string WEST = "WEST";
                currentlocal->move(&player, WEST);//move player in location
            }
            else if (action == "OUT") {//if action is ...
                string OUT = "OUT";
                currentlocal->move(&player, OUT);//move player in location
                }
            else if (action == "IN") {//if action is ...
                string IN = "IN";
                currentlocal->move(&player, IN);//move player in location
            }

            else if (action == "INVENTORY") {//if action is ...
                cout << "ITEMS IN BAG ARE: " << endl;
                for (Item* i : player.getinventory()) {
                    cout << "    " << i->getname() << endl;
                }
                cout << endl;
            }



            else if (action == "WHAT") {//if action is ...
                bool found = false;

                for (Item* i : createdItems) { //loop through every item created

                    string upper = i->getname();
                    for (char& c : upper) {
                        c = toupper(c); //normalise for check
                    }
                    if ((" " + upper) == target) { //once item found output description
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

            else if (action == "HELP") { //Added help so players know what they can do
                cout << "// --------------------------" << endl;
                cout << "//  Usable Commands " << endl;
                cout << "// --------------------------" << endl;
                cout << endl;

                cout << "(Be careful of spaces with target item)" << endl;
                cout << " RedKey != Red Key" << endl;
                cout << endl;

                cout << "1. Look" << endl;
                cout << "   Action: Shows the name and description of your current location and lists all items in location." << endl;
                cout << "   Example: Look" << endl;
                cout << endl;

                cout << "2. Take [Item Name]" << endl;
                cout << "   Action: Picks up the item from the location and adds it to your inventory." << endl;
                cout << "   Example: Take red key" << endl;
                cout << endl;

                cout << "3. Drop [Item Name]" << endl;
                cout << "   Action: Removes the specified item from your inventory and drops it at location." << endl;
                cout << "   Example: Drop red key" << endl;
                cout << endl;

                cout << "4. Open [Item Name]" << endl;
                cout << "   Action: Opens a container. Its contents are added to the location and the container dissapears." << endl;
                cout << "   Example: Open chest" << endl;
                cout << endl;

                cout << "5. Inventory" << endl;
                cout << "   Action: Opens and lists your inventory out to you." << endl;
                cout << "   Example: im sure youll figure this one out ;)" << endl;
                cout << endl;

                cout << "6. Direction" << endl;
                cout << "   Action: go in the direction stated in or out also works" << endl;
                cout << "   Example: North" << endl;
                cout << endl;

                cout << "7. What [Item Name]" << endl;
                cout << "   Action: describes any item in the game to you as long as you know its name" << endl;
                cout << "   Example: what chest" << endl;
                cout << endl;

                cout << "8. STATUS" << endl;
                cout << "   Action: displays steps taken , where you are , and your current inventory" << endl;
                cout << "   Example: STATUS" << endl;
                cout << endl;

                cout << "9. Quit" << endl;
                cout << "   Action: Exits the game." << endl;
                cout << "   Example: Quit" << endl;
                cout << "// --------------------------" << endl;
    
            }

            else {
                cout << "Unknown Input" << endl;
            } //input unknown throw player error

 
    }
           for (Item* i : createdItems) {
                delete i;
            }

            for (Location* l : createdLocations) {
                delete l;
            }
    return 0;
}


