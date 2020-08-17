#include <algorithm>
#include <iostream>

#include <fstream>
#include <cstdlib>
#include <ctime>

#include "enemy.h"
#include "floor.h"
#include "vampire.h"
#include "werewolf.h"
#include "troll.h"
#include "goblin.h"
#include "merchant.h"
#include "dragon.h"
#include "phoenix.h"

using namespace std;

void Floor::genMap(string fileName, string boardName)
{
  ifstream map{fileName};
  string sRow;
  while (getline(map, sRow))
  {
    vector<char> vRow(sRow.begin(), sRow.end());
    if (boardName == "board")
    {
      board.emplace_back(vRow);
    }
    else if (boardName == "initBoard")
    {
      initBoard.emplace_back(vRow);
    }
  }
}

Floor::Floor(int floorLevel, bool showStair, bool hasSuit, shared_ptr<Player> myPlayer, int spawnChamber, int stairChamber, string mapFile)
{
  this->floorLevel = floorLevel;
  this->showStair = showStair;
  this->hasSuit = hasSuit;
  this->myPlayer = myPlayer;
  this->spawnChamber = spawnChamber;
  this->stairChamber = stairChamber;
  myPlayer->resetPlayer();

  genMap(mapFile, "board");
  genMap(mapFile, "initBoard");
}

Floor::Floor(int floorLevel, shared_ptr<Player> myPlayer, string blankMapFile, string userMapFile)
{
  this->floorLevel = floorLevel;
  this->myPlayer = myPlayer;
  myPlayer->resetPlayer();

  //set default/won't use field values
  showStair = true;
  hasSuit = false;
  spawnChamber = 0;
  stairChamber = 0;

  genMap(blankMapFile, "initBoard");
  //cerr << floorLevel << endl;
  int lineStart = 25 * (floorLevel - 1);
  int lineEnd = 25 * floorLevel;
  ifstream map{userMapFile};
  string sRow;

  for (int i = 0; getline(map, sRow); ++i)
  {
    if ((i >= lineStart) && (i <= lineEnd))
    {
      vector<char> vRow(sRow.begin(), sRow.end());
      board.emplace_back(vRow);
    }
  }

  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      char cell = getCell(i, j);
      switch (cell)
      {
      case 'N':
      {
        shared_ptr<Enemy> aGoblin = make_shared<Goblin>(i, j);
        enemyList.emplace_back(aGoblin);
        enemies += 1;
      }
      break;
      case 'W':
      {
        shared_ptr<Enemy> aWerewolf = make_shared<Werewolf>(i, j);
        enemyList.emplace_back(aWerewolf);
        enemies += 1;
      }
      break;
      case 'V':
      {
        shared_ptr<Enemy> aVampire = make_shared<Vampire>(i, j);
        enemyList.emplace_back(aVampire);
        enemies += 1;
      }
      break;
      case 'T':
      {
        shared_ptr<Enemy> aTroll = make_shared<Troll>(i, j);
        enemyList.emplace_back(aTroll);
        enemies += 1;
      }
      break;
      case 'X':
      {
        shared_ptr<Enemy> aPhoenix = make_shared<Phoenix>(i, j);
        enemyList.emplace_back(aPhoenix);
        enemies += 1;
      }
      break;
      case 'M':
      {
        shared_ptr<Enemy> aMerchant = make_shared<Merchant>(i, j);
        enemyList.emplace_back(aMerchant);
        enemies += 1;
      }
      break;
      case '0':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "RH");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '1':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "BA");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '2':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "BD");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '3':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "PH");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '4':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "WA");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '5':
      {
        shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, "WD");
        potionList.emplace_back(aPotion);
        setCell(i, j, 'P');
      }
      break;
      case '6':
      {
        shared_ptr<Gold> aGold = make_shared<Gold>(i, j, 1, true);
        goldList.emplace_back(aGold);
        setCell(i, j, 'G');
      }
      break;
      case '7':
      {
        shared_ptr<Gold> aGold = make_shared<Gold>(i, j, 2, true);
        goldList.emplace_back(aGold);
        setCell(i, j, 'G');
      }
      break;
      case '8':
      {
        shared_ptr<Gold> aGold = make_shared<Gold>(i, j, 4, true);
        goldList.emplace_back(aGold);
        setCell(i, j, 'G');
      }
      break;
      case '9':
      {
        shared_ptr<Gold> aGold = make_shared<Gold>(i, j, 6, false);
        goldList.emplace_back(aGold);
        setCell(i, j, 'G');
      }
      break;
      case '@':
      {
        playerPos = make_pair(i, j);
        myPlayer->setPosition(i, j);
      }
      break;
      case '\\':
        stairPos = make_pair(i, j);
        break;
      case 'B':
        hasSuit = true;
        break;
      case 'C':
	showStair = false;
	break;
      }
    }
  }
  for (auto it : goldList)
  {

    if (it->getAmount() == 6)
    {

      int goldR = it->getPosition().first;
      int goldC = it->getPosition().second;
      for (int i = goldR - 1; i <= goldR + 1; ++i)
      {
        for (int j = goldC - 1; j <= goldC + 1; ++j)
        {
          if (getCell(i, j) == 'D')
          {
            bool isTaken = false;
            shared_ptr<Enemy> aDragon;
            for (auto enemyItr : enemyList)
              {
                if (enemyItr->getPosition().first == i && enemyItr->getPosition().second == j)
                  {
                    isTaken = true;
                    break;
                  }
              }
              //modified
              //shared_ptr<Enemy> aDragon = dynamic_pointer_cast<Enemy>(make_shared<Dragon> (i, j, it));
              if (isTaken == false)
                {  
                  aDragon = make_shared<Dragon>(i, j, it);
                  enemyList.emplace_back(aDragon);
                  enemies += 1;
                  break;
                }
              else 
                {
                  continue;
                }
          }
        }
      }
    }
  }
  playerPos = myPlayer->getPosition();
  setCell(playerPos.first, playerPos.second, '@');
}

