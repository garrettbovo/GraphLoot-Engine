#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include "Item.hpp"

#include <iostream>
#include <string>
using namespace std;

//converts the user's destination string into its appropiate order
void inputLocation(string &);
//checks if the user's input ever is "quit"
bool checkQuit(string);
//returns an item's rarity into a string
string rarityToString(const rarity &);
//converts an item's bullet type into a string
string bulletToString(const bullet &);
//converts an item's category type into a string
string typeToString(const type &);
//converts the desired argv value into a stirng
string getArgValue(const int &, char *[], const string &);

#endif