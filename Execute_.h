#ifndef EXECUTE_
#define EXECUTE_
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include "Package_.h"

using namespace std;

class Execute{
    vector<string> holdCommands;
    vector<char> holdLogic;
    vector<Package> holdPackages;
    vector<string> executionVec; 
    int boolMarker;
    int commandStatus;
    const char* execArgs[50];
    //Package workingPackage;
    public:
        void receivePackage(vector<Package>); /* we take a package given to the Command class by the controller. and immediately unpacks it and marks if it contains operators or not*/
        void unpack(Package);  /* will unpack and place our package command and logic 
        vectors into the holdCommands and holdLogic vectors respectively */
        bool executeCommands(); //creates a fork and attempts to execute the command loaded into execArgs[50], it returns a char to alert whether command executed or failed.
        void loadConstChar(); //loads execArgs[50 with the contents of executionVec
        vector<Package> returnPackageVector();  //returns package vector
        void printContents();   //prints the contents of holdCommands and holdLogic
        bool createArgVec(string); //takes a single string of instructinos from holdCommands and splits it into individual words and places it into executionVec;
        //This function is critical to the exit process, it will return a true value if it detects that the 'terminate' command has been entered.
        string returnCommand(int); //this returns a string from within the holdCommand vector
        bool executePackage(); //no functionlity implemented yet
        bool executeSingle(string);
       // bool executeTest(int, string , char);
       // bool stat(int, char*argv[], char);
       bool runTest(string);
       bool checkTest(string);
       bool check_stat(int, char*argv[], char);
};
#endif