int Floor::getFloorLevel() const
{
  return floorLevel;
}

int Floor::getStairChamber() const
{
  return stairChamber;
}

vector<shared_ptr<Potion>> Floor::getPotionList() const
{
  return potionList;
}

vector<shared_ptr<Gold>> Floor::getGoldList() const
{
  return goldList;
}

vector<shared_ptr<Enemy>> Floor::getEnemyList() const
{
  return enemyList;
}

char Floor::getCell(int i, int j) const
{
  return board[i][j];
}

void Floor::setCell(int i, int j, char c)
{
  board[i][j] = c;
}

void Floor::unSetCell(int i, int j)
{
  board[i][j] = initBoard[i][j];
}

bool Floor::checkAvailability(int i, int j)
{ //checks for availability of a chamber cell
  char cell = getCell(i, j);
  if (cell == '.')
    return true;
  else
    return false;
}

pair<int, int> Floor::genCell(string genFor)
{ //generate a cell for genFor(ex. player, stair, enemies, etc.)
  int r, c;
  int chamber = rand() % 5 + 1;
  if (genFor == "player")
  {
    spawnChamber = chamber;
  }

  if (genFor == "stair")
  {
    while (chamber == spawnChamber)
    {
      chamber = rand() % 5 + 1; //only when initStairPos calls genCell will loop through this block
    }
    stairChamber = chamber;
  }

  switch (chamber)
  {
  case 1:
  { // 4*26
    while (true)
    {
      r = rand() % 4 + 3;
      c = rand() % 26 + 3;
      if (checkAvailability(r, c) == true)
        break;
    }
  }
  break;
  case 2:
  { //2 * 23 + 1 * 31 + 1 * 34 + 6 * 15
    while (true)
    {
      int cell = rand() % 201;
      if (cell >= 0 && cell <= 45)
      {
        r = cell / 23 + 3;
        c = cell % 23 + 39;
      }
      else if (cell >= 46 && cell <= 76)
      {
        r = (cell - 46) / 31 + 5;
        c = (cell - 46) % 31 + 39;
      }
      else if (cell >= 77 && cell <= 111)
      {
        r = (cell - 77) / 34 + 6;
        c = (cell - 77) % 34 + 39;
      }
      else
      {
        r = (cell - 111) / 15 + 7;
        c = (cell - 111) % 15 + 61;
      }
      if (checkAvailability(r, c) == true)
        break;
    }
  }
  break;
  case 3:
  { // 3 * 12
    while (true)
    {
      r = rand() % 3 + 10;
      c = rand() % 12 + 38;
      if (checkAvailability(r, c) == true)
        break;
    }
  }
  break;
  case 4:
  { // 7 * 22
    while (true)
    {
      r = rand() % 7 + 15;
      c = rand() % 22 + 3;
      if (checkAvailability(r, c) == true)
        break;
    }
  }
  break;

  case 5:
  { // 3 * 11 + 3 * 39
    while (true)
    {
      int cell = rand() % 150;
      if (cell >= 0 && cell <= 32)
      {
        r = cell / 11 + 16;
        c = cell % 11 + 65;
      }
      else
      {
        r = cell / 39 + 19;
        c = cell % 39 + 37;
      }
      if (checkAvailability(r, c) == true)
        break;
    }
  }
  break;
  }
  return make_pair(r, c);
}

