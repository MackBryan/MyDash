/*
  This program needs the file error.c and ourhdr.h to compile.
 */
#include    "mydash.h"
#include    "listJobs.h"
#include    "checkBG.h"
#include    "getJobID.h"
#include    "handleJob.h"
#include    "parseInput.h"
#include    "handleCommand.h"
#include    "changeDirectory.h"
#include    <readline/readline.h>
#include    <readline/history.h>
#include    "../../p0/testsuite/Object.c"

char    *prompt;
const char* git_version(void);
void exitShell();
void getVersion(void);
void freeToken(char **toFree, int numTokens);
int fgTrue = 0; // 0 = prints caught-z/c and no fg process,
                // 1 = print stopped for fg process or nothing if no bg jobs
char *temp;     // Copy of input for bg jobs and stopped processes

int main(int argc, char *argv[])
{
    struct list *dll = NULL;
    char    **token;
    int     numTokens = 0;
    char    *lastParam;
    char    *command;
    char    *delimiter = " ;";
    char    *line;


    prompt = getenv("DASH_PROMPT");
    if(strlen(prompt) == 0 ){
        prompt = "mash>";
    }

    if(argc > 1){
        if((strcmp(argv[1],"-v")) == 0){
            getVersion();
        }
    }
    //Enable history
    using_history();

    signal(SIGINT, sigintHandler);
    signal(SIGTSTP,sigstpHandler);

    while ((line = readline(prompt))) {

        int bgJob = 0;
        if(line != NULL){//Will not add empty spaces to history
        add_history(line);
        }
        if(line[0] == '\0'){

        }else{
            if(strlen(line) >0){
            temp = malloc(strlen(line)+1);
            strcpy(temp, line);
            }
        }

        //tokenize input
        if(strlen(line) >0 ){
        token = parseInput(line, delimiter, &numTokens);

        //set command for correct execvp params
        command = token[0];
        }else{
            command = NULL;
            numTokens = 0;
        }

        //if empty command AKA Check DONE
        if(command == NULL){
            if(dll == NULL || dll->size < 1){
               // dll = createList(equals, toString, freeObject);
            }else{


                if(dll != NULL || dll->size > 0){
                   struct list *t = checkBG(dll);
                    int isDone = 0;
                    struct node *current = t->head;
                    struct jobl *cJob = current->obj;
                    while(current != NULL){
                        if(cJob->done == 1){
                            isDone++;
                        }
                        current = current->next;
                        if(current != NULL){
                            cJob = current->obj;
                        }
                    }// end while


                    if(isDone == t->size){
                        free(dll);
                        dll = NULL;
                        current = NULL;
                        cJob = NULL;
                    }else{
                        dll=t;
                    }

                }
            }
        }else if((strcmp(command, "jobs"))==0){
                if(dll == NULL){

                }else{
                    struct list *t;
                    t = listJobs(dll);

                    int isDone = 0;
                    struct node *current = t->head;
                    struct jobl *cJob = current->obj;

                    while(current != NULL){
                        if(cJob->done == 1){
                            isDone++;
                        }
                        current = current->next;
                        if(current != NULL){
                            cJob = current->obj;
                        }
                    }// end while
                    if(isDone == t->size){
                        free(dll);
                        dll = NULL;
                        current = NULL;
                        cJob = NULL;
                    }else{
                        dll=t;
                    }
                }
    }else{//else

            lastParam = token[numTokens - 1];

            //check if & was appended to any params
            if(strcmp(lastParam, "&") == 0){//not appended
                bgJob=1;
                free(token[numTokens-1]);
                token[numTokens- 1] = NULL;

            }else if(strstr(lastParam, "&") != NULL){//& appended

                bgJob =1;
                strtok(lastParam, "&" );

            }

            //Check for exit command
            if((strcmp(command, "exit")) == 0){
                freeToken(token, numTokens);
                free(line);
                exitShell();

            }

            //check for background job
            if( bgJob == 1){
                int tjobID;
                if(dll == NULL){
                    dll=createList(equals,toString,freeObject);
                    tjobID = 1;
                }else{
                    tjobID = getJobID(dll);
                }
                struct jobl *jl;
                jl = handleJob(command, token, tjobID, temp);
                struct node *nd = createNode(jl);
                addAtFront(dll, nd);

            }else{//if not bg-job
                // Our signal handler needs to know what to print,
                // set fg true and false after returning
                fgTrue = 1;
                handleCommand(command, token);
                fgTrue = 0;
                }
        }
        if(strlen(line) > 0){
            free(temp);
        }
        free(line);
        freeToken(token, numTokens);
        lastParam = NULL;
        temp = NULL;
        token = NULL;
        command = NULL;
    }
    free(line);
    freeList(dll);
    command = NULL;
    exit(EXIT_SUCCESS);
}


void sigintHandler(int signo){
    signal(SIGINT, sigintHandler);
    if(fgTrue == 0){ // If no foreground jobs
        printf("Caught Control-c \n%s", prompt);
    }
    // Catching the signal leaves us in the while(realine) loop still
    // and does not return prompt so I cheesed it and put a fake one
    // in for anyone curious
}


void sigstpHandler(int signo){
    signal(SIGTSTP, sigstpHandler);
    //int status = 0;
    //waitpid(0,&status, WUNTRACED);
    if(fgTrue == 0){// If no foreground jobs
    printf("Caught Control-z \n%s", prompt);
    }else{// Else we are running a fg process and we stopped it
        printf("[1]  Stopped %s \n", temp);
    }
}


/**
 * freeToken will free malloc'd
 * token array to allow for new
 * dash input.
 */
void freeToken(char **toFree, int numTokens){
    int i = 0;

    if(numTokens == 0){

    }else{
        for(i = 0; i <= numTokens+1  ; i++){

            free(toFree[i]);

        }
    }//end else
        if(numTokens > 0){
        free(toFree);
    }

    toFree=NULL;
    numTokens = 0;
}

/**
 * Returns the git_version on ./mydash -v
 * startup command and proceeds to exit
 * after printing.
 *
 */
void getVersion(void){
    printf("Git_version: %s \n", git_version());
    exitShell();
}
 /*
 * exitShell will successfuly exit the
 * shell with a return status of 0.
 *
 */
void exitShell(){
    exit(EXIT_SUCCESS);
}


/* vim: set ts=4: */
