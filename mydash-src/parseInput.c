#include <stdio.h>
#include <stdlib.h>
#include "parseInput.h"
#include "mydash.h"
/**
 * parseInput parses input from mydash
 * into an array of tokens
 */
const int MAX_TOKENS = 2048;

char **parseInput(char *s, char *delimiter, int *numTokens)
{

    char *nextToken;
    char **token = (char **) malloc (sizeof(char *) * MAX_TOKENS);

    nextToken = strtok(s , delimiter);
    *numTokens = 0;
    while (nextToken != NULL) {
        token[*numTokens] = (char *) malloc(sizeof(char) * (strlen(nextToken)+1));
        strcpy(token[*numTokens], nextToken);
        (*numTokens)++;
        nextToken = strtok(NULL, delimiter);
    }
      // (*numTokens)++;
       // token[*numTokens] = (char *) malloc(sizeof(char));
        token[*numTokens] = '\0';
        // (*numTokens)++;
       // nextToken = NULL;
    return token;
}

