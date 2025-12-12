#ifndef WEAPON_H
#define WEAPON_H

#include "Item.hpp"

#include <iostream>
using namespace std;

class Weapon : public Item
{
    double damage, fireRate, reloadTime;
    bullet ammo;
    int magSize;

    public:
        Weapon() {}
        Weapon(const double, const double, const double, const bullet, const int);
        Weapon(const int , const rarity, const string, const string, const double, const double, const double, const bullet, const int);
        double getDamage() const { return damage; }
        void setDamage(const double id) { damage = id; }
        double getFireRate() const { return fireRate; }
        void setFireRate(const double id) { fireRate = id; }
        double getReloadTime() const { return reloadTime; }
        void setReloadTime (const double id) { fireRate = id; }
        bullet getAmmo() const { return ammo; }
        void setFireRate(const bullet id) { ammo = id; }
        double getMagSize() const { return magSize; }
        void setMagSize(const int id) { magSize = id; }
};

#endif