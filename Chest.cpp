#include "Chest.hpp"

Chest::Chest(Weapon *gun, Item *item)
{
    weapon = gun;
    setAmmoQuantity(gun);
    setAmmoType(gun);
    extra = item;
}

void Chest::setAmmoQuantity(Weapon *gun)
{
    if (gun == nullptr)
        return;
        
    switch (gun->getAmmo())
    {
        case Light: ammoQuantity = LightDrop; break;
        case Medium: ammoQuantity = MediumDrop; break;
        case Heavy: ammoQuantity = HeavyDrop; break;
        case Shells: ammoQuantity = ShellDrop; break;
        case Rockets: ammoQuantity = RocketDrop; break;
    }
}