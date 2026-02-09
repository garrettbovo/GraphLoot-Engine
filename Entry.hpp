#ifndef ENTRY_H
#define ENTRY_H

#include "Item.hpp"

#include <vector>

//enum defining how common each type of weapon should be when randomly generating items to be in the chest
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

//enum defining the weight of each extra item to be used when randomly generating the extra item in the chest
enum CategoryWeight
{
    Weapons = 100,
    Consumables = 70,
    Throwables = 30,
    Utilities = 20
};

class Entry
{
    //private member attributes
    Item *item;
    double weight;

    public:
        //default constructor
        Entry() {}
        //constructor initializing an entry into the loot pool consisting of an item and its weight
        Entry(Item *, double);
        //getter returning the type of item for this entry
        Item *getItem() const { return item; }
        //setter assigning new item to be included in the entry
        void setItem (Item *id) { item = id; }
        //getter returning the weight of the current item in the entry
        double getWeight() const { return weight; }
        //setter assigning the weight of the item in the entry
        void setWeight(double id) { weight = id; }
        //default destructor
        ~Entry() {}
};

#endif