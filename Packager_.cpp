#include <iostream>
#include <vector>
#include <string>
#include "Packager_.h"

//readInput, takes a string parses it up into seperate commands 
void Packager::commandParse (string input) {
    
  int startSplit = 0;
  int endSplit;
  char testValue; 
  string subString;
  vector<string> tempVec;
  
  for (int i=0; i<input.length(); i++) {
     char testValue = input[i];
     if(testValue == ';') //this if statement will seek all commands from start to just before the end of the string
     {
         //std::cout<<"Main Hit"<<std::endl;
         endSplit = i-startSplit; //this is done to remove the ';' from the substring
         subString = input.substr(startSplit, endSplit);
         tempVec.push_back(subString);
         startSplit = i+1; //sets new starting point for the start string just beyond the ';'

         
     }
     if (i == input.length()-1) //this if statement will capture the final/single command
     {
         if(input[i] != ';')
         {
            //std::cout<<input[i]<<std::endl;
            //std::cout<<"if hit"<<std::endl;
            endSplit = i+1;
            subString = input.substr(startSplit, endSplit);
            tempVec.push_back(subString);
         }
     }
     if (testValue == '#')
     {
         i = input.length();
     }
   
  }
    commandVec = tempVec;
}

void Packager::packageCommands () {
    /*this function will take the parsed command vec and edit the commands further
     by seperating the commands and the bool values and placing them into a package class
     and uploads them to a package vector*/
     //std::cout<< "<from Packager>: commandVec.size(): " << commandVec.size() << std::endl;
     vector<Package> tempVec;
     for (int i=0; i<commandVec.size(); i++){
         string testString = commandVec[i]; //current command to be cleaned up
         int startSplit = 0;
         int endSplit;
         string subString;
         char logicChar;
         //std::cout<< "a new package has been built" << std::endl;
         tempVec.push_back(Package()); //an empty package has been created and pushed into the packagevector
         //Package currentPackage = packageVector[i]; //sets currentPackage to the new empty variable

         
         for(int j=0; j<testString.length(); j++){
             if((testString[j] == '&') && (testString[j+1] == '&') && (testString[j+2] != '&')){ //testing for '&&' bool statement
                 tempVec[i].addLogic('&'); //places an '&' into the package bool vector
                 //now building the command string to be added to package
                 endSplit = j-startSplit; //this is done to remove the '&' from the substring
                 subString = testString.substr(startSplit, endSplit);
                 //std::cout << "<Package: " << i << "> --- Adding: " << subString << std::endl;
                 tempVec[i].addCommand(subString);
                 startSplit = j+2; //sets new starting point for the start string just beyond the '&&'
             }
             
             if((testString[j] == '|') && (testString[j+1] == '|') && (testString[j+2] != '|')){ //testing for '||' bool statement
                 tempVec[i].addLogic('|'); //places an '|' into the package bool vector
                 //now building the command string to be added to package
                 endSplit = j-startSplit; //this is done to remove the '|' from the substring
                 subString = testString.substr(startSplit, endSplit);
                // std::cout << "<Package: " << i << "> --- Adding: " << subString << std::endl;
                 tempVec[i].addCommand(subString);
                 startSplit = j+2; //sets new starting point for the start string just beyond the '||'
             }
             
             if (j == testString.length()-1) //this if statement will capture a command that does not contain booleans or final command of a chain of commands.
            {
                endSplit = j+1;
                subString = testString.substr(startSplit, endSplit);
               // std::cout << "<Package: " << i << "> --- Adding: " << subString << std::endl;
                startSplit = j+1;
                tempVec[i].addCommand(subString); //adds the command substring to the command vector of the package.
               // std::cout<< packageVector[i].getCommands(0) << " has been added" << std::endl;
                
            }
         }
     }
    packageVector = tempVec; //packageVector is cleared and takes in tempVec values.
}

vector<string> Packager::returnVector(){
   //...
   vector <string> retVec = commandVec;
   //...
   return retVec;
}

vector<Package> Packager::returnPackageVector(){
   //...
   //vector<Package> retVec = packageVector;
   //...
   return packageVector;
}

Package Packager::returnPackage(int input)
{
    //Package tempPack = packageVector[input];
    return packageVector[input];
}

void Packager::displayCmdVector(){
   //...
   std::cout << "<Command Vector Contents" << std::endl;
   for(int i=0;i<commandVec.size();i++)
   {
       std::cout << "commandVec[" << i << "]: "<< commandVec[i] << std::endl;
   }
   //...
}

bool Packager::detectParen(string input){
    bool detector = false;
    bool initDetect = false;
    for(int i = 0; i<input.length(); i++)
    {
        if(input[i] == '('){
            initDetect = true; //first parenthesis hit
        }
        if(initDetect && input[i] == ')') //only test for second parenthesis if there exists an intial one
        {
            detector = true; //two parenthesis hit in the correct order!
            //std::cout << "paren hit" << std::endl;
        }
    }
    return detector;
}

string Packager::parseParen(string input1){
    int i = 0;
    bool initialBool = false;
    bool twoParBool;
    int startSplit=0;
    int endSplit=0; 
    string splitString;
    //std::cout<< initialBool << std::endl;
    //cout << "hit" << endl;
    while ((i<input1.length()) && (input1.length() != 0))
    {
        char testValue = input1[i];
        char currentChar; 
        if((testValue == '('))
        {
            if(!initialBool){
                startSplit = i+1; 
                //std::cout<< "hit 1" << std::endl;
                initialBool = true;
            }
            else
            {
                initialBool = false; 
                //std::cout<<"hit 2" << std::endl;
            }
        }
        if(testValue == ')')
        {
            if(!initialBool){
                
                initialBool = true;
                //std::cout<<"hit 3" << std::endl;
            }
            else{
                //std::cout<<"hit 4" << std::endl;
                endSplit = i - startSplit;      
                //std::cout<< endSplit << std::endl;
                i = input1.length();
            }
        }
        i++;
    }
        
        return splitString = input1.substr(startSplit, endSplit);
}

string Packager::parenCmdParse(string input1){
    bool charHit = false;
    int startSplit = 0;
    int endSplit;
    int i = 0;
    while((!charHit) && (i<input1.length()))
    {
        if(input1[i] == '&')
        {
            //std::cout<<"hit 1"<<std::endl;
            if(input1[i+1] == '&')
            {
                //std::cout<<"hit 2"<<std::endl;
                charHit = true;
                endSplit = i;
            }
        }
        if(input1[i] == '|')
        {
            if(input1[i+1] == '|')
            {
                charHit = true;
                endSplit = i;
            }
        }
        if(input1[i] == '(')
        {
            charHit = true;
            endSplit = i;
        }
        i++;
    }
    return input1.substr(startSplit, endSplit);
}

string Packager::removeWhiteSpace(string input1)
{
    int strLength = input1.length();
    int i = 0;
    while(input1[i] == ' ')
    {
        i++;
    }
    
    return input1 = input1.substr(i, strLength-i);
}










