#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

enum rarity
{
    Common = 0,
    Uncommon = 1,
    Rare = 2,
    Epic = 3,
    Legendary = 4,
    Mythic = 5,
    Exotic = 6
};

enum bullet
{
    Light = 0,
    Medium = 1,
    Heavy = 2,
    Shells = 3,
    Rockets = 4
};

enum type
{
    Weapon = 1,
    Consumable = 2,
    Bullet = 3,
    Throwables = 4
};

class Item
{
    int ID;
    rarity rarityID;
    type typeID;
    string name, description;

    public:
        Item();
        Item();
        int getID() const { return ID; }
        void setID(const int id) { ID = id; }
        rarity getRarityID() const { return rarityID; }
        void setRarityID(const rarity id) { rarityID = id; }
        type getTypeID() const { return typeID; }
        void setTypeID(const type id) { typeID = id; }
        string getName() const { return }
};

#endif