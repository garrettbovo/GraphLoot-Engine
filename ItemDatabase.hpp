#ifndef ITEMDATABASE_H
#define ITEMDATABASE_H

#include "Item.hpp"
#include "Weapon.hpp"
#include "Entry.hpp"
#include "LootPool.hpp"
#include "Chest.hpp"

#include <vector>

class ItemDatabase
{
    //private member attributes
    LootPool weaponPool, itemPool;
    vector<Item *> allItems;

    public:
        //default constructor
        ItemDatabase() {}
        //setting the loot pool
        void setLootPool();
        //reading the information from the CSV
        int readCSV();
        //rolling a weapon
        Weapon *rollWeapon();
        //rolling an item
        Item *rollItem();
        //opening a chest
        Chest openChest();
        //freeing vectors from memory regardless of data type
        template <typename T>
        void freeMem(vector<T *> &vectDS)
        {
            for (int i = 0; i < vectDS.size(); i++)
            {
                delete vectDS[i];
                vectDS[i] = nullptr;
            }

            vectDS.clear();
        }
        //destructor
        ~ItemDatabase() { freeMem(allItems); }
};

#endif