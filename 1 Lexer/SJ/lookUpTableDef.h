/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#ifndef _LOOKUPTABLEDEF_
#define _LOOKUPTABLEDEF_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexerDef.h"

struct node7{
	char* lexeme;
	Tokentype type;
	struct node7* next;
};
typedef struct node7* Node;

struct list1{
	Node head;
};
typedef struct list1* List;

struct lookUp{
	List* slots;
	int slotsNum;
};	

typedef struct lookUp* LookUpTable;


#endif