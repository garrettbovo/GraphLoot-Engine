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
    LootPool weaponPool, itemPool;
    vector<Item *> allItems;

    public:
        void setLootPool();
        int readCSV();
        Weapon *rollWeapon();
        Item *rollItem();
        Chest openChest();
        template <typename T>
        void freeMem(vector<T *> &)
        {
            for (int i = 0; i < vectDS.size(); i++)
            {
                delete vectDS[i];
                vectDS[i] = nullptr;
            }

            vectDS.clear();
        }
        ~ItemDatabase() { freeMem(allItems); }
};

#endif