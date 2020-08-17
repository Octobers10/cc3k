#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <string>
#include "floor.h"
#include "./players/player.h"
#include "direction.h"

class Game {
  char myRace;
  int floorLevel;
  int suitLevel;
  unique_ptr<Floor> currFloor;
  shared_ptr<Player> myPlayer;

  int totalLevel = 5;

  void initFloor();
  void initFloor(string fileName);

 public:
  

  void init(char race);
  void init(char race, string fileName);
  
  bool isFinished();  
  int getScore();
  
  string move(Direction direction);
  string move(Direction direction, string fileName);
  string attack(Direction direction);
  string usePotion(Direction direction);
  
  string printGame(string argument);
};

#endif
