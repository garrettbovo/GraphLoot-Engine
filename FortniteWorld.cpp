#include "FortniteWorld.hpp"
#include "ItemDatabase.hpp"

//function for building the Fortnite map
World buildWorld(ItemDatabase &db)
{
    //variable declaration
    World world;

    //adding POIs to the map
    world.addDrop("Lonely Labs");
    world.addDrop("Brutal Bastion");
    world.addDrop("Anvil Square");
    world.addDrop("Mega City");
    world.addDrop("Slappy Shores");
    world.addDrop("Frenzy Fields");
    world.addDrop("Faulty Splits");
    world.addDrop("Shattered Slabs");

    //adding weighted, undirected connections between edges starting at Lonely Labs
    world.addConnection("Lonely Labs", "Anvil Square", 5.0);
    world.addConnection("Lonely Labs", "Mega City", 6.5);

    //adding weighted, undirected connections between edges starting at Brutal Bastion
    world.addConnection("Brutal Bastion", "Anvil Square", 4.0);

    //adding weighted, undirected connections between edges starting at Anvil Square
    world.addConnection("Anvil Square", "Mega City", 3.5);
    world.addConnection("Anvil Square", "Slappy Shores", 3.0);

    //adding weighted, undirected connections between edges starting at Mega City
    world.addConnection("Mega City", "Slappy Shores", 2.0);
    world.addConnection("Mega City", "Frenzy Fields", 5.5);

    //adding weighted, undirected connections between edges starting at Slappy Shores
    world.addConnection("Slappy Shores", "Faulty Splits", 4.0);

    //adding weighted, undirected connections between edges starting at Faulty Splits
    world.addConnection("Faulty Splits", "Frenzy Fields", 3.0);
    world.addConnection("Faulty Splits", "Shattered Slabs", 2.5);

    //adding weighted, undirected connections between edges starting at Frenzy Fields
    world.addConnection("Frenzy Fields", "Shattered Slabs", 4.5);

    //adding a single chest to each named POI
    world.addChest("Lonely Labs", db.openChest());
    world.addChest("Brutal Bastion", db.openChest());
    world.addChest("Anvil Square", db.openChest());
    world.addChest("Mega City", db.openChest());
    world.addChest("Slappy Shores", db.openChest());
    world.addChest("Frenzy Fields", db.openChest());
    world.addChest("Faulty Splits", db.openChest());

    return world;
}