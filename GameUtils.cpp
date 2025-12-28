#include "GameUtils.hpp"

void inputLocation(string &input)
{
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    for (int i = 0; i < input.size(); i++)
    {
        if (i == 0)
            input[i] = toupper(input[i]);
        else if (input[i - 1] == ' ')
            input[i] = toupper(input[i]);
        else
            input[i] = tolower(input[i]);
    }
}

bool checkQuit(string &input)
{
    input.erase(0, input.find_first_not_of(" \t\n\r"));
    input.erase(input.find_last_not_of(" \t\n\r") + 1);

    for (int i = 0; i < input.size(); i++)
        input[i] = tolower(input[i]);
    
    if (input == "quit")
        return false;
    
    return true;
}