#include "changeDirectory.h"
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
/**
 * changeDir will change a user's directory
 * to a specified path or to their home directory
 * if no path is given
 */
void changeDir(char *command, char *directory){
  if(directory == NULL){

   chdir((getpwuid(getuid())->pw_dir));

   }else{
   if(chdir(directory) == -1){
    printf("%s : Is not a valid directory \n", directory);
   }
   }
}

