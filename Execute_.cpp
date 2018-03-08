#include "Execute_.h"

using namespace std;

void Execute::receivePackage(vector<Package> inputPack){
    holdPackages = inputPack;
};

void Execute::unpack(Package currentPack){
    holdCommands = currentPack.getCommandVec();
    holdLogic = currentPack.getLogicVec();
};

bool Execute::executeCommands(){
    bool tempBool = true;
    char tempChar = 't';
    //building pipe
    int mypipefd[2];
    int ret;
    char buf[20];
    ret = pipe(mypipefd);
    if(ret == 1){
        perror("pipe");
        exit(1);
    }
    //forking:
    pid_t pid=fork();
    if (pid==0)
    { /* child process */
            //std::cout << "Hit Exec" << std::endl;
            execvp(execArgs[0], (char**)execArgs);
            
            write(mypipefd[1], "f", 12);
            close(mypipefd[0]);
            exit(127); /* only if execv fails */
    }
    else
    { /* pid!=0; parent process */
        waitpid(pid,0,0); 
        close(mypipefd[1]);
        read(mypipefd[0], buf, 15);
        tempChar = buf[0];
        //std::cout<< "tempChar:" << buf[0] << std::endl;
        if(tempChar == 'f')
        {
            tempBool = false;
        }
    }
    return tempBool;
};
    
void Execute::loadConstChar()
{
    for(int i = 0; i < executionVec.size(); i++ ){
        execArgs[i] = executionVec[i].c_str();
    }
    execArgs[executionVec.size()] = NULL;

};

vector<Package> Execute::returnPackageVector(){
    return holdPackages;
};

void Execute::printContents(){
    std::cout << "Printing out logic vec contents: " << std::endl;
    for(int i = 0; i < holdLogic.size(); i++){
        std::cout << holdLogic[i] << std::endl;
    }
    std::cout << "Printing out command vec contents: " << std::endl;
    for(int i = 0; i < holdCommands.size(); i++){
        std::cout << holdCommands[i] << std::endl;
    }
};

bool Execute::createArgVec (string input){
    vector<string> execArr;
    bool exitBool = false;
    int startSplit;
    int endSplit;
    int j = 0;
    string subString;
    for(int i=0; i<input.length(); i++){
        if(!isspace(input[i])&& ((input[i] != '\'') && (input[i] != '"'))){
            startSplit = i;
            i++;
            while(((!isspace(input[i])) && (i < input.length()))){
                i++;
            }
            endSplit = i - startSplit;
            subString = input.substr(startSplit, endSplit);
            //std::cout << "Loading Command: " << subString << std::endl;
            execArr.push_back(subString);
            startSplit = i+1;
            j++;
        }
        if((input[i] == '"') || (input[i] == '\'')){
            //std::cout<<"Is there something here" << std::endl;
            startSplit = i+1;
            i++;
            while((input[i] != '"') && (input[i] != '\''))
            {
                i++;
            }
            endSplit = i - startSplit;
            subString = input.substr(startSplit, endSplit);
            execArr.push_back(subString);
            startSplit = i+1;
            j++;
        }
        if(subString == "terminate")
        {
            exitBool = true;
            //std::cout << "terminate detected" << std::endl;
        }
    }
    executionVec = execArr; 
    return exitBool;    
};

string Execute::returnCommand(int input){
  return holdCommands[input];  
};

