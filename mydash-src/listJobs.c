 #include "mydash.h"
/*
 *  listJobs returns the current jobs in the minishell
 *  It contains running and done jobs. Done jobs are
 *  removed from the list and will not be shown next
 *  time jobs is called.
 *
 */
struct list *listJobs(struct list *lst){

        int status;
        int checkDone;
        struct node *current;
        struct jobl *tmpJob;
        current = lst->head;
        tmpJob = current->obj;
        while(current != NULL){
            signal(SIGTSTP,SIG_IGN);
            signal(SIGINT, SIG_IGN);
            checkDone = waitpid(tmpJob->pid,&status, WNOHANG);
            if(checkDone == tmpJob->pid){//if job is done

                //print job status as Done
                printf("[%d]  %d    %s %s \n", tmpJob->jobID,
                tmpJob->pid, "Done", tmpJob->lne);
                tmpJob->done = 1;

            }else{

                //print job status as Running
                printf("[%d]  %d    %s %s \n", tmpJob->jobID,
                tmpJob->pid, "Running", tmpJob->lne);
            }
                current = current->next;
                if(current != NULL){
                    tmpJob = current->obj;
                }
    }// end while

            signal(SIGTSTP,sigstpHandler);
            signal(SIGINT, sigintHandler);
   return lst;

}
