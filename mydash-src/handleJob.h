#ifndef __HANDLEJOB_H
#define __HANDLEJOB_H

/**
 * Handles backgroud jobs specified by the user.
 *
 * @param command entered
 * @param token tokenized array of user input
 * @param jobID valid jobID for current job
 * @param line Copy of the user input string
 * @return initialized job object with the given params
 */
 struct jobl *handleJob(char *command, char **token,int jobID, char *line);

#endif  /* __HANDLEJOB_H */

