#include "ItemDatabase.hpp"
#include "LootPool.hpp"

#include <fstream>
#include <sstream>
#include <string>

int readCSV()
{
    ifstream file;
    string strID, strRarityID, line, name, description, strAmmo, strMagSize, strDamage, strFireRate, strReloadTime, strType;
    int ID, magSize, i = 0;
    rarity rarityID;
    bullet ammo;
    double damage, fireRate, reloadTime;
    type typeID;
    Item *node;
    file.open("Items.csv");

    if (!file.is_open())
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    while (getline(file, line))
    {
        stringstream ss(line);

        if (i++ == 0)
            continue;
        
        getline(ss, strID, ',');
        ID = stoi(strID);

        getline(ss, name, ',');

        getline(ss, strRarityID, ',');
        rarityID = static_cast<rarity>(stoi(strRarityID));
        
        getline(ss, description, ',');

        getline(ss, strType, ',');
        typeID = static_cast<type>(stoi(strType));

        if (!typeID)
            node = new Item(ID, rarityID, name, description, typeID);
            
        else
        {
            getline(ss, strAmmo, ',');
            ammo = static_cast<bullet>(stoi(strAmmo));

            getline(ss, strDamage, ',');
            damage = stod(strDamage);

            getline(ss, strFireRate, ',');
            fireRate = stod(strFireRate);

            getline(ss, strMagSize, ',');
            magSize = stoi(strMagSize);

            getline(ss, strReloadTime, ',');
            reloadTime = stod(strReloadTime);

            node = new Weapon(ID, rarityID, name, description, typeID, damage, fireRate, reloadTime, ammo, magSize);
        }

        allItems.push_back(node);
    }

    return 0;
}

void setLootPool()
{
    RarityWeight rarityWeight;
    int gunWeight = Weapons;
    Weapon *weapon;
    Entry *newNode;
    LootPool weaponPool, itemPool;

    for (int i = 0; i < allItems.size(); i++)
    {
        switch (allItems[i]->getRarityID())
        {
            case 0: rarityWeight = Common; break;
            case 1: rarityWeight = Uncommon; break;
            case 2: rarityWeight = Rare; break;
            case 3: rarityWeight = Epic; break;
            case 4: rarityWeight = Legendary; break;
            case 5: rarityWeight = Mythic; break;
            case 6: rarityWeight = Exotic; break;
        }

        if (allItems[i]->getType() == Gun)
        {
            weapon = static_cast<Weapon *>(allItems[i]);

            switch (weapon->getAmmo())
            {
                case Light: gunWeight *= 1.1; break;
                case Medium: gunWeight *= 1; break;
                case Heavy: gunWeight *= 0.5; break;
                case Shells: gunWeight *= 0.9; break;
                case Rockets: gunWeight *= 0.3; break;
            }

            weaponPool.addEntry(weapon, rarityWeight * gunWeight);
        }

        else
        {
            switch (allItems[i]->getType())
            {
                case Consumable: gunWeight = Consumables; break;
                case Throwable: gunWeight = Throwables; break;
                case Utility: gunWeight = Utilities; break;
            }

            itemPool.addEntry(allItems[i], gunWeight);
        }
    }
}

template <typename T>
void freeMem(vector<T *> vectDS)
{
    for (int i = 0; i < vectDS.size(); i++)
    {
        delete vectDS[i];
        vectDS[i] = nullptr;
    }

    vectDS.clear();
}