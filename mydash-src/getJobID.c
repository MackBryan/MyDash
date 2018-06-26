#include "mydash.h"

/*
 * getJobID returns the next usable
 * jobID based on the jobID's being used
 * in the DLL by checking for the highest
 * if any jobID.
 */
int getJobID(struct list *dlJ){

    int retID = 0;//retID will always start at 0
    //if finds anything larger it will replace otherwise
    //it will default to 1.

    struct node *currNode;
    struct jobl *currJob;

    if((isEmpty(dlJ)) > 0){

        retID  = 1;

    }else{

        currNode= dlJ->head;

        while(currNode != NULL){

            //set Node obj to currJob to dereference
            //job data
            currJob = currNode->obj;

            if((currJob->jobID > retID) ==1){

                retID = currJob->jobID;

            }
            currNode = currNode->next;
        }
        retID++;
    }
    return retID;
}
