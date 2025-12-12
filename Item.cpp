#include "Item.hpp"

#include <iostream>
using namespace std;

Item::Item(const int id, const rarity rID, const string nID, const string dID)
{
    ID = id;
    rarityID = rID;
    name = nID;
    description = dID;
}