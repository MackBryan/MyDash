#ifndef __CHECKBG_H
#define __CHECKBG_H

/**
 * Checks for background jobs that have finished
 * and marks them for removal
 *
 * @param dlC List of jobs to be searched
 * @return List of marked jobs for removal
 */
struct list *checkBG(struct list *dlC);

#endif  /* __CHECKBG_H */
