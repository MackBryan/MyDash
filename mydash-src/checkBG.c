#include "mydash.h"
//#include "../../p0/testsuite/Object.c"

/* checkBG will iterate a doubly linked list
 * looking for finished jobs to report to the user
 * as well as returning a new list containing the
 * still running jobs.
 *
 * @param list structure to check for finished jobs
 * @return list with finished jobs marked
 */

struct list *checkBG(struct list *dlC){

    int status;
    struct node *current = dlC->head;
    struct jobl *job = current->obj;
    int isDone;

    while( current != NULL){
        if(job->done == 0){
            signal(SIGTSTP, SIG_IGN);
            signal(SIGINT, SIG_IGN);
            isDone = waitpid(job->pid, &status, WNOHANG);
            signal(SIGINT, sigintHandler);
            signal(SIGTSTP,sigstpHandler);
        }else{
            isDone = job->pid;
        }
         if(isDone == job->pid){
            if(job->done == 0){
                printf("[%d]  %d    %s %s \n", job->jobID,
                       job->pid, "Done",job->lne);
                free(job->lne);
                job->done = 1;
            }
        }
        current = current->next;

        if(current != NULL){
            job = current->obj;
        }
    }// end while

    return dlC;
}
