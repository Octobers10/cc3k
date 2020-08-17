#ifndef _ITEM_H_
#define _ITEM_H_

#include <utility>

class Item {
    std::pair<int, int> position; 
    
    public: 
    Item(int, int); 
    virtual ~Item();
    std::pair<int, int> getPosition();
    void setPosition(int, int);
    virtual void setPickable();
    virtual bool getPickable() = 0;
};


#endif
