#include "Item.hpp"

#include <string>

Item::Item(const int id, const rarity rID, const string nID, const string dID, const type tID)
{
    ID = id;
    rarityID = rID;
    name = nID;
    description = dID;
    typeID = tID;
}