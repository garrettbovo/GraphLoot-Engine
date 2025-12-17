#include "LootPool.hpp"

#include <vector>

void LootPool::addEntry(const Item *item, const int weight)
{
    entries.emplace_back(item, weight);

    totalWeight += weight;
}

Item *LootPool::roll() const 
{
    int randNum, weight = 0;

    if (entries.empty())
        return nullptr;
    
    randNum = rand() % totalWeight + 1;

    for (int i = 0; i < entries.size(); i++)
    {
        weight += entries[i].getWeight();

        if (randNum <= weight)
            return entries[i].getItem();
    }

    return nullptr;
}

LootPool::~LootPool()
{
    entries.clear();
}