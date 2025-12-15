#ifndef ENTRY_H
#define ENTRY_H

#include "Item.hpp"

#include <vector>

enum RarityWeight
{
    Common = 40,
    Uncommon = 30,
    Rare = 15,
    Epic = 8,
    Legendary = 4,
    Mythic = 1,
    Exotic = 1
};

enum CategoryWeight
{
    Weapons = 100,
    Consumables = 70,
    Throwables = 30,
    Utility = 20
};

class Entry
{
    Item *item;
    int weight;

    public:
        Entry() {}
        Entry(Item *, const int);
        Item *getItem() const { return item; }
        void setItem (Item *id) { item = id; }
        int getWeight() const { return weight; }
        void setWeight(const int id) { weight = id; }
        ~Entry() {}
};

#endif