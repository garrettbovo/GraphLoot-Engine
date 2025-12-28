#include "FortniteWorld.hpp"
#include "ItemDatabase.hpp"

World buildWorld(ItemDatabase &db)
{
    World world;

    world.addDrop("Lonely Labs");
    world.addDrop("Brutal Bastion");
    world.addDrop("Anvil Square");
    world.addDrop("Mega City");
    world.addDrop("Slappy Shores");
    world.addDrop("Frenzy Fields");
    world.addDrop("Faulty Splits");
    world.addDrop("Shattered Slabs");

    world.addConnection("Lonely Labs", "Mega City", 6.5);
    world.addConnection("Lonely Labs", "Anvil Square", 5.0);

    world.addConnection("Brutal Bastion", "Anvil Square", 4.0);

    world.addConnection("Anvil Square", "Mega City", 3.5);
    world.addConnection("Anvil Square", "Slappy Shores", 3.0);

    world.addConnection("Mega City", "Slappy Shores", 2.0);
    world.addConnection("Mega City", "Frenzy Fields", 5.5);

    world.addConnection("Slappy Shores", "Faulty Splits", 4.0);

    world.addConnection("Frenzy Fields", "Faulty Splits", 3.0);
    world.addConnection("Frenzy Fields", "Shattered Slabs", 4.5);

    world.addConnection("Faulty Splits", "Shattered Slabs", 2.5);

    world.addChest("Lonely Labs", db.openChest());
    world.addChest("Brutal Bastion", db.openChest());
    world.addChest("Mega City", db.openChest());
    world.addChest("Slappy Shores", db.openChest());
    world.addChest("Frenzy Fields", db.openChest());
    world.addChest("Faulty Splits", db.openChest());

    return world;
}