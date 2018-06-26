#ifndef __LISTJOBS_H
#define __LISTJOBS_H

/*
 * Lists all running and un-notified finished jobs
 * in the givn list.
 *
 * @param lst Job list to be printed
 * @return List with finished jobs marked to be removed.
 */
struct list *listJobs(struct list *lst);

#endif  /* __LISTJOBS_H */