pair<int, int> Floor::genMove(int currR, int currC)
{
  int nextR = currR;
  int nextC = currC;
  int counter = 0;
  srand(time(NULL));

  while (true)
  {
    int pos = rand() % 8;
    //cerr << "randomly generated " << pos << endl;
    if (counter == 10)
    {
      srand(time(NULL));
    }
    switch (pos)
    {
    case 0:
      nextR = currR - 1;
      break;
    case 1:
      nextR = currR + 1;
      break;
    case 2:
      nextC = currC + 1;
      break;
    case 3:
      nextC = currC - 1;
      break;
    case 4:
    {
      nextR = currR - 1;
      nextC = currC + 1;
    }
    break;
    case 5:
    {
      nextR = currR - 1;
      nextC = currC - 1;
    }
    break;
    case 6:
    {
      nextR = currR + 1;
      nextC = currC + 1;
    }
    break;
    case 7:
    {
      nextR = currR + 1;
      nextC = currC - 1;
    }
    break;
    }
    if (checkAvailability(nextR, nextC) == true)
      break;
  }
  return make_pair(nextR, nextC);
}

pair<int, int> Floor::genMove(vector<pair<int, int>> availPos)
{
  int nextR, nextC;
  pair<int, int> nextPos;

  int availSpace = availPos.size();
  if (availSpace == 1)
  {
    nextPos = availPos[0];
    return nextPos;
  }
  int counter = 0;
  srand(time(NULL));

  while (true)
  {
    int pos = rand() % (availSpace - 1);
    //cerr << "randomly generated " << pos << endl;
    if (counter == 10)
    {
      srand(time(NULL));
    }
    nextPos = availPos[pos];
    nextR = nextPos.first;
    nextC = nextPos.second;
    //cerr << checkAvailability(nextR, nextC) << endl;
    if (checkAvailability(nextR, nextC) == true)
      break;
  }
  return nextPos;
}

void Floor::initPlayerPos()
{
  int i, j;
  if (spawnChamber == 0)
  {
    playerPos = genCell("player");
    myPlayer->setPosition(playerPos.first, playerPos.second);
  }
  else
  {
    playerPos = myPlayer->getPosition();
  }
  i = playerPos.first;
  j = playerPos.second;
  setCell(i, j, '@');
}

