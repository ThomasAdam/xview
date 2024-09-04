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

extern char *list,*program;

/*This function will put together a list of screens to save information from.

  Inputs:  default_screen - default screen to use if no option list given
           total_screens  - total number of screens this server knows about
  Outputs: screens        - list of screen numbers to save from
  Locals:  loop           - loop through list array
           numscreens     - number of screens in list
           pointer        - loop through option list
           screens        - array of screen numbers
  Globals: list           - option list of screens to save from
           program        - name of currently executing program
           NULL           - 0
*/
int *make_list(default_screen,total_screens)
int default_screen,total_screens;
{
        int *screens,numscreens,loop;
        char *pointer;

        /*Found out how big an array we need - how many screens to save
          from*/
        if(!list) numscreens = 2;
        else if(strcmp(list,"all")) numscreens = count_spaces(list)+2;
             else numscreens = total_screens + 1;

        if((screens = (int *) calloc(numscreens,sizeof(int *))) == NULL) {
          perror(program);
          exit(1);
        }

        /*Set up array list*/
        if(!list) {
          screens[0] = default_screen;
          screens[1] = -1;
        } else if(strcmp(list,"all")) {
                 loop = 0;
                 for(pointer = list;pointer;pointer = index(pointer+1,' '))
                   sscanf(pointer,"%d",&screens[loop++]);
                 screens[loop] = -1;
               } else {
                        for(loop = 0;loop < total_screens;++loop)
                          screens[loop] = loop;
                        screens[loop] = -1;
                      }

        return(screens);
}

/*Count the number of spaces in a string.

  Inputs:  string    - string to count spaces in
  Outputs: numspaces - number of spaces in a string
  Locals:  numspaces - number of spaces in a string
           pointer   - pointer to spaces in string
  Globals: none
*/
count_spaces(string)
char *string;
{
        int numspaces = 0;
        char *pointer = string;

        while(pointer = index(pointer+1,' ')) ++numspaces;

        return(numspaces);
}

