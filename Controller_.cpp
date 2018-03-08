#include "Controller_.h"

using namespace std;

string Controller::receiveInput()
{
     getline(cin,input);
     return input;
};

void Controller::displayInput()
{
    std::cout << input << std::endl;
};

bool Controller::receiveAndRun(string input1)
{
    //cout <<"$ ";
    string tempString;
    int strLen = input.length();
    int endSplit;
    bool terminateBool = false;
    bool parenBool = false;
    //receiveInput(); //asking for user input;
    //parenBool = parse.detectParen(input1);
    parse.commandParse(input1);
    parse.packageCommands(); //input has been packaged
    executer.receivePackage(parse.returnPackageVector()); //package vector has been received by executer
    terminateBool = executer.executePackage(); //package is being executed
    return terminateBool;
    
};

char Controller::seekOp(string input1){
    bool breakBool = false;
    char indicator = 'e';
    int i = 0;
    while((i < input1.length()) && (!breakBool) && (input1.length() != 0))
    {
        if((input1[i] == '&') && (input1[i + 1] == '&'))
        {

            //input1 = input1.substr(i+2, (input1.length()-(i+2))); //removing operators from string
            indicator = '&';
            return indicator;
        }
        if((input1[i] == '|') && (input1[i + 1] == '|'))
        {
            breakBool = true;
            //input1 = input1.substr(i+2, (input1.length()-(i+2))); //removing operators from string
            indicator = '|';
            return indicator;
        }
        i++;
    }
    //cout << "seekOp return: " << indicator <<endl;
    return indicator;
};

