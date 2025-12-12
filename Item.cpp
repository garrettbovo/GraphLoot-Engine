#include "Item.hpp"

#include <string>

Item::Item(const int id, const rarity rID, const string nID, const string dID)
{
    ID = id;
    rarityID = rID;
    name = nID;
    description = dID;
}