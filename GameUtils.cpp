#include "GameUtils.hpp"

#include <string>

//converting the user's input string for a location name into its appropiate form
void inputLocation(string &input)
{
    //trimming whitespaces around the string
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    //iterating through each character of the string
    for (int i = 0; i < input.size(); i++)
    {
        //making the first character uppercase
        if (i == 0)
            input[i] = toupper(input[i]);
        //making the first character following a whitespace uppercase
        else if (input[i - 1] == ' ')
            input[i] = toupper(input[i]);
        //converting all other characters to lowercase
        else
            input[i] = tolower(input[i]);
    }
}

//checking if the user input a "quit" signalling the game to end
bool checkQuit(string input)
{
    //trimming whitespaces around the string
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    //converting each letter to be lowercase
    for (int i = 0; i < input.size(); i++)
        input[i] = tolower(input[i]);
    
    //returning false if the user wants to quit the game
    if (input == "quit")
        return false;
    
    return true;
}

//converting an item's rarity into a string
string rarityToString(const rarity &r)
{
    switch (r)
    {
        case Common: return "Common";
        case Uncommon: return "Uncommon";
        case Rare: return "Rare";
        case Epic: return "Epic";
        case Legendary: return "Legendary";
        case Mythic: return "Mythic";
        case Exotic: return "Exotic";
    }

    return "Unknown";
}

//converting a weapon's bullet type into a string
string bulletToString(const bullet &b)
{
    switch (b)
    {
        case Light: return "Light";
        case Medium: return "Medium";
        case Heavy: return "Heavy";
        case Shells: return "Shells";
        case Rockets: return "Rockets";
    }

    return "Unknown";
}

//converting an item's type into a string
string typeToString(const type &t)
{
    switch (t)
    {
        case Gun: return "Weapon";
        case Consumable: return "Consumable";
        case Bullet: return "Bullet";
        case Throwable: return "Throwable";
        case Utility: return "Utility";
    }

    return "Unknown";
}

//converting the desired argv value into a string
string getArgValue(const int &argc, const char *argv[], const string &key)
{
    //variable declaration to temporarily store command line argument
    string argString;

    //for loop iterating to read how many times the program should execute
    for (int i = 1; i < argc; i++)
    {
        //storing the current command line argument into a string
        argString = argv[i];

        //checking if the current command line argument is "--runs". if that is the case, the next command line argument is the number of times the program will run
        if (argString == key && i + 1 < argc)
            return argv[i + 1];
    }

    return "";
}