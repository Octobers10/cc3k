#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../players/character.h"
#include "../players/player.h"
#include <memory>

class Enemy: public Character {
    bool hostile; 
    bool has_compass;
    bool is_fighting;
    bool dragon; 
    bool merchant; 
    
    public: 
    Enemy(int hp, int atk, int def, int x, int y, bool hostile=true, bool dragon=false, bool merchant = false);
    virtual ~Enemy();
    int attackedBy(int);
    int attack(std::shared_ptr<Player>);
    bool getHostile();
    void setHostile(bool);
    bool get_has_compass();
    void set_has_compass(bool compass);

    void start_fighting();
    void stop_fighting();
    bool get_is_fighting();
    //override this for dragon
    virtual int notify(std::shared_ptr<Player>, std::string & special);
    virtual void notify_merchant();
    bool isDragon(); 
    bool isMerchant(); 
    virtual std::shared_ptr<Item> get_item_ptr();
};


#endif
