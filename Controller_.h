#ifndef CONTROLLER_
#define CONTROLLER_
#include <iostream>
#include <vector>
#include <string>
#include "Packager_.h"
#include "Execute_.h"
#include "Package_.h"
#include "Redirection_.h"

using namespace std;

class Controller{
   
    string input;
    char masterIndicator;
    bool terminationFlag = false;
    string semiString;
    Packager parse;
    Execute executer;
    Redirection redirect;
    
    public:
       string receiveInput();
       void displayInput();
       bool receiveAndRun(string);
       char seekOp(string);
       string clearOp(string);
       bool runParen(string, bool);
       bool semiParse(string);
       bool execParen(string);
       char opCheck(string);
       bool properParen(string);
       string handleComment(string);
       bool checkTermination(string);
       bool returnTerm();
       bool detectRedirection(string);
};

#endif
