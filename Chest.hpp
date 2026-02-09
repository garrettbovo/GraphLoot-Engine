#ifndef CHEST_H
#define CHEST_H

#include "Item.hpp"
#include "Weapon.hpp"

//stores the amount of each ammo type to be dropped in each chest
enum ammoDrop
{
    LightDrop = 30,
    MediumDrop = 25,
    ShellDrop = 8,
    HeavyDrop = 7,
    RocketDrop = 2,
};

class Chest
{
    //private Chest attributes
    Weapon *weapon;
    int ammoQuantity;
    bullet ammoType;
    Item *extra;

    public:
        //default constructor
        Chest() {}
        //constructor initializing a chest with a weapon and additional item
        Chest(Weapon *, Item *);
        //setter assigning a weapon to the chest
        void setWeapon(Weapon *wID) { weapon = wID; }
        //getter returning the weapon found in the chest
        Weapon *getWeapon() const { return weapon; }
        //setter assigning the amount of ammo found in the chest
        void setAmmoQuantity(Weapon *wID);
        //getter returning the amount of ammo found in the chest
        int getAmmoQuantity() const { return ammoQuantity; }
        //setter assigning the type of ammo to be found in the chest
        void setAmmoType(Weapon *wID) { ammoType = wID->getAmmo(); }
        //getter returning the type of ammo to be found in the chest
        bullet getAmmoType() const { return ammoType; }
        //setter assigning the extra item to the chest
        void setExtra(Item *iID) { extra = iID; }
        //getter returning the extra item from the chest
        Item *getExtra() const { return extra; }
        //method for displaying information about what is in the chest
        void displayChest() const;
        //default destructor
        ~Chest() {}
};

#endif