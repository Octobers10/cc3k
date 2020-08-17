#include "merchant.h"

using namespace std;

Merchant::Merchant(int x, int y):
    Enemy{30, 70, 5, x, y, false, false, true} {}


void Merchant::notify_merchant() {
    setHostile(true);
}

