#include <iostream>
#include <vector>
#include <string>
#include "Packager_.cpp"
#include "Execute_.cpp"
#include "Controller_.cpp"
#include "Package_.cpp"


using namespace std;

int main() {
    Controller control;
    Packager parse;
    bool breakLoop = false;
    std::cout << "Welcome to rshell, enter command 'terminate' to end your session." << std::endl;
    string holdInput;
    while(!breakLoop){
       std::cout<<"$ ";
       holdInput = control.receiveInput();
       holdInput = control.handleComment(holdInput);
       //cout << "Term Flag: " << control.returnTerm() << endl;
           if(control.properParen(holdInput))
           {
            control.execParen(holdInput);
           }
           else
           {
               cout << "Error: Improper Parenthesis" << endl;
           }
       
       if((holdInput == "terminate") || (control.returnTerm())){
           //cout<<"hit?"<<endl;
           breakLoop = true;
       }
    }
    return 0;
}
