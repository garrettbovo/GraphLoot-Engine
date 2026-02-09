#include "Chest.hpp"
#include "GameUtils.hpp"

//Chest constructor
Chest::Chest(Weapon *gun, Item *item)
{
    weapon = gun;
    setAmmoQuantity(gun);
    setAmmoType(gun);
    extra = item;
}

//setter for the number of bullets to be set in the chest
void Chest::setAmmoQuantity(Weapon *gun)
{
    //checking if the current item is a gun; otherwise method will terminate
    if (gun == nullptr)
        return;
    
    //setting number of bullets to be in the chest dependent on enum value
    switch (gun->getAmmo())
    {
        case Light: ammoQuantity = LightDrop; break;
        case Medium: ammoQuantity = MediumDrop; break;
        case Heavy: ammoQuantity = HeavyDrop; break;
        case Shells: ammoQuantity = ShellDrop; break;
        case Rockets: ammoQuantity = RocketDrop; break;
    }
}

//method for displaying all the items in the chest
void Chest::displayChest() const
{
    //chest opened introduction
    cout << "\n========================================\n";
    cout << "           CHEST OPENED!\n";
    cout << "========================================\n\n";

    //printing weapon information to the screen
    cout << "WEAPON FOUND\n";
    cout << "----------------------------------------\n";
    cout << "Name:        " << weapon->getName() << "\n";
    cout << "Rarity:      " << rarityToString(weapon->getRarityID()) << "\n";
    cout << "Ammo Type:   " << bulletToString(weapon->getAmmo()) << "\n";
    cout << "Damage:      " << weapon->getDamage() << "\n";
    cout << "Fire Rate:   " << weapon->getFireRate() << "\n";
    cout << "Magazine:    " << weapon->getMagSize() << "\n";
    cout << "Reload Time: " << weapon->getReloadTime()  << "s\n\n";

    //printing the additional item and its information found in the chest to the screen
    cout << "EXTRA ITEM\n";
    cout << "----------------------------------------\n";
    cout << "Name:        " << extra->getName() << "\n";
    cout << "Type:        " << typeToString(extra->getType()) << "\n";
    cout << "Rarity:      " << rarityToString(extra->getRarityID()) << "\n";
    cout << "Description: " << extra->getDescription() << "\n\n";

    cout << "========================================\n";
}