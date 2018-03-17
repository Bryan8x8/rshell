#include "Redirection_.h"

using namespace std;

void Redirection::direct_loop(char*** cmd)
{
     int   p[2];
  pid_t pid;
  int   fd_in = 0;
  int in;
  int out;
  //cout << "entering direct_loop" << endl;
  

  while ((*cmd != NULL) && (logicRedirect.size() != 0))
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if ((pid == 0) && (logicRedirect[0] == '|' ))
        {
          //cout << "hit |" << endl;
          //cout << logic.size() << endl;
          //here we have entered the child function.
          dup2(fd_in, 0); //change the input according to the old one 
          //fd_in is pointing to the file descriptor that holds the output from a previous loop.
          if (*(cmd + 1) != NULL){ //this checks to make sure that we are not on the final command.
          //cout << "this should still output" << endl;
          //cout << (*cmd)[0] << endl;
            dup2(p[1], 1); //sets pipe (write) to std_output 
          }
          //if we skip this if statement, we know we are at the final command and we want its output to hit STDOUT
          close(p[0]); //we are closing pipe input (read)
          execvp((*cmd)[0], *cmd); //executes the current cmd that the cmd[] array is pointing too
          //because our pipe duplicated was set to std_output, whatever the command outputs will now be written onto our pipe.
          exit(EXIT_FAILURE);
        }
        else if ((pid == 0) && (logicRedirect[0] == '<'))
        {
          //cout << "hit <" << endl;
          //here we have entered the child function.
          //dup2(fd_in, 0); //change the input according to the old one, fd_in is pointing to the file descriptor that holds the output from a previous loop.
          in = open(*(cmd+1)[0], O_RDONLY);
          dup2(in,0); //this is how I will read
          dup2(p[1], 1); //sets pipe (write) to std_output 
          //if we skip this if statement, we know we are at the final command and we want its output to hit STDOUT
          close(p[0]); //we are closing pipe input (read)
          execvp((*cmd)[0], *cmd); //executes the current cmd that the cmd[] array is pointing too
          exit(EXIT_FAILURE);
        }
        else if ((pid == 0) && (logicRedirect[0] == '>'))
        {
          //cout <<"hit >"<< endl;
          //here we have entered the child function.
          //dup2(fd_in, 0); //change the input according to the old one, fd_in is pointing to the file descriptor that holds the output from a previous loop.
          out = open(*(cmd)[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); 
          dup2(fd_in, 0); //change the input according to the old one 
          dup2(out, 1); //sets pipe (write) to std_output 
          //if we skip this if statement, we know we are at the final command and we want its output to hit STDOUT
          close(out);
          close(p[0]); //we are closing pipe input (read)
          const char* indoorCat[] = {"cat", NULL}; 
          const char** inCmd[] = {indoorCat, NULL};
          execvp((indoorCat)[0], (char**)indoorCat); //executes the current cmd that the cmd[] array is pointing too
          exit(EXIT_FAILURE);
          
        }
        else if ((pid == 0) && (logicRedirect[0] == '^'))
        {
          //cout <<"hit >>"<< endl;
          //here we have entered the child function.
          //dup2(fd_in, 0); //change the input according to the old one, fd_in is pointing to the file descriptor that holds the output from a previous loop.
          out = open(*(cmd)[0], O_WRONLY | O_APPEND); 
          dup2(fd_in, 0); //change the input according to the old one 
          dup2(out, 1); //sets pipe (write) to std_output 
          //if we skip this if statement, we know we are at the final command and we want its output to hit STDOUT
          close(out);
          close(p[0]); //we are closing pipe input (read)
          const char* indoorCat[] = {"cat", NULL}; 
          const char** inCmd[] = {indoorCat, NULL};
          execvp((indoorCat)[0], (char**)indoorCat); //executes the current cmd that the cmd[] array is pointing too
          exit(EXIT_FAILURE);
          
        }
        
      else
        {
          wait(NULL);
          //cout << "else hit" << endl;
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          // I beleive this is storing the pipe output file desrciptor to fd_in for later use
          if(((logicRedirect[0] == '|') || (logicRedirect[0] == '>') || (logicRedirect[0] == '^')) && (*(cmd + 1) != NULL))
          {
            //cout<< "hit one iterator" <<endl;
            cmd++; //shifts working command
            logicRedirect.erase(logicRedirect.begin());
          }
          else if((logicRedirect[0] == '<') && (*(cmd + 1) != NULL))
          {
              //cout << "hit two iterator"<<endl;
              cmd++;
              cmd++;
              logicRedirect.erase(logicRedirect.begin());
          }
          else
          {
              cmd++;
          }
        }
    }
}

