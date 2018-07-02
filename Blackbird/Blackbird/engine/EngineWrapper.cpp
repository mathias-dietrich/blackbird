//
//  EngineWrapper.cpp
//  Blackbird
//
//  Created by Mathias Dietrich on 6/16/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#include "EngineWrapper.hpp"

#include <boost/algorithm/string/predicate.hpp>


bool isEngineRunning = false;

void EngineWrapper::setup(string engine){
   
    if(isEngineRunning){
        quit();
    }
     if(engine.substr(engine.length()-4) == "User"){
         return;
     }
    if(engine.substr(engine.length()-9) == "Blackbird"){
        isEngineRunning = true;
        isUci = true;
        return;
    }
     isUci = false;
    const char *cstr = engine.c_str();
    createChild(cstr);
    pthread_create(&threads[0], NULL,  staticFunction, this);
    isEngineRunning = true;
}

void EngineWrapper::quit(){
    if(isUci){
        return;
    }
    toEngine("quit\n");
}

bool StartsWith(const std::string& text,const std::string& token)
{
    if(text.length() < token.length())
        return false;
    return (text.compare(0, token.length(), token) == 0);
}

char *trimwhitespace(char *str)
{
    char *end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0)  // All spaces?
        return str;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator character
    end[1] = '\0';
    
    return str;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

std::vector<std::string> split_ws( std::string str )
{
    std::vector<std::string> result ;
    
    std::istringstream stm(str) ; // http://www.artima.com/cppsource/streamstrings3.html
    std::string token ;
    while( stm >> token ) result.push_back(token) ;
    // could use std::istream_iterator<std::string> instead
    
    return result ;
}

void EngineWrapper::memberFunction()
{
    while(true)
    {
        char buf[500];
        int n;
        while ( (n = read(aStdoutPipe[PIPE_READ], &buf, 500)) !=-1)  {
            std::string reply(buf, n);
            observer->logEngine(reply);
            std::vector<std::string> parts  = split_ws(reply);
      
            size_t found = reply.find("bestmove");
            
            if (found!=std::string::npos) {
                string cmd = reply.substr(found + 9,4);
               // int row =cmd[0]-97;
               // int col =(cmd[1]-49);
                int from = (cmd[0]-97) + 8 * (cmd[1]-49);
                int to = (cmd[2]-97) + 8 * (cmd[3]-49);
                
                std::cout << "found move: " << cmd << '\n';
                Ply ply;
                ply.from = from;
                ply.to = to;
                if(isEngineWhite){
                    observer->makeMoveWhite(ply);
                }else{
                    observer->makeMoveBlack(ply);
                }
            }
        }
    }
}

// Include error check here
void EngineWrapper::toEngine(const char* msg) {
    if(isUci){
        string cmd(msg);
        uci->listen(cmd);
        return;
    }
    write(aStdinPipe[PIPE_WRITE], msg, strlen(msg));
}

int EngineWrapper::createChild(const char* szCommand) {
    if (pipe(aStdinPipe) < 0) {
        perror("allocating pipe for child input redirect");
        return -1;
    }
    if (pipe(aStdoutPipe) < 0) {
        //close(aStdinPipe[PIPE_READ]);
        //close(aStdinPipe[PIPE_WRITE]);
        perror("allocating pipe for child output redirect");
        return -1;
    }
    
    nChild = fork();
    if (0 == nChild) {
        // child continues here
        
        // redirect stdin
        if (dup2(aStdinPipe[PIPE_READ], STDIN_FILENO) == -1) {
            perror("redirecting stdin");
            return -1;
        }
        
        // redirect stdout
        if (dup2(aStdoutPipe[PIPE_WRITE], STDOUT_FILENO) == -1) {
            perror("redirecting stdout");
            return -1;
        }
        
        // redirect stderr
        if (dup2(aStdoutPipe[PIPE_WRITE], STDERR_FILENO) == -1) {
            perror("redirecting stderr");
            return -1;
        }
        
        // all these are for use by parent only
        // close(aStdinPipe[PIPE_READ]);
        // close(aStdinPipe[PIPE_WRITE]);
        // close(aStdoutPipe[PIPE_READ]);
        // close(aStdoutPipe[PIPE_WRITE]);
        
        // run child process image
        // replace this with any exec* function find easier to use ("man exec")

        char * const command[] = {"", NULL};
        nResult = execve(szCommand, command, environ);
        
        // if we get here at all, an error occurred, but we are in the child
        // process, so just exit
        perror("exec of the child process");
        exit(nResult);
    } else if (nChild > 0) {
        // parent continues here
        
        // close unused file descriptors, these are for child only
        // close(aStdinPipe[PIPE_READ]);
        // close(aStdoutPipe[PIPE_WRITE]);
        
        // done with these in this example program, you would normally keep these
        // open of course as long as you want to talk to the child
        // close(aStdinPipe[PIPE_WRITE]);
        //close(aStdoutPipe[PIPE_READ]);
        
    } else {
        // failed to create child
        close(aStdinPipe[PIPE_READ]);
        close(aStdinPipe[PIPE_WRITE]);
        close(aStdoutPipe[PIPE_READ]);
        close(aStdoutPipe[PIPE_WRITE]);
    }
    return nChild;
}




