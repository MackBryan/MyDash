#include "handleJob.h"
#include "mydash.h"
#include <sys/wait.h>
#include "changeDirectory.h"

 /* handleCommand is the base function
 * that will handle a command from input.
 * It uses the execvp command that allows
 * for normal command functionality.
 */
struct jobl *handleJob(char *command, char **token, int jobID, char *line){

    pid_t pid;
    int status;

    char *tL = malloc(strlen(line)+1);
    strcpy( tL ,line);

    //check for change directory
    if((strcmp(command, "cd")) == 0){
        changeDir(command,token[1]);

    }else{

        if ((pid = fork()) <0){
        err_sys("fork error");

        }else if(pid == 0){
            signal(SIGINT, SIG_IGN);
            signal(SIGTSTP, SIG_IGN);
            execvp(command, token);
            err_ret("couldn't execute bgprocess: %s", command);
            exit(EXIT_FAILURE);
        }
            //Populate our new job
            int newID = jobID;
            struct jobl *retJob = malloc(sizeof(struct jobl));
            retJob->jobID = newID;
            retJob->pid = pid;
            retJob->cmnd = command;
            retJob->done = 0;
            retJob->lne = tL;
            tL=NULL;
            //print new job to user
            printf("[%d] %d   %s \n", newID, pid, line);

            if ( (pid = waitpid(pid, &status, WNOHANG))<0  ){
                err_sys("bg waitpid error");
            }
            signal(SIGINT, sigintHandler);
            signal(SIGTSTP, sigstpHandler);

            //free(tL);
            return retJob;
    }
    struct jobl *r = NULL;

    return r;
    }

