#ifndef _POTION_H_
#define _POTION_H_

#include "item.h"
#include <string>

class Potion: public Item {
    std::string type;

    public:
    Potion(int x, int y, std::string type);
    std::string getType();
    bool getPickable() override;

};

#endif