void Redirection::processRedirct(string testInput)
{
    bool charHit = false;
    int startSplit = 0;
    int endSplit;
    int i = 0;
    string pushThis;
    while(i<testInput.length())
    {
        if(testInput[i] == '<')
        {
           logicRedirect.push_back('<');
           pushThis = testInput.substr(startSplit, i-startSplit);
           pushThis = parse.removeWhiteSpace(pushThis);
           //cout << "Pushing: " << pushThis << endl;
           commandsRedirect.push_back(pushThis);
           startSplit = i+1;
        }
        if(testInput[i] == '|')
        {
            logicRedirect.push_back('|');
            pushThis = testInput.substr(startSplit, i-startSplit);
            pushThis = parse.removeWhiteSpace(pushThis);
            //cout << "Pushing: " << pushThis << endl;
            commandsRedirect.push_back(pushThis);
            startSplit = i+1;
            
        }
        if(testInput[i] == '>' && testInput[i+1] != '>' && testInput[i-1] != '>')
        {
            logicRedirect.push_back('>');
            pushThis = testInput.substr(startSplit, i-startSplit);
            pushThis = parse.removeWhiteSpace(pushThis);
            //cout << "Pushing: " << pushThis << endl;
            commandsRedirect.push_back(pushThis);
            startSplit = i+1;
            
        }
        if(testInput[i] == '>' && testInput[i+1] == '>')
        {
            logicRedirect.push_back('^');
            pushThis = testInput.substr(startSplit, i-startSplit);
            pushThis = parse.removeWhiteSpace(pushThis);
            //cout << "Pushing: " << pushThis << endl;
            commandsRedirect.push_back(pushThis);
            startSplit = i+2;

        }
        if(i == testInput.length() - 1)
        {
            pushThis = testInput.substr(startSplit, i-startSplit+1);
            pushThis = parse.removeWhiteSpace(pushThis);
            //cout << "Pushing: " << pushThis << endl;
            commandsRedirect.push_back(pushThis);
            startSplit = i+1;
        }
        i++;
    }
    //return input1.substr(startSplit, endSplit);
    
}

bool Redirection::detectRedirection(string testInput)
{
    bool breakBool = false;
    int i = 0;
    while((!breakBool) && (i<testInput.length()))
    {
        if(((testInput[i] == '|') || (testInput[i] == '<') || (testInput[i] == '>')))
        {
            breakBool == true;
        }
        i++;
    }
    cout << "detected redirection!" << endl;
    return breakBool;
}

bool Redirection::createArgVec (string input){
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

void Redirection::loadConstChar()
{
  //*(cmd)[0]
  for(int j = 0; j < commandsRedirect.size(); j++)
  {
    if(j==0){
    createArgVec(commandsRedirect[j]);
    for(int i = 0; i < executionVec.size(); i++ ){
        //cout << executionVec[i] << endl;
        cmd0[i] = (char*) malloc(50);
        strcpy((char*)cmd0[i], (const char*)executionVec[i].c_str());
        
    }
    cmd0[executionVec.size()] = NULL;
    //cmd0 = execArgs1;
    //cout << "cmd0[0]: " << cmd0[0] << endl;
    }
    
    if(j==1){
    createArgVec(commandsRedirect[j]);
    for(int i = 0; i < executionVec.size(); i++ ){
        //cout << executionVec[i] << endl;
        cmd1[i] = (char*) malloc(50);
        strcpy((char*)cmd1[i], (const char*)executionVec[i].c_str());
        //executionVec[i].c_str();
    }
    cmd1[executionVec.size()] = NULL;
    //cmd1 = execArgs2;
    ///cout << "cmd0[0]: " << cmd0[0] << endl;
    //cout << "cmd1[0]: " << cmd1[0] << endl;
    }
    
    if(j==2){
    createArgVec(commandsRedirect[j]);
    for(int i = 0; i < executionVec.size(); i++ ){
        cmd2[i] = (char*) malloc(50);
        strcpy((char*)cmd2[i], (const char*)executionVec[i].c_str());
    }
    cmd2[executionVec.size()] = NULL;
    //cmd2 = execArgs3;
    //cout << "cmd0[0]: " << cmd0[0] << endl;
    //cout << "cmd1[0]: " << cmd1[0] << endl;
    //cout << "cmd2[0]: " << cmd2[0] << endl;
    }
    
    if(j==3){
    createArgVec(commandsRedirect[j]);
    for(int i = 0; i < executionVec.size(); i++ ){
        //cout << executionVec[i] << endl;
        cmd3[i] = (char*) malloc(50);
        strcpy((char*)cmd3[i], (const char*)executionVec[i].c_str());
    }
    cmd3[executionVec.size()] = NULL;
    //cmd3 = execArgs4;
    //cout << "cmd0[0]: " << cmd0[0] << endl;
    //cout << "cmd1[0]: " << cmd1[0] << endl;
    //cout << "cmd2[0]: " << cmd2[0] << endl;
    //cout << "cmd3[0]: " << cmd3[0] << endl;
    }
  }
  
  //**(cmd+commandsRedirect.size()) = NULL;
  
};

void Redirection::runRedirection(string inps)
{
  processRedirct(inps);
  loadConstChar();
  const char** cmd[] = {cmd0,cmd1,cmd2,cmd3,cmd4,cmd5,cmd6,cmd7,cmd8,cmd9,cmd10,cmd11,cmd12,cmd13,cmd14, NULL};
  direct_loop((char***)cmd);
  
}
