#include "game.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;



void move_position(Game &g, string command, string fileName);
void initialized(Game &g);
void initialized_file(Game &g, string filename);
void make_attack(Game &g, string command);
void use_potion(Game &g, string command);

int main(int argc, char *argv[]) {
    string fileName = "";
    srand(time(NULL));
    Game g;
    if (argc == 2){
        fileName = argv[1]; 
        initialized_file(g, fileName);
    } else {
        initialized(g);
    }
    
    string command = "";

    while (! g.isFinished()) {
        getline(cin, command);
        
        if ((command == "no")||(command == "so")||(command == "ea")||(command == "we")||
            (command == "ne")||(command == "nw")||(command == "se")||(command == "sw")) {
        
            move_position(g, command, fileName);
            continue;
        } else if ((command == "u no")||(command == "u so")||(command == "u ea")||(command == "u we")||
            (command == "u ne")||(command == "u nw")||(command == "u se")||(command == "u sw")) {
            use_potion(g, command);
            continue;
        } else if ((command == "a no")||(command == "a so")||(command == "a ea")||(command == "a we")||
            (command == "a ne")||(command == "a nw")||(command == "a se")||(command == "a sw")) {
            make_attack(g, command);
            continue;
        } else if (command == "r") {
            cout << "Are you sure you want to restart the game? (y/n)" << endl;
            string s;
            getline(cin, s);
            if (s == "y") {
              if (fileName == "") initialized(g);
              else initialized_file(g, fileName);
            }
            else if (s == "n") continue;
            else cout << "Please enter y or n." << endl;
        } else if (command == "q") {
            cout << "Are you sure you want to exit the game? (y/n)" << endl;
            string s;
            getline(cin, s);
            if (s == "y") return 0;
            else if (s == "n") continue;
            else cout << "Please enter y or n." << endl;
        } else if ((command == "w")||(command == "a")||(command == "s")||(command == "d")) {
          #ifdef SC
            move_position(g, command, fileName);
            continue;
          #endif 
          cout << "Invalid command." << endl;
        }

        else {
          cout << "Invalid command." << endl;
        }
    }


    cout << "You get "<< g.getScore() << " in total!" << endl;
}

void initialized_file(Game &g, string fileName){
    cout << "Please select a race from: " << endl;
    cout << "=================================================================" << endl;
    cout << "   Race(key)    HP    Atk    Def    Special Power" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "   Human(h)     140   20     20     Increase final score by 50%!" << endl;
    cout << "   Elves(e)     140   30     10     All potions are positive!" << endl;
    cout << "   Dwarf(d)     100   20     30     Double all golds value!" << endl;
    cout << "   Orc  (o)     180   30     25     1/2 all golds value!" << endl;
    cout << "=================================================================" << endl;
    cout << "press the corresponding key to start" << endl;
    cout << "press any keys if not choosing" << endl;
    string race;
    getline(cin, race);
    cout << "Command Menu:" << endl;
    cout << "=================================================================================" << endl;
    cout << "== (shortcut key) ===============================================================" << endl;
    cout << "   w s a d                       move up, down, left, right" << endl;
    cout << "== (direction key) ==============================================================" << endl;
    cout << "   no, so, ea, we                move north, south, east, west" << endl;
    cout << "   ne, nw, se, sw                move northeast, northwest, southeast, southwest" << endl;
    cout << "=================================================================================" << endl;
    cout << "   a <direction key)             attack the enemy at that direction" << endl;
    cout << "   u <direction key)             use the potion at that direction" << endl;
    cout << "   (walk on the gold to pick it up)" << endl;
    cout << "=================================================================================" << endl;

    if (race == "h"){
        g.init('h', fileName); 
    } else if (race == "e") {
        g.init('e', fileName);
    } else if (race == "d") {
        g.init('d', fileName); 
    } else if (race == "o") {
        g.init('o', fileName);
    } else {
        g.init('h', fileName); 
    }
    cout << g.printGame("Player character has spawned.");

}


void initialized(Game &g){
  cout << "Please select a race from: " << endl;
  cout << "=================================================================" << endl;
  cout << "   Race(key)    HP    Atk    Def    Special Power" << endl;
  cout << "-----------------------------------------------------------------" << endl;
  cout << "   Human(h)     140   20     20     Increase final score by 50%!" << endl;
  cout << "   Elves(e)     140   30     10     All potions are positive!" << endl;
  cout << "   Dwarf(d)     100   20     30     Double all golds value!" << endl;
  cout << "   Orc  (o)     180   30     25     1/2 all golds value!" << endl;
  cout << "=================================================================" << endl;
  cout << "press the corresponding key to start" << endl;
  cout << "press any keys if not choosing" << endl;
  string race;
  getline(cin, race);
  cout << "Command Menu:" << endl;
  cout << "=================================================================================" << endl;
  cout << "== (shortcut key) ===============================================================" << endl;
  cout << "   w s a d                       move up, down, left, right" << endl;
  cout << "== (direction key) ==============================================================" << endl;
  cout << "   no, so, ea, we                move north, south, east, west" << endl;
  cout << "   ne, nw, se, sw                move northeast, northwest, southeast, southwest" << endl;
  cout << "=================================================================================" << endl;
  cout << "   a <direction key)             attack the enemy at that direction" << endl;
  cout << "   u <direction key)             use the potion at that direction" << endl;
  cout << "   (walk on the gold to pick it up)" << endl;
  cout << "=================================================================================" << endl;

  if (race == "h"){
      g.init('h'); 
  } else if (race == "e") {
      g.init('e');
  } else if (race == "d") {
      g.init('d'); 
  } else if (race == "o") {
      g.init('o');
  } else {
      g.init('h'); 
  }
  cout << g.printGame("Player character has spawned.");
}


Direction getDirection(string command) {
  Direction d;
  if ((command == "no")|| (command == "u no") || (command == "a no")){
    d = Direction::no;
  }
  if ((command == "so")|| (command == "u so") || (command == "a so")){
    d = Direction::so;
  }
  if ((command == "ea")|| (command == "u ea") || (command == "a ea")){
    d = Direction::ea;
  }
  if ((command == "we")|| (command == "u we") || (command == "a we")){
    d = Direction::we;
  }
  if ((command == "ne")|| (command == "u ne") || (command == "a ne")){
    d = Direction::ne;
  }
  if ((command == "nw")|| (command == "u nw") || (command == "a nw")){
    d = Direction::nw;
  }
  if ((command == "se")|| (command == "u se") || (command == "a se")){
    d = Direction::se;
  }
  if ((command == "sw")|| (command == "u sw") || (command == "a sw")){
    d = Direction::sw;
  }

  #ifdef SC
  if (command == "w"){
      d = Direction::no;
  } else if (command == "a"){
      d = Direction::we;
  } else if (command == "s"){
      d = Direction::so;
  } else if (command == "d"){
      d = Direction::ea;
  }
  #endif
  
  return d;
}

void move_position(Game &g, string command, string fileName){
  Direction d = getDirection(command);    
  if (fileName == "") {
    string action = g.move(d);
    cout << g.printGame(action);
  } else {
    string action = g.move(d, fileName);
    cout << g.printGame(action);
  }
}

void make_attack(Game &g, string command){
  Direction d = getDirection(command);    
  string action = g.attack(d);
  cout << g.printGame(action);
}

void use_potion(Game &g, string command){
  Direction d = getDirection(command);    
  string action = g.usePotion(d);
  cout << g.printGame(action);
}



