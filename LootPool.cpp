#include "LootPool.hpp"

#include <vector>

void LootPool::addEntry(const Item *item, const double weight)
{
    entries.emplace_back(item, weight);

    totalWeight += weight;
}

Item *LootPool::roll() const 
{
    double roll, weight = 0.0;

    if (entries.empty())
        return nullptr;
    
    do
    {
        roll = (double) rand() / RAND_MAX * totalWeight;
    } while (roll == 0.0);

    for (int i = 0; i < entries.size(); i++)
    {
        weight += entries[i].getWeight();

        if (roll <= weight)
            return entries[i].getItem();
    }

    return nullptr;
}

void LootPool::clear()
{
    entries.clear();
    totalWeight = 0.0;
}