void Floor::initStairPos()
{
  stairPos = genCell("stair");
  int i = stairPos.first;
  int j = stairPos.second;

  setCell(i, j, '\\');
}

void Floor::genPotion(int potionNum)
{
  for (int n = 0; n < potionNum; ++n)
  {
    int p = rand() % 6;
    string potion;
    switch (p)
    {
    case 0:
      potion = "RH";
      break;
    case 1:
      potion = "BA";
      break;
    case 2:
      potion = "BD";
      break;
    case 3:
      potion = "PH";
      break;
    case 4:
      potion = "WA";
      break;
    case 5:
      potion = "WD";
      break;
    }

    pair<int, int> pos = genCell("potion");
    int i = pos.first;
    int j = pos.second;
    shared_ptr<Potion> aPotion = make_shared<Potion>(i, j, potion);
    potionList.emplace_back(aPotion);
    setCell(i, j, 'P');
  }
}

void Floor::genGold(int goldNum)
{
  for (int n = 0; n < goldNum; ++n)
  {
    int g = rand() % 8;
    int amount;
    bool pickable = true;

    if (g >= 0 && g <= 4)
    { //normal p = 5/8
      amount = 1;
    }
    else if (g >= 5 && g <= 6)
    { //small p = 2/8
      amount = 2;
    }
    else
    { //dragon p = 1/8
      amount = 6;
      pickable = false;
    }

    pair<int, int> pos = genCell("gold"); //generate gold spawn position
    int goldR = pos.first;
    int goldC = pos.second;
    shared_ptr<Gold> aGold = make_shared<Gold>(goldR, goldC, amount, pickable);
    goldList.emplace_back(aGold);
    setCell(goldR, goldC, 'G');

    if (amount == 6)
    {
      pair<int, int> dgPos = genMove(goldR, goldC);
      int dgR = dgPos.first;
      int dgC = dgPos.second;
      shared_ptr<Enemy> aGragon = make_shared<Dragon>(dgR, dgC, aGold);
      enemyList.emplace_back(aGragon);
      setCell(dgR, dgC, 'D');
      enemies += 1;
    }
  }
}

void Floor::genSuit()
{
  if (hasSuit == false)
  {
    return;
  }
  else
  {
    pair<int, int> suitPos = genCell("suit");
    int suitR = suitPos.first;
    int suitC = suitPos.second;
    shared_ptr<BarrierSuit> aSuit = make_shared<BarrierSuit>(suitR, suitC);
    bSuit = aSuit; 
    setCell(suitPos.first, suitPos.second, 'B');

    pair<int, int> dgPos = genMove(suitR, suitC);
    int dgR = dgPos.first;
    int dgC = dgPos.second;
    //shared_ptr<Enemy> aGragon = dynamic_cast<Enemy>(make_shared<Dragon> (dgR, dgC, aSuit));
    shared_ptr<Enemy> aGragon = make_shared<Dragon>(dgR, dgC, aSuit);
    enemyList.emplace_back(aGragon);
    setCell(dgR, dgC, 'D');
    enemies += 1;
  }
}

void Floor::genEnemies(int enemyNum)
{
  while (enemies <= enemyNum)
  {
    //cerr << "Number of enemies in the list " << enemies << endl;
    int e = rand() % 18;

    pair<int, int> pos = genCell("enemy");
    int r = pos.first;
    int c = pos.second;

    shared_ptr<Enemy> aEnemy;
    char eChar;

    if (e >= 0 && e <= 4)
    { //Goblin p = 5/18
      aEnemy = make_shared<Goblin>(r, c);
      eChar = 'N';
    }
    else if (e >= 5 && e <= 8)
    { //Werewolf p = 4/18
      aEnemy = make_shared<Werewolf>(r, c);
      eChar = 'W';
    }
    else if (e >= 9 && e <= 11)
    { //Vampire p = 3/18
      aEnemy = make_shared<Vampire>(r, c);
      eChar = 'V';
    }
    else if (e >= 12 && e <= 13)
    { //Troll p = 2/18
      aEnemy = make_shared<Troll>(r, c);
      eChar = 'T';
    }
    else if (e >= 14 && e <= 15)
    { //Phoenix p = 2/18
      aEnemy = make_shared<Phoenix>(r, c);
      eChar = 'X';
    }
    else
    { //Merchant p = 2/18
      aEnemy = make_shared<Merchant>(r, c);
      eChar = 'M';
    }
    //cerr << "generating " << eChar << " at " << r << " " << c << endl;
    enemyList.emplace_back(aEnemy);
    setCell(r, c, eChar);
    //cerr << getCell(r, c) << " " << aEnemy->getHP() << endl;
    enemies += 1;
  }
}

