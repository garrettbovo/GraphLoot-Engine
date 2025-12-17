#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include "Item.hpp"
#include "Weapon.hpp"
#include "Entry.hpp"
#include "LootPool.hpp"

#include <vector>

extern vector<Item *> allItems;

int readCSV();
void setLootPool();

template <typename T>
void freeMem(T *);

#endif