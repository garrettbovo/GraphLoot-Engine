#ifndef LOOTPOOL_H
#define LOOTPOOL_H

#include "Entry.hpp"
#include "Item.hpp"

#include <vector>

class LootPool
{
    vector<Entry> entries;
    int totalWeight;

    public:
        LootPool();
        void addEntry(const Item *, const int);
        Item *roll() const;
        int size() const { return entries.size(); }
        int getTotalWeight() const { return totalWeight; }
        ~LootPool();
};

#endif