void Floor::genCompass()
{
  int compass = rand() % 20;
  while (enemyList[compass]->isMerchant() == true)
  {
    compass = rand() % 20;
  }
  enemyList[compass]->set_has_compass(true);
}

bool comparePos(shared_ptr<Enemy> e1, shared_ptr<Enemy> e2)
{
  int R1 = e1->getPosition().first;
  int C1 = e1->getPosition().second;
  int R2 = e2->getPosition().first;
  int C2 = e2->getPosition().second;

  if (R1 < R2)
  {
    return true;
  }
  else if ((R1 == R2) && (C1 < C2))
  {
    return true;
  }
  else
  {
    return false;
  }
}

string Floor::moveEnemies()
{ //loops through sorted enemyList, move each of them, and notify player while moving
  string enemyAction = "";
  string special = "";
  //cerr << "seg fault 1" << endl;
  sort(enemyList.begin(), enemyList.end(), comparePos);
  //cerr << "seg fault 2" << endl;

  for (auto it : enemyList)
  {
    //move enenmies on the board
    if ((it->get_is_fighting() == false) && (it->isDragon() == false))
    {
      int currR = it->getPosition().first;
      int currC = it->getPosition().second;

      //first check if there is space for it to move
      int availSpace = 0;
      vector<pair<int, int>> availPos;
      for (int i = currR - 1; i <= currR + 1; ++i)
      {
        for (int j = currC - 1; j <= currC + 1; ++j)
        {
          //cerr << getCell(i, j) << endl;
          if (getCell(i, j) == '.')
          {
            availSpace += 1;
            availPos.emplace_back(make_pair(i, j));
          }
        }
      }
      char enemy = getCell(currR, currC);
      //cerr << enemy << " " << currR << " " << currC << endl;
      pair<int, int> nextPos;
      //cerr << "available space " << availSpace << endl;
      if (availSpace > 0)
      {
        nextPos = genMove(availPos);
      }
      else
      { //if no available space, don't move
        //nextPos = make_pair(currR, currC);
        continue;
      }
      int nextR = nextPos.first;
      int nextC = nextPos.second;
      it->setPosition(nextR, nextC);
      //cerr << enemy << " " << it->getPosition().first << " " << it->getPosition().second << endl;
      unSetCell(currR, currC);
      setCell(nextR, nextC, enemy);
      //cerr << "previous position is " << getCell(currR, currC) << endl;
      //cerr << "current position is " << getCell(nextR, nextC) << endl;
    }
  }

  //calculate the damage
  for (auto it : enemyList)
  {
    int damage = it->notify(myPlayer, special);
    if (damage > 0)
    {
      char enemy = getCell(it->getPosition().first, it->getPosition().second);
      enemyAction = enemyAction + enemy + " deals " + to_string(damage) + " damage to PC. ";
      //enemyAction = enemyAction + enemy + " at " + to_string(it->getPosition().first) + " " + to_string(it->getPosition().second);
    }
    else if (damage == 0)
    {
      char enemy = getCell(it->getPosition().first, it->getPosition().second);
      enemyAction = enemyAction + enemy + " has missed an attack. ";
      //enemyAction = enemyAction + enemy + " at " + to_string(it->getPosition().first) + " " + to_string(it->getPosition().second);
    }
  }
  //sort(enemyList.begin(), enemyList.end(), comparePos);
  return enemyAction + special;
}