bool Execute::executePackage(){
    bool exitBool = false;
    for(int i = 0; i < holdPackages.size(); i++){
        unpack(holdPackages[i]); //current package is being unpacked and holdCommand and holdLogic are being populated with current package vectors
        if(holdLogic.size() == 0 && !exitBool) //there is no logic, the package is a single command, execute it.
        {
            exitBool = createArgVec(holdCommands[0]);
            if(exitBool){ 
             i = holdPackages.size(); 
             //exitBool = true;
            }
            loadConstChar();
            executeCommands();    
            //cout<<i<<endl;
        }
        if(holdLogic.size() != 0 && !exitBool)
        {
            bool checkBool;
            exitBool = createArgVec(holdCommands[0]);
            if(exitBool){ 
             i = holdPackages.size();  
             //exitBool = true;
            }
            loadConstChar();
            checkBool = executeCommands(); //first command in the vector has been executed, and bool is loaded indicating whether the first command failed or succeeded.
            if(!exitBool){
                for(int k = 1; k < holdCommands.size(); k++)
                {
                    if(checkBool && holdLogic[k-1] == '&')
                    {
                        exitBool = createArgVec(holdCommands[k]);
                        if(exitBool){ 
                            k = holdCommands.size(); 
                            //exitBool = true;
                        }
                        loadConstChar();
                        checkBool = executeCommands(); 
                    }
                    if(!checkBool && holdLogic[k-1] == '|')
                    {
                        exitBool = createArgVec(holdCommands[k]);
                        if(exitBool){ 
                            k = holdCommands.size(); 
                            //exitBool = true;
                        }
                        loadConstChar();
                        checkBool = executeCommands();    
                    }
                }
            }
        }
    }
    return exitBool;
};

bool Execute::executeSingle(string input)
{
    createArgVec(input);
    loadConstChar();
    return executeCommands();
}

bool Execute::checkTest(string inp)
{
    Packager parse;
    string temp = parse.removeWhiteSpace(inp);
    inp = temp;
    //cout <<inp << endl;
    
    //check for []
    bool mainTest = false;
    bool whileBool = true;
    bool isBracketTest = false;
    bool isStringTest = false;
    bool firstBool = false;
    char flagChar;
    int n = 0;
    while((whileBool) && (n <= inp.length()))
    {
        if(inp[0] == '[')
        {
            firstBool = true;
        }
        if((inp[n] == ']') && (firstBool))
        {
            isBracketTest = true;      //we have found a test
            whileBool = false; //break this loop
            inp = inp.substr(0,n);
            //cout << inp << endl;
        }
        n++;
    }
    string stringCheck;
    stringCheck = temp.substr(0,4);
    //cout <<stringCheck<<endl;
    if(stringCheck == "test")
    {
        //cout << "hit2" << endl;
        isStringTest = true;
    }
    //this tests if we have a string test.
    if(isBracketTest){
        bool flagHit = false;
        bool firstHit;
        int j = 0;
        while((!flagHit) && (j <= inp.length()))
        {
            if(inp[j] == '-')
            {
                flagChar = inp[j+1];
                flagHit = true;
            }
            j++;
        }
        if(flagHit){
            //cout << "hit" <<endl;
            inp = inp.substr(j+1,inp.length()-(j)); //this removes the initial flag
            //cout << inp << endl;
        }
    }
    if(isStringTest)
    {
        bool flagHit2 = false;
        int q = 0;
        while((!flagHit2) && (q <= inp.length()))
        {
            if(inp[q] == '-')
            {
                //cout << "hit" << endl;
                flagChar = inp[q+1];
                flagHit2 = true;
            }
            q++;
        }
        if(flagHit2){
            inp = inp.substr(q+1,inp.length()-(q+1)); //this removes the initial flag
            //cout << inp << endl;
        }
    }
    if((isBracketTest == true) || (isStringTest == true))
    {
        mainTest = true;
    }
    return mainTest;
    //cout<<mainTest<<endl;
}

