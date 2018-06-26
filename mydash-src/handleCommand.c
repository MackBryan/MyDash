#include "handleCommand.h"
#include "mydash.h"
#include "changeDirectory.h"


void handleCommand(char *command, char **token){
    pid_t pid;
    int status;
    if((strcmp(command, "cd")) == 0){
        changeDir(command,token[1]);
    }else{

    if ((pid = fork()) < 0){
        err_sys("fork error");

    }else if (pid == 0) {        /* child */
        execvp(command, token);

        err_ret("couldn't execute: %s", command);

        exit(EXIT_FAILURE);

    }
        /* parent */
        if ( (pid = waitpid(0, &status, WUNTRACED)) < 0){
            err_sys("waitpid error");
        }


    }
    }



