#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include <vector>
#include "Item.hpp"
#include "Weapon.hpp"

vector<Item> allItems;

int readCSV(const string &);
void freeMem();

#endif