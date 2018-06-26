#ifndef __GETJOBID_H
#define __GETJOBID_H

/**
 * Gets the next usables JobId
 *
 * @param dlJ to search for the highest jobID
 * @return Next usable jobID
 */
int getJobID(struct list *dlJ);

#endif  /* __GETJOBID_H */