pair<int, int> Floor::getPos(int currR, int currC, Direction direction)
{
  int nextR = currR;
  int nextC = currC;

  switch (direction)
  {
  case Direction::no:
    nextR -= 1;
    break;
  case Direction::so:
    nextR += 1;
    break;
  case Direction::ea:
    nextC += 1;
    break;
  case Direction::we:
    nextC -= 1;
    break;
  case Direction::ne:
  {
    nextR -= 1;
    nextC += 1;
  }
  break;
  case Direction::nw:
  {
    nextR -= 1;
    nextC -= 1;
  }
  break;
  case Direction::se:
  {
    nextR += 1;
    nextC += 1;
  }
  break;
  case Direction::sw:
  {
    nextR += 1;
    nextC -= 1;
  }
  break;
  }
  return make_pair(nextR, nextC);
}

string Floor::movePlayer(Direction direction)
{

  //cerr << "player previous position " << myPlayer->getPosition().first << " " << myPlayer->getPosition().second << endl;

  string action = "PC moves ";
  string dir = "";

  int currR = playerPos.first;
  int currC = playerPos.second;

  int nextR = getPos(currR, currC, direction).first;
  int nextC = getPos(currR, currC, direction).second;

  switch (direction)
  {
  case Direction::no:
    dir = "North";
    break;
  case Direction::so:
    dir = "South";
    break;
  case Direction::ea:
    dir = "East";
    break;
  case Direction::we:
    dir = "West";
    break;
  case Direction::ne:
    dir = "North East";
    break;
  case Direction::nw:
    dir = "North West";
    break;
  case Direction::se:
    dir = "South East";
    break;
  case Direction::sw:
    dir = "South West";
    break;
  }

  char nextCell = getCell(nextR, nextC);

  if (nextCell == '.' || nextCell == '#' || nextCell == '+')
  {
    myPlayer->move(direction);
    playerPos = make_pair(nextR, nextC);
    unSetCell(currR, currC);
    setCell(nextR, nextC, '@');
    action = action + dir;
  }
  else if (nextCell == 'G')
  {

    int index = 0;
    for (auto it : goldList)
    {
      int goldR = it->getPosition().first;
      int goldC = it->getPosition().second;

      int goldAmount;
      bool picked;
      if (goldR == nextR && goldC == nextC)
      {
        picked = myPlayer->setGold(*it);
        if (picked)
        {
          myPlayer->move(direction);
          playerPos = make_pair(nextR, nextC);
          setCell(nextR, nextC, '@');
          unSetCell(currR, currC);

          goldAmount = it->getAmount();
          goldList.erase(goldList.begin() + index);
          action = action + dir + " and picked " + to_string(goldAmount) + " gold";
        }
        else
        {
          action = "You need to defeat the Dragon first";
        }
        break;
      }
      index += 1;
    }
  }
  else if (nextCell == 'C')
  {
    myPlayer->move(direction);
    playerPos = make_pair(nextR, nextC);
    unSetCell(currR, currC);
    setCell(nextR, nextC, '@');
    showStair = true; //stair is now visible by player
    action = action + dir + " and picked a compass";
  }
  else if (nextCell == 'B')
  {
    if (bSuit->getPickable()){
      myPlayer->move(direction);
      playerPos = make_pair(nextR, nextC);
      unSetCell(currR, currC);
      setCell(nextR, nextC, '@');
      myPlayer->wearBSuit();
      action = action + dir + " and wore the Barrier Suit";
    } else {
      action = "You need to defeat the Dragon first.";
    }
  }
  else if (nextCell == '\\')
  {
    myPlayer->move(direction);
    playerPos = make_pair(nextR, nextC);
    //won't show player position on the board since the player has reached the stair
    unSetCell(currR, currC);
    action = action + dir + " and reached the stairs. PC has reached the next Floor.";
  }
  else
  {
    action = "Invalid move.";
  }

  //cerr << "player current position " << myPlayer->getPosition().first << " " << myPlayer->getPosition().second << endl;

  string enemyAction = "";
  if (action != "Invalid move." && nextCell != '\\')
  {
    enemyAction = moveEnemies();
    //cerr << "seg fault 3" << endl;
    if (enemyAction == "")
    {
      action = action + ". ";
    }
    for (int i = nextR - 1; i <= nextR + 1; ++i)
    {
      for (int j = nextC - 1; j <= nextC + 1; ++j)
      {
        char seeCell = getCell(i, j);
        switch (seeCell)
        {
        case 'P':
        {
          for (auto it : potionList)
          {
            if (it->getPosition().first == i && it->getPosition().second == j)
            {
              string potionType = it->getType();
              if (myPlayer->getKnowledge(potionType))
              {
                action = action + "PC sees " + potionType + ". ";
              }
              else
              {
                action = action + " PC sees an unknown potion. ";
              }
            }
          }
        }
        break;
        case 'G':
          action = action + " PC sees a pile of gold. ";
          break;
        case 'C':
          action = action + " PC sees a compass. ";
          break;
        case 'B':
          action = action + " PC sees a Barrier Suit. ";
          break;
        case '\\':
        {
          if (showStair)
          {
            action = action + " PC sees a stair. ";
          }
          break;
        }
        }
      }
    }
  }
  return action + " " + enemyAction;
}

