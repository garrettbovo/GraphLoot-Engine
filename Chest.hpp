#ifndef CHEST_H
#define CHEST_H

#include "Item.hpp"
#include "Weapon.hpp"

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
    Weapon *weapon;
    int ammoQuantity;
    bullet ammoType;
    Item *extra;

    public:
        Chest() {}
        Chest(Weapon *, Item *);
        void setWeapon(Weapon *wID) { weapon = wID; }
        Weapon *getWeapon() const { return weapon; }
        void setAmmoQuantity(Weapon *wID);
        int getAmmoQuantity() const { return ammoQuantity; }
        void setAmmoType(Weapon *wID) { ammoType = wID->getAmmo(); }
        bullet getAmmoType() const { return ammoType; }
        void setExtra(Item *iID) { extra = iID; }
        Item *getExtra() const { return extra; }
};

#endif