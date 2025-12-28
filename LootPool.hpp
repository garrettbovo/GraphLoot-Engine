#ifndef LOOTPOOL_H
#define LOOTPOOL_H

#include "Entry.hpp"
#include "Item.hpp"

#include <vector>

class LootPool
{
    vector<Entry> entries;
    double totalWeight;

    public:
        LootPool();
        void addEntry(const Item *, const double);
        Item *roll() const;
        int size() const { return entries.size(); }
        double getTotalWeight() const { return totalWeight; }
        void clear();
        ~LootPool();
};

#endif