string Floor::fightPlayer(Direction direction)
{ //player attacks enemies

  string action = "";

  int currR = playerPos.first;
  int currC = playerPos.second;

  int nextR = getPos(currR, currC, direction).first;
  int nextC = getPos(currR, currC, direction).second;
  char enemy = getCell(nextR, nextC); //may be some other characters which do not represent enemies but will only prints when the cell get matched with an enemy in enemyList

  pair<int, int> enemyPos = make_pair(nextR, nextC);
  int index = 0;
  bool valid = false;
  for (auto it : enemyList)
  {
    if (it->getPosition() == enemyPos)
    {
      valid = true;
      it->start_fighting();
      action = "PC deals ";
      if (it->isMerchant())
      {
        for (auto it1 : enemyList)
        {
          it1->notify_merchant();
        }
      }
      int damageByPlayer = myPlayer->attack(it);

      action = action + to_string(damageByPlayer) + " damage to " + enemy + ". ";

      if (it->getHP() <= 0)
      { 
        myPlayer->incGold();
        action = action + enemy + " dies. ";
        unSetCell(nextR, nextC);

        if (it->get_has_compass())
          {
            action = action + enemy + "drops a compass. ";
            setCell(nextR, nextC, 'C');
          }
        if (enemy == 'D')
        { //if a dragon dies, the item it holds becomes pickable
          it->get_item_ptr()->setPickable();
          enemyList.erase(enemyList.begin() + index);
        }
        else if (enemy == 'M')
        { //if a merchant dies, its position becomes merchant hoard
          shared_ptr<Gold> aGold = make_shared<Gold>(nextR, nextC, 4, true);
          setCell(nextR, nextC, 'G');
          goldList.emplace_back(aGold);
          enemyList.erase(enemyList.begin() + index);
        }
        else
        {
          enemyList.erase(enemyList.begin() + index);
        }
        break;
      }
    }
    index += 1;
  }
  if (valid) {
    string enemyAction = moveEnemies();
    //cerr << "seg fault 4" << endl;
    return action + enemyAction;
  } else {
    return "Invalid command.";
  }
  
}

