/*
Group Number  --> 23
Names and IDs --> 1. Garvit Soni                2017B3A70458H
                  2. Aman Badjate               2017B3A70559H
                  3. Prakhar Suryavansh         2017B4A71017H
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "Stack.h"
#include "NaryTree.h"
#include"lexer.h"


    if (fp != NULL)
        fclose(fp);




void parseCodeandPrintErrors(char *testcaseFile, ParseTable table) 
{
    modify(testcaseFile);
    if (endoffile)
        return;
    testcaseFile = "modified_input_code.txt";
    FILE* fp = initLexer(testcaseFile);
    
}