string Controller::clearOp(string input1){
    bool breakBool = false;
    char indicator = 'e';
    int i = 0;
    //cout << "Initial value: " << input1 << endl;
    while((i < input1.length()) && (!breakBool) && (input1.length() != 0))
    {
        //cout << input1[i] << endl;
        if((input1[i] == '&') && (input1[i + 1] == '&'))
        {
            //cout << "hit & , current working string: " << input1 << endl;
            //cout << i+1 << endl;
            //cout << (input1.length()-(i+2)) << endl;
            breakBool = true;
            input1 = input1.substr((i + 2), (input1.length()-(i + 2))); //removing operators from string
            indicator = '&';
            return input1;
            
        }
        if((input1[i] == '|') && (input1[i + 1] == '|'))
        {
           //cout << "Hit at, " << i << endl;
            breakBool = true;
            input1 = input1.substr(i + 2, (input1.length()-(i + 2))); //removing operators from string
            indicator = '|';
            return input1;
        }
        i++;
    }
    return input1;
};
//flags will be used to mark recursion, either true or false
//flag will indicated whether semiString or input 1 is to be used!!!!
bool Controller::runParen(string input1, bool flag)
{
    //the recursive methods should not edit semiString at all, that should be left strictly to the parent
    string tempString;
    bool testBool;
    bool operate;
    char opChar = 'e';
    //REMOVING WHITE SPACE AND OPCHECK
    if(flag){
        semiString = parse.removeWhiteSpace(semiString); //any initial whitepace removed
        //cout << "Hit Removing White Space " << input1 << endl;
        if(input1 == "blackmagic"){}
        opChar = opCheck(semiString); //stores leading operator
        if (opChar != 'e') //this means we've hit an operator at the start of the string and it needs to be cleared before we can proceed
        {
            semiString = clearOp(semiString);
            semiString = parse.removeWhiteSpace(semiString);
            //cout << semiString << " this should get command parsed" << endl;
            if(semiString == "black magic"){}
        }
        if(semiString == "black magic"){}
        tempString = parse.parenCmdParse(semiString);
        semiString = semiString.substr(tempString.length(), semiString.length()-tempString.length());
        //cout << "1Hit first CMD parse attempt, " << tempString << endl;
    }
    else{
        input1 = parse.removeWhiteSpace(input1);
        //cout << "1 " << input1 << endl;
        //cout << "Hit Remvoing White Spave, " << input1 << endl;
        if(input1 == "black magic"){}
        opChar = opCheck(input1); //stores leading operator
        if (opChar != 'e') //this means we've hit an operator at the start of the string and it needs to be cleared before we can proceed
        {
            input1 = clearOp(input1);
            //cout << "2 " << input1 << endl;
            if(input1 == "black magic"){}
            input1 = parse.removeWhiteSpace(input1);
            //cout<<input1 << " this should get command parsed" << endl;
        } 
        if (input1 == "fuck this"){};
        /*Black magic conditional, everything codes fails without it and I don't know why. */
        tempString = parse.parenCmdParse(input1);
        input1 = input1.substr(tempString.length(), input1.length()-tempString.length());
        //cout << "Hit first CMD parse attempt, " << tempString << endl;
    }
    
    //CHECKING TO SEE IF CMD WAS SUCCESSFULLY PARSED
    //cout << "testBool: " << testBool << " opChar: " << opChar << " tempString: " << tempString << endl;
    if(testBool == false){}
    if(tempString == "blackmagic"){}
    if(opChar == 'F'){}
    if((tempString.length() != 0) && ((opChar == 'e') || ((opChar == '&') && (testBool == 1)) || ((opChar == '|') && (testBool == 0)))) //detects if single command is present, if so it is packaged and executed.
    {
        //we have entered into the single commands area now we must continue to search for single commands
        //COMMAND IS BEING EXECUTED AND ITS RESULT LOADED INTO TEST BOOL
       //cout << "Attempting execution using, tempString: " << tempString << endl;
       if(tempString == "blackmagic"){}
       //cout << tempString << endl;
        if((checkTermination(tempString)) || (terminationFlag))
        {
            //cout << "hit" << endl;
            terminationFlag = true;
            tempString.clear();
            semiString.clear();
            input.clear();
        }
        if((executer.checkTest(tempString)) && (!terminationFlag))
        {
            testBool = executer.runTest(tempString);
        }
        else
        {
            if(!terminationFlag){
            //cout << tempString << endl;
            testBool = executer.executeSingle(tempString); 
            }
            //cout << testBool << endl;
        }
        bool whileBreak = true;
        while (whileBreak)
        {
            
            //SEEKING AND CLEARING OPERATOR AND REMOVING WHITE SPACE
            if(flag){
                if (semiString == "black magic"){}
                opChar = seekOp(semiString);
                //cout << opChar << endl;
                semiString = clearOp(semiString);
                semiString = parse.removeWhiteSpace(semiString);
               //cout<<"seeking and removing Op, "<< opChar << ", semiString: " << semiString << endl;
            }
            else{
                if(input1 == "black magic"){}
                //cout << opChar << endl;
                string holdInput = input1;
                opChar = seekOp(input1);
                input1 = clearOp(holdInput);
                input1 = parse.removeWhiteSpace(input1);
                //cout<<"seeking and removing Op, " << opChar << ", input1: " << input1 << endl;

            }
            
            //ATTEMPTING TO LOAD A NEW COMMAND
            if(flag){
                if(semiString == "black Magic"){}
                tempString = parse.parenCmdParse(semiString);
                semiString = semiString.substr(tempString.length(), semiString.length()-tempString.length()); //this removes the processed string
              //cout << "new command, tempstring: " << tempString << endl;
            }
            else{
              if(input1 == "black magic"){}
                tempString = parse.parenCmdParse(input1);
                input1 = input1.substr(tempString.length(), input1.length()-tempString.length()); //this removes the processed string  
               //cout << "new command, tempstring: " << tempString << endl;
            }
            //cout << "opChar: " << opChar << " testBool: " << testBool << endl;
            if (((testBool == 1) && (opChar == '&')) || ((testBool == 0) && (opChar == '|'))) 
            {
                //cout << "hit" << endl;
                //cout << tempString << endl;
                if(tempString == "black magic"){}
                if((checkTermination(tempString)) || (terminationFlag))
                {
                    //cout << "hit" << endl;
                    terminationFlag = true;
                    tempString.clear();
                    semiString.clear();
                    input.clear();
                }
                //cout <<tempString<<endl;
                if((executer.checkTest(tempString)) && (!terminationFlag)){
                    testBool = executer.runTest(tempString);
                }
                else{
                if(!terminationFlag){
                //cout << tempString<<endl;
                testBool = executer.executeSingle(tempString);
                }
                }
            }
            if(tempString.length() == 0)
            {
                //cout << "exiting command loop" << endl;
                whileBreak = false; //testString returned as zero, we must hit the end of the command or a parenthesis
            }
        }
        
    }
    //we have handled all available sigle commands
    //we will handle the whole paren in here.
    //cout<< "Entering Parenthesis and recursion" << endl;
    if(flag){
        tempString = parse.parseParen(semiString); //we are checking to see if we have find any parenthesis
        if(tempString.length() != 0){ //the substr below expects parenthesis to be found, if there were none there is no need to split
            semiString = semiString.substr((tempString.length()+2), (semiString.length() - (tempString.length()+2))); //this removes the processed string
            //cout << "new semi: " << semiString << endl;
        }
        //cout << "Paren Parse, " << tempString << endl;
    }
    else{
        tempString = parse.parseParen(input1); //we are checking to see if we have find any parenthesis
        if(tempString.length() !=0){ //the substr below expects parenthesis to be found, if there were none there is no need to split
        input1 = input1.substr((tempString.length()+2), (input1.length() - (tempString.length()+2)));
        }
        //cout << "Paren Parse, " << tempString << endl;

    }
    if((tempString.length() > 0) && (((testBool == 1) && (opChar == '&')) || ((testBool == 0) && (opChar == '|')) || (opChar == 'e')))
    {
        //this handles all the commands within the pare
        //cout << "Recursing, flag: false, and tempString: " << tempString << endl;
        bool testBool = runParen(tempString, false); //recursion will handle whatever is inside the parenthesis and return a bool result.
    }
    if((semiString.length() > 1) && (flag))
    {
        bool testBool = runParen(semiString, true);
    }
    //cout <<"Run Paren Exiting" << endl;
    //cout << semiString << endl;
};

