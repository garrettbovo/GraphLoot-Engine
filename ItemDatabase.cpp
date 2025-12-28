#include "ItemDatabase.hpp"
#include "LootPool.hpp"
#include "Chest.hpp"

#include <fstream>
#include <sstream>
#include <string>

int ItemDatabase::readCSV()
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

void ItemDatabase::setLootPool()
{
    RarityWeight rarityWeight;
    double categoryWeight;
    Weapon *weapon;

    weaponPool.clear();
    itemPool.clear();

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
            default: rarityWeight = Common; break;
        }

        if (allItems[i]->getType() == Gun)
        {
            weapon = static_cast<Weapon *>(allItems[i]);

            switch (weapon->getAmmo())
            {
                case Light: categoryWeight = Weapons * 1.1; break;
                case Medium: categoryWeight = Weapons * 1; break;
                case Heavy: categoryWeight = Weapons * 0.5; break;
                case Shells: categoryWeight = Weapons * 0.9; break;
                case Rockets: categoryWeight = Weapons * 0.3; break;
                default: categoryWeight = Weapons; break;
            }

            weaponPool.addEntry(weapon, rarityWeight * categoryWeight);
        }

        else
        {
            switch (allItems[i]->getType())
            {
                case Consumable: categoryWeight = Consumables; break;
                case Throwable: categoryWeight = Throwables; break;
                case Utility: categoryWeight = Utilities; break;
                default: categoryWeight = Weapons; break;
            }

            itemPool.addEntry(allItems[i], rarityWeight * categoryWeight);
        }
    }
}

Weapon *ItemDatabase::rollWeapon()
{
    return static_cast<Weapon *>(weaponPool.roll());
}

Item *ItemDatabase::rollItem()
{
    return itemPool.roll();
}

Chest ItemDatabase::openChest()
{
    Chest newNode;
    Weapon *rollW = rollWeapon();
    Item *rollI = rollItem();

    newNode.setWeapon(rollW);
    newNode.setAmmoQuantity(rollW);
    newNode.setAmmoType(rollW);
    newNode.setExtra(rollI);

    return newNode;
}