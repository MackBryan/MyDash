#ifndef __PARSEINPUT_H
#define __PARSEINPUT_H

/**
 * parses the line of user input in an array
 *
 * @param s User entered string
 * @param delimiter Delimiter for the tokenizer
 * @param numTokens pointer to reference number of tokens
 * @return tokenized array of user input.
 */
char **parseInput(char *s, char *delimiter, int *numTokens);

#endif  /* __PARSEINPUT_H */

