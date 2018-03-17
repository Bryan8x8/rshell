#ifndef REDIRECTION
#define REDIRECTION
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
#include  <termios.h>
#include <cstring>
#include "fcntl.h"
#include "Packager_.h"
#include "Execute_.h"
#include "Package_.h"

using namespace std;

class Redirection{

    vector<char> logicRedirect;
    vector<string> commandsRedirect;
    vector<string> executionVec;
    const char* execArgs1[50];
    const char* execArgs2[50];
    const char* execArgs3[50];
    const char* execArgs4[50];
    Packager parse;
    
    const char *cmd0[50]; 
    const char* cmd1[50]; 
    const char* cmd2[50]; 
    const char* cmd3[50]; 
    const char* cmd4[50];
    const char* cmd5[50];
    const char* cmd6[50];
    const char* cmd7[50];
    const char* cmd8[50];
    const char* cmd9[50];
    const char* cmd10[50];
    const char* cmd11[50];
    const char* cmd12[50];
    const char* cmd13[50];
    const char* cmd14[50];
    
    public:
        /*Constructors*/
        //Redirection();
        //
        void direct_loop(char***);
        void processRedirct(string);
        bool detectRedirection(string);
        bool createArgVec(string);
        void loadConstChar();
        void runRedirection(string);
        
};

#endif
