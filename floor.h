#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <utility>
#include <memory>
#include <string>
#include "./players/player.h"
#include "./enemies/enemy.h"
#include "direction.h"
#include "./items/potion.h"
#include "./items/gold.h"
#include "./items/barriersuit.h"

using namespace std;

class Floor {
  int floorLevel;

  bool showStair;
  bool hasSuit;
  shared_ptr<Player> myPlayer;
  int spawnChamber;
  int stairChamber;

  vector<vector<char>> initBoard;
  vector<vector<char>> board;

  pair<int, int> playerPos;
  pair<int, int> stairPos;

  vector<shared_ptr<Potion>> potionList;
  vector<shared_ptr<Gold>> goldList;
  vector<shared_ptr<Enemy>> enemyList;
  shared_ptr<BarrierSuit> bSuit = nullptr;

  int width = 79;
  int height = 25;
  int enemies = 1;

  
  void genMap(string fileName, string boardName);
  
  char getCell(int i, int j) const;
  void setCell(int i, int j, char c);
  void unSetCell(int i, int j);
  
  bool checkAvailability(int i, int j);
  pair<int, int> genCell(string genFor);
  pair<int, int> genMove(int i, int j);
  pair<int, int> genMove(vector<pair<int, int>> availPos);
  pair<int, int> getPos(int currR, int currC, Direction direction);
  string moveEnemies();



  public:
  Floor(int floorLevel, bool showStair, bool hasSuit, shared_ptr<Player> myPlayer, int spawnChamber, int stairChamber, string mapFile);
  Floor(int floorLevel, shared_ptr<Player> myPlayer, string blankMapFile, string userMapFile);
  int getFloorLevel() const;
  int getStairChamber() const;

  vector<shared_ptr<Potion>> getPotionList() const;
  vector<shared_ptr<Gold>> getGoldList() const;
  vector<shared_ptr<Enemy>> getEnemyList() const;

  void initPlayerPos();
  void initStairPos();
  
  void genPotion(int potionNum);
  void genGold(int goldNum);
  void genSuit();
  void genEnemies(int enemyNum);
  void genCompass();
   
  string movePlayer(Direction direction);
  string fightPlayer(Direction direction);
  string usePotion(Direction direction);
  
  bool isFinishedLevel();
  
  string printFloor();
};

#endif
