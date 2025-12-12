#include "Item.hpp"
#include "Weapon.hpp"
#include "ItemDatabase.hpp"

#include <fstream>

int readCSV(const string &filename)
{
    ifstream file;
    string strID, strRarityID, line, name, description, strAmmo, strMagSize, strDamage, strFireRate, strReloadTime;
    int ID, magSize;
    rarity rarityID;
    bullet ammo;
    double damage, fireRate, reloadTime;
    Item *node;
    file.open("Items.csv");

    if (!file.is_open())
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    for (int i = 0; !file.eof(); i++)
    {
        getline(file, line);

        if (!i)
            continue;
        
        getline(file, strID, ',');
        ID = stoi(strID);

        getline(file, name, ',');

        getline(file, strRarityID, ',');
        rarityID = static_cast<rarity>(stoi(strRarityID));
        
        getline(file, description, ',');
        
        getline(file, strAmmo, ',');
        ammo = static_cast<bullet>(stoi(strAmmo));

        getline(file, strDamage, ',');
        damage = stod(strDamage);

        getline(file, strFireRate, ',');
        fireRate = stod(strFireRate);

        getline(file, strMagSize, ',');
        magSize = stoi(strMagSize);

        getline(file, strReloadTime, ',');
        reloadTime = stod(strReloadTime);

        if (ammo == None)
            node = new Item(ID, rarityID, name, description);
        else
            node = new Weapon(ID, rarityID, name, description, damage, fireRate, reloadTime, ammo, magSize);
    }

    return 0;
}