bool Execute::runTest(string inp)
{
    //cout<<"RUNTEST"<<endl;
    Packager parse;
    string temp = parse.removeWhiteSpace(inp);
    inp = temp;
    //cout <<inp << endl;
    
    //check for []
    bool masterBool = false;
    bool whileBool = true;
    bool isBracketTest = false;
    bool isStringTest = false;
    bool firstBool = false;
    char flagChar;
    int n = 0;
    while((whileBool) && (n <= inp.length()))
    {
        if(inp[0] == '[')
        {
            firstBool = true;
        }
        if((inp[n] == ']') && (firstBool))
        {
            isBracketTest = true;      //we have found a test
            whileBool = false; //break this loop
            inp = inp.substr(0,n);
            //cout << inp << endl;
        }
        n++;
    }
    string stringCheck;
    stringCheck = temp.substr(0,4);
    //cout <<stringCheck<<endl;
    if(stringCheck == "test")
    {
        //cout << "hit2" << endl;
        isStringTest = true;
    }
    //this tests if we have a string test.
    if(isBracketTest){
        bool flagHit = false;
        bool firstHit;
        int j = 0;
        while((!flagHit) && (j <= inp.length()))
        {
            if(inp[j] == '-')
            {
                flagChar = inp[j+1];
                flagHit = true;
            }
            j++;
        }
        if(flagHit){
            //cout << "hit" <<endl;
            inp = inp.substr(j+1,inp.length()-(j)); //this removes the initial flag
            //cout << inp << endl;
        }
    }
    if(isStringTest)
    {
        bool flagHit2 = false;
        int q = 0;
        while((!flagHit2) && (q <= inp.length()))
        {
            if(inp[q] == '-')
            {
                //cout << "hit" << endl;
                flagChar = inp[q+1];
                flagHit2 = true;
            }
            q++;
        }
        if(flagHit2){
            inp = inp.substr(q+1,inp.length()-(q+1)); //this removes the initial flag
            //cout << inp << endl;
        }
    }
    inp = parse.removeWhiteSpace(inp);
    //cout << flagChar << endl;
    bool moreTest = true;
    int v = inp.length();
    while(moreTest)
    {
      //  cout << "hit"<< endl;
        if(inp[v-1] == ' ')
        {
         //   cout<<"hit2"<<endl;
        inp = inp.substr(0,v-1);
        }
        if(inp[v-1] != ' ')
        {
            moreTest = false;
        }
        v--;
    }
    const char* argv[] = {inp.c_str()}; 
    masterBool = check_stat(2,(char**)argv,flagChar);
    if(masterBool == false)
    {
        string magicDirectoryString = "../../../../../../../../../../../";
        string superCool = magicDirectoryString + inp;
        //lets try again with the magical directory string
       // cout << superCool << "space test" <<endl;
        const char *argv[] = {superCool.c_str()}; 
        masterBool = check_stat(2,(char**)argv,flagChar);
    }
    return masterBool;
}

bool Execute::check_stat(int argc, char* argv[], char flagInput)
{
    char flag; 
    struct stat sb;     //sb is the buf holding the returned data when stat() is called
    bool mainBool = false;      //will be returned
    
    if (argc != 2){
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        return mainBool;
    }
    
    if (stat(argv[0], &sb) == -1)       //if stat() call failed
    {
        //perror("stat");
        return mainBool;
    }
    //this case calls stat
    //now we are checking the data within the buf to determine what was written was a file or directory
    //by defauly we have reached a file or folder
    //cases for file existence
    switch (sb.st_mode & S_IFMT){       //switch cases for file type
        case S_IFDIR: 
            //cout << "directory" << endl;
            if(flagInput == 'd')
            {
                mainBool = true;
                return mainBool;
            }  
            break;     //return true if file is a directory
        case S_IFREG:  
            //cout << "reg file" << endl;
            if(flagInput == 'f')
            {
                mainBool = true;
                return mainBool;
            }   
            break;     //return true if its a regular file
        default:    
            //cout << "exists" <<endl;
            if((flagInput == 'e') || (flagInput == 'f') || (flagInput == 'd'))
            {
                mainBool = true;
                return mainBool;
            }  
            break;     //default -e case, file exist
    }
    //cout << mainBool << endl;
    return mainBool;
    //exit(EXIT_SUCCESS);         //can be modified for function purposes within rshell
}
