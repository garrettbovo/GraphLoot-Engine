#ifndef LOOTPOOL_H
#define LOOTPOOL_H

#include "Entry.hpp"
#include "Item.hpp"

#include <vector>

class LootPool
{
    //variable declarations
    vector<Entry> entries;
    double totalWeight;

    public:
        //default constructor
        LootPool() {}
        //method for adding a new entry to the loot pool
        void addEntry(Item *, double);
        //rolling a random item to be added to the loot pool
        Item *roll() const;
        //returning the total number of items in the loot pool
        int size() const { return entries.size(); }
        //getter returning the sum of all the weights of the items in the loot pool
        double getTotalWeight() const { return totalWeight; }
        //method deleting the loot pool and reassigning the totalWeight to 0
        void clear();
};

#endif