#ifndef INVENTORY_H
#define INVENTORY_H

#include "Weapon.hpp"
#include "Item.hpp"
#include <unordered_map>
#include <vector>

class Inventory
{
    static const int MAX_SLOTS = 5;
    unordered_map<bullet, int> ammo;
    vector<Item *> items;

    public:
        void addAmmo(bullet, int);
        void addItem(Item *);
        bool isFull() const;
        void print() const;
};

#endif