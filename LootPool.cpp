#include "LootPool.hpp"

#include <vector>

//method for adding an entry to the loot pool
void LootPool::addEntry(Item *item, double weight)
{
    //instantiating an entry and pushing the entry back to the vector of entires
    entries.emplace_back(item, weight);

    //incrementing the total weight of all the items in the loot pool by the current item's weight
    totalWeight += weight;
}

//method for randomly rolling an items from the list of all entries in the pool
Item *LootPool::roll() const 
{
    //variable declarations and initializations
    double roll, weight = 0.0;

    //returning nullptr if the loot pool vector is empty
    if (entries.empty())
        return nullptr;
    
    //randomly generating a float number until the number is not equal to exactly zero
    do
    {
        roll = (double) rand() / RAND_MAX * totalWeight;
    } while (roll == 0.0);

    //for loop which iterates over each entry in the pool until the randomly rolled number is less than to total weight of all prior entries
    for (int i = 0; i < entries.size(); i++)
    {
        weight += entries[i].getWeight();

        //returning the item that was randomly rolled
        if (roll <= weight)
            return entries[i].getItem();
    }

    return nullptr;
}

//method for removing all the entries in the loot pool
void LootPool::clear()
{
    entries.clear();
    totalWeight = 0.0;
}