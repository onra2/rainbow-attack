#ifndef HELP_H
#define HELP_H

#include <iostream>

namespace crypto {

class help
{
public:
    help();
    static void displayPasswordGenerationHelp();
    static void displayCrackHelp();
    static void displayCheckPasswordHelp();
    static void displayRainbowTableHelp();
    static void displayCommandHelp();
    static void displayParameterHelp();
};

}

#endif // HELP_H
