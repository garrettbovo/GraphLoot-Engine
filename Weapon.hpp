#ifndef WEAPON_H
#define WEAPON_H

#include "Item.hpp"

#include <string>

//child class Weapon inherited from Item class
class Weapon : public Item
{
    //private member attributes
    double damage, fireRate, reloadTime;
    bullet ammo;
    int magSize;

    public:
        //default constructor
        Weapon() {}
        //constructor
        Weapon(const int , const rarity, const string, const string, const type, const double, const double, const double, const bullet, const int);
        //getter returning the damage the gun outputs
        double getDamage() const { return damage; }
        //setter assigning a new damage amount to the weapon
        void setDamage(const double id) { damage = id; }
        //getter returning the weapon's fire rate
        double getFireRate() const { return fireRate; }
        //setter assigning the weapon's fire rate
        void setFireRate(const double id) { fireRate = id; }
        //getter returning the weapon's reload time
        double getReloadTime() const { return reloadTime; }
        //setter assigning the weapon's reload time
        void setReloadTime (const double id) { fireRate = id; }
        //getter returning the weapon's ammo type
        bullet getAmmo() const { return ammo; }
        //setter assigning the weapon's ammo type
        void setAmmo(const bullet id) { ammo = id; }
        //getter returning the weapon's magazine size
        int getMagSize() const { return magSize; }
        //setter assigning the weapon's magazine size
        void setMagSize(const int id) { magSize = id; }
        //default destructor
        ~Weapon() {}
};

#endif