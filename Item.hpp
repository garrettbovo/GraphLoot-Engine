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
    Gun = 1,
    Consumable = 2,
    Bullet = 3,
    Throwable = 4,
    Utility = 5
};

class Item
{
    int ID;
    rarity rarityID;
    string name, description;
    type typeID;

    public:
        Item() {}
        Item(const int, const rarity, const string, const string, const type);
        int getID() const { return ID; }
        void setID(const int id) { ID = id; }
        rarity getRarityID() const { return rarityID; }
        void setRarityID(const rarity id) { rarityID = id; }
        string getName() const { return name; }
        void setName(const string id) { name = id; }
        string getDescription() const { return description; }
        void setDescription(const string id) { description = id; }
        type getType() const { return typeID; }
        void setType(const type id) { typeID = id; }
        virtual ~Item() {}
};

#endif