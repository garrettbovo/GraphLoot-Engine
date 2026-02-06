#ifndef ENTRY_H
#define ENTRY_H

#include "Item.hpp"

#include <vector>

enum RarityWeight
{
    WeightCommon = 40,
    WeightUncommon = 30,
    WeightRare = 15,
    WeightEpic = 8,
    WeightLegendary = 4,
    WeightMythic = 1,
    WeightExotic = 1
};

enum CategoryWeight
{
    Weapons = 100,
    Consumables = 70,
    Throwables = 30,
    Utilities = 20
};

class Entry
{
    Item *item;
    double weight;

    public:
        Entry() {}
        Entry(Item *, const double);
        Item *getItem() const { return item; }
        void setItem (Item *id) { item = id; }
        double getWeight() const { return weight; }
        void setWeight(const double id) { weight = id; }
        ~Entry() {}
};

#endif