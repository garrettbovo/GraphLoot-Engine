#include "Weapon.hpp"

#include <string>

Weapon::Weapon(const int ID, const rarity rarityID, const string name, const string description, const double dID, const double fID, const double rID, const bullet aID, const int mID) 
    : Item(ID, rarityID, name, description), damage(dID), fireRate(fID), reloadTime(rID), ammo(aID), magSize(mID) {}