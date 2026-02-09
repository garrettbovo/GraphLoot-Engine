#include "ItemDatabase.hpp"
#include "LootPool.hpp"
#include "Chest.hpp"

#include <fstream>
#include <sstream>
#include <string>

//converts string weapon type into its enum form
type getType(const string &str)
{
    if (str == "Weapon") return Gun;
    else if (str == "Consumable") return Consumable;
    else if (str == "Ammo") return Bullet;
    else if (str == "Throwable") return Throwable;
    else if (str == "Utility") return Utility;
    
    return Gun;
}

//converts string weapon rarity type into its enum form
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

//converts string bullet type into its enum form
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

//method reading in the items' information from the CSV
int ItemDatabase::readCSV()
{
    //variable declarations and initializations
    ifstream file;
    string strID, strRarityID, line, name, description, strAmmo, strMagSize, strDamage, strFireRate, strReloadTime, strType;
    int ID, magSize, i = 0;
    rarity rarityID;
    bullet ammo;
    double damage, fireRate, reloadTime;
    type typeID;
    Item *node;

    //opening the file
    file.open("Items.csv");

    //checking if the file opened successfully; otherwise, the program will terminate
    if (!file.is_open())
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    //reading each line of the file
    while (getline(file, line))
    {
        if (line.find_first_not_of(" \t\r\n") == string::npos)
            continue;
        
        stringstream ss(line);

        //skipping the first line of the file
        if (i++ == 0)
            continue;
        
        //reading in the item's ID and storing it as an int
        getline(ss, strID, ',');
        ID = stoi(strID);

        //reading in the item's name
        getline(ss, name, ',');

        //reading in the item's category type
        getline(ss, strType, ',');
        typeID = getType(strType);

        //reading in the item's rarity type
        getline(ss, strRarityID, ',');
        rarityID = getRarity(strRarityID);
        
        //reading in the item's description
        getline(ss, description, ',');

        //if the item is not a weapon, instantiate a new node for the item
        if (typeID != Gun)
            node = new Item(ID, rarityID, name, description, typeID);
            
        //otherwise if the item is a weapon
        else
        {
            //reading in the weapon's ammo type and storing it as a bullet enum type
            getline(ss, strAmmo, ',');
            ammo = getBullet(strAmmo);

            //reading in the weapon's damage value and storing it as a float
            getline(ss, strDamage, ',');
            damage = stod(strDamage);

            //reading in the weapon's fire rate value and storing it as a float
            getline(ss, strFireRate, ',');
            fireRate = stod(strFireRate);

            //reading in the weapon's magazine size and storing it as an int
            getline(ss, strMagSize, ',');
            magSize = stoi(strMagSize);

            //reading in the weapon's reload time and storing it as a float
            getline(ss, strReloadTime, ',');
            reloadTime = stod(strReloadTime);

            //instantiating a new Weapon node to be pushed back onto the vector of all items 
            node = new Weapon(ID, rarityID, name, description, typeID, damage, fireRate, reloadTime, ammo, magSize);
        }

        allItems.push_back(node);
    }

    return 0;
}

//method for defining the weapon's loot pool and item's loot pool
void ItemDatabase::setLootPool()
{
    //variable declarations
    RarityWeight rarityWeight;
    double categoryWeight;
    Weapon *weapon;

    //making sure the pools are empty before adding to them
    weaponPool.clear();
    itemPool.clear();

    //looping through all items read from the file
    for (int i = 0; i < allItems.size(); i++)
    {
        //switch statement to calculate the weight of the current item in the vector of all items
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

        //checking if the current item in the vector is a weapon
        if (allItems[i]->getType() == Gun)
        {
            //if so, convert the item into a Weapon pointer
            weapon = static_cast<Weapon *>(allItems[i]);

            //switch statement needed to calculate the weight of the current weapon needed for the entry
            switch (weapon->getAmmo())
            {
                case Light: categoryWeight = Weapons * 1.1; break;
                case Medium: categoryWeight = Weapons * 1; break;
                case Heavy: categoryWeight = Weapons * 0.5; break;
                case Shells: categoryWeight = Weapons * 0.9; break;
                case Rockets: categoryWeight = Weapons * 0.3; break;
                default: categoryWeight = Weapons; break;
            }

            //adding entry to the weapon pool
            weaponPool.addEntry(weapon, rarityWeight * categoryWeight);
        }

        //otherwise if the item is not a weapon
        else
        {
            //switch statement needed to calculate the weight of the current item needed for the entry
            switch (allItems[i]->getType())
            {
                case Consumable: categoryWeight = Consumables; break;
                case Throwable: categoryWeight = Throwables; break;
                case Utility: categoryWeight = Utilities; break;
                default: categoryWeight = Weapons; break;
            }

            //adding new entry into the item loot pool
            itemPool.addEntry(allItems[i], rarityWeight * categoryWeight);
        }
    }
}

//method for randomly choosing a weapon from the weapon loot pool
Weapon *ItemDatabase::rollWeapon()
{
    return static_cast<Weapon *>(weaponPool.roll());
}

//method for randomly choosing an item from the item loot pool
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
