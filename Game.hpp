#ifndef GAME_H
#define GAME_H

#include "World.hpp"
#include "ItemDatabase.hpp"

#include <string>

class Game
{
    World world;
    string currentLoc;

    public:
        Game() {}
        void setWorld(World wID) { world = wID; }
        World getWorld() const { return world; }
        void setCurrentLoc(string lID) { currentLoc = lID; }
        string getCurrentLoc() const { return currentLoc; }
        bool run(ItemDatabase &);
        void printWorld() const;
        ~Game() {}
};

#endif