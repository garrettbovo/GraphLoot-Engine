#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include "Item.hpp"
#include "Weapon.hpp"
#include "LootPool.hpp"

#include <vector>

extern vector<Item *> allItems;
extern vector<Entry *> gunWeights, otherWeights;

int readCSV();
void setLootPool();
void freeMem();

#endif