#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

//enum for the rarity of the item
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

//enum for the bullet type of the weapon
enum bullet
{
    Light = 0,
    Medium = 1,
    Heavy = 2,
    Shells = 3,
    Rockets = 4
};

//enum categorizing the type of item
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
    //private member attributes
    int ID;
    rarity rarityID;
    string name, description;
    type typeID;

    public:
        //default constructor
        Item() {}
        //constructor
        Item(const int, const rarity, const string, const string, const type);
        //getter returning the ID of the item
        int getID() const { return ID; }
        //setter assigning the ID of the item
        void setID(const int id) { ID = id; }
        //getter returning the rarity of the item
        rarity getRarityID() const { return rarityID; }
        //setter assigning the rarity of the item
        void setRarityID(const rarity id) { rarityID = id; }
        //getter returning the name of the item
        string getName() const { return name; }
        //setter assigning the name of the item
        void setName(const string id) { name = id; }
        //getter returning the description of the item
        string getDescription() const { return description; }
        //setter assigning the description of the item
        void setDescription(const string id) { description = id; }
        //getter returning the item's category
        type getType() const { return typeID; }
        //setter assigning the item's category
        void setType(const type id) { typeID = id; }
        //default destructor
        virtual ~Item() {}
};

#endif