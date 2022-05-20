/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lookUpTableDef.h"


int hash(char* key, int slotsNum);
LookUpTable newLookUpTable(int slotsNum);
void lookUpTablePopulate(LookUpTable lookUpTable);
void addEntrytoLookup(LookUpTable lookUpTable, char* key, Tokentype tokentype);
Node getType_Token(char* key, LookUpTable lookUpTable);