#ifndef PACKAGER_
#define PACKAGER_
#include <iostream>
#include <vector>
#include <string>
#include "Package_.h"

using namespace std;

class Packager {
    //commandVec contains all the split commands, it has still not been processed to deal with boolean logic.
    vector <string> commandVec;
    vector<Package> packageVector;

  public:
    void commandParse (string);
    void packageCommands();
    vector<string> returnVector();
    vector<Package> returnPackageVector();
    void displayCmdVector();
    Package returnPackage(int);
    bool detectParen(string); //this exists to tell us if there are proper parenthesis within the input
    string parseParen(string);
    string parenCmdParse(string);
    string removeWhiteSpace(string);
}; 

#endif
