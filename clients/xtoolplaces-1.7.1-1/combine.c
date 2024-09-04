/*Copyright (c) 1993-1998 Xerox Corporation.  All Rights Reserved.

  Permission to use, copy, modify  and  distribute  without  charge
  this  software,  documentation, images, etc. is granted, provided
  that this copyright and the author's name is retained.

  A fee may be charged for this program ONLY to recover  costs  for
  distribution  (i.e.  media costs).  No profit can be made on this
  program.

  The author assumes no responsibility for  disasters  (natural  or
  otherwise) as a consequence of use of this software.

  Adam Stein (adam@iset.scan.mc.xerox.com)
*/

#include <stdio.h>
#include "xtoolplaces.h"

extern char *program;

/*This function will combine multiple argv[] strings into a single string.
  For command lines that are in multiple argv[] strings, any argument with
  whitespace will be double quoted.  It is assumed that command lines already
  in a single string have double quoted any white space arguments they have.

  Inputs:  argc     - number of arguments
           argv     - list of arguments
  Outputs: pointer  - pointer to single string of arguments
  Locals:  loop     - loop through arguments
           numbytes - number of bytes needed for single argument string
           pointer  - pointer to single string of arguments
  Globals: NULL     - 0
*/
char *combine(argc,argv)
int argc;
char *argv[];
{
        int numbytes,loop;
        char *pointer;

        /*If argc equals 1, then all the arguments are already in a single
          string and there's no reason to do anything else but copy it*/
        if(argc != 1) {
          /*Set numbytes initially to count the spaces between arguments
            and the NULL (number of arguments - 1 + 1)*/
          numbytes = argc;

          /*Count bytes in each argument, add double quotes if argument
            has whitespace*/
          for(loop = 0;loop < argc;++loop) {
            if((index(argv[loop],' ') || index(argv[loop],'\t')) &&
               (argv[loop][0] != '"')) {
              if((pointer = malloc(strlen(argv[loop]) + 3)) == NULL) {
                perror(program);
                exit(1);
              }
              else {
                       sprintf(pointer,"\"%s\"",argv[loop]);
                       argv[loop] = pointer;
                     }
            }
            numbytes += strlen(argv[loop]);
          }

          if((pointer = malloc(numbytes)) == NULL) {
            perror(program);
            exit(1);
          }

          strcpy(pointer,argv[0]);

          for(loop = 1;loop < argc;++loop) {
            strcat(pointer," ");
            strcat(pointer,argv[loop]);
          }
        } else if((pointer = strdup(argv[0])) == NULL) {
                 perror(program);
                 exit(1);
               }

        return(pointer);
}

