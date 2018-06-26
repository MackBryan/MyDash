#ifndef	__MYDASH_H
#define	__MYDASH_H

#include	<sys/types.h>	/* required for some of our prototypes */
#include	<stdio.h>		/* for convenience */
#include	<stdlib.h>
#include	<sysexits.h>
#include	<string.h>
#include	<unistd.h>
#include    <sys/wait.h>
#include    <signal.h>
#include    "../../p0/include/List.h"
#include    "../../p0/include/Node.h"
//#include    "../../p0/testsuite/Object.c"

#define	MAXLINE	4096			/* max line length */

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */


/* prototypes for our own functions */
struct jobl{
    int jobID;
    pid_t pid;
    char *cmnd;
    char *lne;
    int done;
};
/**
 * sigintHandler will catch SIGINT signals
 * and interupt a foreground process otherwise it
 * will print a debug statement when no foreground
 * processes are present.
 *
 * @param signo Signal number received
 */
void    sigintHandler(int signo);

/**
 * sigstpHandler will catch SIGTSTP signals
 * and stop and print the corresponging foreground
 * process otherwise it will print a debug statemewhen
 * when no foreground process is running
 *
 * @param signo Signal number received
 */
void    sigstpHandler(int signo);

void	err_dump(const char *, ...);	/* {App misc_source} */
void	err_msg(const char *, ...);
void	err_quit(const char *, ...);
void	err_ret(const char *, ...);
void	err_sys(const char *, ...);


#endif	/* __MYDASH_H */
