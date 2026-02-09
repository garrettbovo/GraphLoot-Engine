#include "ItemDatabase.hpp"
#include "LootPool.hpp"
#include "Chest.hpp"

#include <fstream>
#include <sstream>
#include <string>

type getType(const string &str)
{
    if (str == "Weapon") return Gun;
    else if (str == "Consumable") return Consumable;
    else if (str == "Ammo") return Bullet;
    else if (str == "Throwable") return Throwable;
    else if (str == "Utility") return Utility;
    
    return Gun;
}

rarity getRarity(const string &str)
{
    if (str == "Common") return Common;
    else if (str == "Uncommon") return Uncommon;
    else if (str == "Rare") return Rare;
    else if (str == "Epic") return Epic;
    else if (str == "Legendary") return Legendary;
    else if (str == "Mythic") return Mythic;
    else if (str == "Exotic") return Exotic;

    return Common;
}

bullet getBullet(const string &str)
{
    if (str == "Light") return Light;
    else if (str == "Medium") return Medium;
    else if (str == "Heavy") return Heavy;
    else if (str == "Shells") return Shells;
    else if (str == "Rockets") return Rockets;
    else if (str == "None") return Light;

    return Light;
}

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
        if (line.find_first_not_of(" \t\r\n") == string::npos)
            continue;
        
        stringstream ss(line);

        if (i++ == 0)
            continue;
        
        getline(ss, strID, ',');
        ID = stoi(strID);

        getline(ss, name, ',');

        getline(ss, strType, ',');
        typeID = getType(strType);

        getline(ss, strRarityID, ',');
        rarityID = getRarity(strRarityID);
        
        getline(ss, description, ',');

        if (typeID != Gun)
            node = new Item(ID, rarityID, name, description, typeID);
            
        else
        {
            getline(ss, strAmmo, ',');
            ammo = getBullet(strAmmo);

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
            case 0: rarityWeight = WeightCommon; break;
            case 1: rarityWeight = WeightUncommon; break;
            case 2: rarityWeight = WeightRare; break;
            case 3: rarityWeight = WeightEpic; break;
            case 4: rarityWeight = WeightLegendary; break;
            case 5: rarityWeight = WeightMythic; break;
            case 6: rarityWeight = WeightExotic; break;
            default: rarityWeight = WeightCommon; break;
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

//
Item *ItemDatabase::rollItem()
{
    return itemPool.roll();
}

//method for creating a chest to be opened
Chest ItemDatabase::openChest()
{
    //variable declarations and randomly rolling loot pool entries to add a weapon and item to the chest
    Chest newNode;
    Weapon *rollW = rollWeapon();
    Item *rollI = rollItem();

    newNode.setWeapon(rollW);
    newNode.setAmmoQuantity(rollW);
    newNode.setAmmoType(rollW);
    newNode.setExtra(rollI);

    return newNode;
}