string Floor::usePotion(Direction direction)
{
  string action = "PC uses ";

  int currR = playerPos.first;
  int currC = playerPos.second;

  int nextR = getPos(currR, currC, direction).first;
  int nextC = getPos(currR, currC, direction).second;

  char nextCell = getCell(nextR, nextC);

  if (nextCell == 'P')
  {
    myPlayer->move(direction);
    playerPos = make_pair(nextR, nextC);
    unSetCell(currR, currC);
    setCell(nextR, nextC, '@');

    int changeHP;
    int changeAtk;
    int changeDef;

    string potionType = "";

    int index = 0;
    for (auto it : potionList)
    {
      int potionR = it->getPosition().first;
      int potionC = it->getPosition().second;

      if (potionR == nextR && potionC == nextC)
      {
        int initHP = myPlayer->getHP();
        int initAtk = myPlayer->getAtk();
        int initDef = myPlayer->getDef();

        myPlayer->consumePotion(*it);

        changeHP = myPlayer->getHP() - initHP;
        changeAtk = myPlayer->getAtk() - initAtk;
        changeDef = myPlayer->getDef() - initDef;

        potionType = it->getType();

        myPlayer->setKnowledge(potionType);

        potionList.erase(potionList.begin() + index);
        break;
      }
      index += 1;
    }

    action = action + potionType + ". ";
    if (changeHP > 0)
    {
      action = action + "PC restored " + to_string(changeHP) + "HP";
    }
    else if (changeAtk > 0)
    {
      action = action + "PC increased Atk by " + to_string(changeAtk);
    }
    else if (changeDef > 0)
    {
      action = action + "PC increased Def by " + to_string(changeDef);
    }
    else if (changeHP < 0)
    { 
        action = action + "PC lost " + to_string(abs(changeHP)) + "HP";
    }
    else if (changeAtk < 0)
    { 
        action = action + "PC decreased Atk by " + to_string(abs(changeAtk));      
    }
    else if (changeDef < 0)
    {
        action = action + "PC decreased Def by " + to_string(abs(changeDef));
    }
    else if (changeHP == 0 || changeAtk == 0 || changeDef == 0)
    {
      action = action + "The potion has no effect on PC";
    }
  } 
  else
    {
      action = "Invalid command.";
    }

  string enemyAction = "";
  if (action != "Invalid command.")
  {
    enemyAction = moveEnemies();
    //cerr << "seg fault 5" << endl;
    action = action + ". ";
    for (int i = nextR - 1; i <= nextR + 1; ++i)
    {
      for (int j = nextC - 1; j <= nextC + 1; ++j)
      {
        char seeCell = getCell(i, j);
        switch (seeCell)
        {
        case 'P':
        {
          for (auto it : potionList)
          {
            if (it->getPosition().first == i && it->getPosition().second == j)
            {
              string potionType = it->getType();
              if (myPlayer->getKnowledge(potionType))
              {
                action = action + "PC sees " + potionType + ". ";
              }
              else
              {
                action = action + " PC sees an unknown potion. ";
              }
            }
          }
        }
        break;
        case 'G':
          action = action + " PC sees a pile of gold. ";
          break;
        case 'C':
          action = action + " PC sees a compass. ";
          break;
        case 'B':
          action = action + " PC sees a Barrier Suit. ";
          break;
        case '\\':
        {
          if (showStair)
          {
            action = action + " PC sees a stair. ";
          }
          break;
        }
        }
      }
    }
  }
  return action + " " + enemyAction;
}

bool Floor::isFinishedLevel()
{
  if (playerPos == stairPos)
    return true;
  else
    return false;
}

string Floor::printFloor()
{
  string output = "";
  int stair_i = stairPos.first;
  int stair_j = stairPos.second;
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      if ((i == stair_i) && (j == stair_j))
      {
        if (showStair)
        {
          output = output + '\\';
        }
        else
        {
          output = output + '.';
        }
      }
      else
      {
        output = output + getCell(i, j);
      }
    }
    output = output + "\n";
  }
  return output;
}
