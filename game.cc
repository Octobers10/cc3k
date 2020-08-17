#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "game.h"
#include "human.h"
#include "dwarf.h"
#include "elves.h"
#include "orc.h"

using namespace std;


void Game::initFloor() {
  bool hasSuit = false;
  if (floorLevel == suitLevel) hasSuit = true;

  int spawnChamber, stairChamber;
  
  if (floorLevel == 1) {
    spawnChamber = 0;
    stairChamber = 0;
  } else {
    spawnChamber = currFloor->getStairChamber();
    stairChamber = 0;
  }
  currFloor = make_unique<Floor> (floorLevel, false, hasSuit, myPlayer, spawnChamber, stairChamber, "blankMap.txt");
  currFloor->initPlayerPos();
  currFloor->initStairPos();
  currFloor->genPotion(10);
  currFloor->genGold(10);
  currFloor->genSuit();
  currFloor->genEnemies(20);
  currFloor->genCompass();

}


void Game::initFloor(string fileName) {
  currFloor = make_unique<Floor> (floorLevel, myPlayer, "blankMap.txt", fileName);
}


void Game::init(char race) {
  myRace = race;
  floorLevel = 1;
  switch (race) {
  case 'e': 
    myPlayer = make_shared<Elves> (0, 0);
    break;
  case 'd':
    myPlayer = make_shared<Dwarf> (0, 0);
    break;
  case 'o':
    myPlayer = make_shared<Orc> (0, 0);
    break;
  default:
    myPlayer = make_shared<Human> (0, 0);
    break;
  }

  suitLevel = rand() % totalLevel + 1;
  initFloor();
}

void Game::init(char race, string fileName) {
  myRace = race;
  floorLevel = 1;
  switch(race) {
  case 'e':
    myPlayer = make_shared<Elves> (0, 0);
    break;
  case 'd':
    myPlayer = make_shared<Dwarf> (0, 0);
    break;
  case 'o':
    myPlayer = make_shared<Orc> (0, 0);
    break;
  default:
    myPlayer = make_shared<Human> (0, 0);
    break;
  }

  initFloor(fileName);
}

bool Game::isFinished() {
  if (floorLevel == totalLevel && currFloor->isFinishedLevel()) return true; 
  else if (myPlayer->getHP() <= 0) return true;
  else {
    return false;
  }
}

int Game::getScore() {
  int score = myPlayer->getGold();
  if (myRace == 'h') {
    double multiplier = 1.5;
    score = ceil(multiplier * score);
  }
  return score;
}

string Game::move(Direction direction) {
  string action = currFloor->movePlayer(direction);
  
  if (floorLevel != totalLevel && currFloor->isFinishedLevel()) {
    floorLevel += 1;
    initFloor();
  }
  return action;
}

string Game::move(Direction direction, string fileName) {
  string action = currFloor->movePlayer(direction);
  
  if (floorLevel != totalLevel && currFloor->isFinishedLevel()) {
    floorLevel += 1;
    initFloor(fileName);
  }
  return action;
}

string Game::attack(Direction direction) {
  string action = currFloor->fightPlayer(direction);
  return action;
}

string Game::usePotion(Direction direction) {
  string action = currFloor->usePotion(direction);
  return action;
}


string Game::printGame(string argument) {
  string printBoard = currFloor->printFloor();
  string race = "";
  switch (myRace) {
  case 'h': 
    race = "Human";
    break;
  case 'o': 
    race = "Orc";
    break;
  case 'd': 
    race = "Dwarf";
    break;
  case 'e': 
    race = "Elves";
    break;
  }
  ostringstream goldnum;
  goldnum << std::fixed;
  goldnum << std::setprecision(1);
  goldnum << myPlayer->getGold();
  printBoard = printBoard + "Race: " + race + " Gold: " + goldnum.str();
  printBoard = printBoard + "                                                  Floor " + to_string(floorLevel) + "\n";
  int hp = myPlayer->getHP();
  if (hp <= 0) hp = 0; 
  printBoard = printBoard + "HP: " + to_string(hp) + "\n";
  printBoard = printBoard + "Atk: " + to_string(myPlayer->getAtk()) + "\n";
  printBoard = printBoard + "Def: " + to_string(myPlayer->getDef()) + "\n";
  printBoard = printBoard + "Action: " + argument + "\n";
  return printBoard;
}
