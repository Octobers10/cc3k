#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "enemy.h"
#include <utility>
#include <memory>

class Gold;

class Dragon: public Enemy {
    std::shared_ptr<Item> item_ptr;

    public:
    Dragon(int x, int y, std::shared_ptr<Item> item_ptr);
    std::shared_ptr<Item> get_item_ptr() override; 
    int notify(std::shared_ptr<Player>, std::string & special) override;
};


#endif