bool Controller::semiParse(string input1){
    bool semiHit = false;
    bool inputEnd = false;
    int i =0;
    while (!semiHit)
    {
        //std::cout<< "semiparse loop hit"<<std::endl;
        if(input1[i] == ';')
        {
           //std::cout<< "building first semi"<<std::endl;
            semiHit = true;
            semiString = input.substr(0, i);
            input = input.substr(semiString.length()+1, (input.length()-semiString.length())); //note we are parsing input for future semi parses
            //cout << "Releasing: " << semiString << endl;
        }
       
        if(i==input1.length())
        {
            //std::cout<<"loop broken"<<std::endl;
            semiHit = true; //this is to end the loop
            inputEnd = true; //input has ended 
            semiString = input;
            //cout << "releasing: "<< semiString << endl;
        }
        i++;
    }
    return inputEnd;
};

bool Controller::execParen(string input1)
{
    //receiveInput(); this is handled in rshell.
    bool inputEnd;
    input = input1;
    //inputEnd = semiParse(input1);
    while(!inputEnd)
    {
    //std::cout<<"exec Parenloop hit"<< std::endl;
    
    //std::cout<<"finished semiParse"<< std::endl;
    inputEnd = semiParse(input);
    //std::cout << semiString << std::endl;
    masterIndicator = 'e';
    runParen(semiString,true);
    

    }
    inputEnd = true;
};

char Controller::opCheck(string input1)
{
    char testChar = 'e';
    if((input1[0] == '&') && (input1[1] == '&'))
    {
        testChar = '&';
        return testChar;
    }
    if((input1[0] == '|') && (input1[1] == '|'))
    {
        testChar = '|';
        return testChar;
    }
    return testChar;
};

bool Controller::properParen(string moreInput){
    bool parenBool = false;
    int startParen = 0;
    int endParen = 0;
    for(int i=0; i < moreInput.length();i++ )
    {
        if(moreInput[i] == '(')
        {
            startParen++;
        }
        if(moreInput[i] == ')')
        {
            endParen++;
        }
    }
    if(startParen - endParen == 0)
    {
        //cout << startParen - endParen << endl;
        parenBool = true;
    } 
    return parenBool;
}

string Controller::handleComment(string moreInput)
{
    bool hitComment = false;
    int endSplit;
    string returnString;
    int k = 0;
    while((!hitComment) && (k<moreInput.length()))
    {
        if(moreInput[k] == '#')
        {
            endSplit = k;
            hitComment = true;
            returnString = moreInput.substr(0,k-1);
        }
        k++;
    }
    return moreInput;
    cout <<returnString<<endl;
    return returnString;
}

bool Controller::checkTermination(string evenMoreInput)
{
    //terminate
    bool termBool = false;
    if(evenMoreInput.length() >= 9){
        //cout << "hit" << endl;
        string checkThis = evenMoreInput.substr(0,9);
        if(checkThis == "terminate")
        {
            termBool = true;
        }
    }
    return termBool;
}

bool Controller::returnTerm(){
    return terminationFlag;
}
