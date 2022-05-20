/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lookUpTable.h"


int hash(char* key, int slotsNum){
	int i,s = 0;
	for(i=0;i<strlen(key);i++){
		s = s + (int)key[i];
	}
	return (s%slotsNum);
}


LookUpTable newLookUpTable(int slotsNum){
	
	LookUpTable lookUpTable = (LookUpTable)malloc(sizeof(struct lookUp));
	lookUpTable->slots = (List*)malloc(slotsNum*sizeof(List));
	lookUpTable->slotsNum = slotsNum;
	int i;
	for(i=0;i<slotsNum;i++){
		lookUpTable->slots[i] = (List)malloc(sizeof(struct list1));
		lookUpTable->slots[i]->head = NULL;
	}
	lookUpTablePopulate(lookUpTable);
	return lookUpTable;
}


void lookUpTablePopulate(LookUpTable lookUpTable){
	int keywordsNum = 24;
	char* keywordList[] = {
		"with",
		"parameters",
		"end",
		"while",
		"type",
		"_main",
		"global",
		"parameter",
		"list",
		"output",
		"input",
		"int",
		"real",
		"endwhile",
		"if",
		"endif",
		"then",
		"read",
		"write",
		"return",
		"call",
		"record",
		"endrecord",
		"else"
	};
	Tokentype keywordEnum[] = {
		TK_WITH,
		TK_PARAMETERS,
		TK_END,
		TK_WHILE,
		TK_TYPE,
		TK_MAIN,
		TK_GLOBAL,
		TK_PARAMETER,
		TK_LIST,
		TK_OUTPUT,
		TK_INPUT,
		TK_INT,
		TK_REAL,
		TK_ENDWHILE,
		TK_IF,
		TK_ENDIF,
		TK_THEN,
		TK_READ,
		TK_WRITE,
		TK_RETURN,
		TK_CALL,
		TK_RECORD,
		TK_ENDRECORD,
		TK_ELSE
	};
	int i;
	for(i=0;i<keywordsNum;i++){
		addEntrytoLookup(lookUpTable,keywordList[i],keywordEnum[i]);
	}
}


void addEntrytoLookup(LookUpTable lookUpTable, char* key, Tokentype tokentype){
	Node entry = (Node)malloc(sizeof(struct node7));
	entry->type = tokentype;
	entry->lexeme = (char*)malloc(sizeof(char)*(strlen(key)+1));
	strcpy(entry->lexeme,key);
	int hashed =  hash(key,lookUpTable->slotsNum);
	entry->next = lookUpTable->slots[hashed]->head;
	lookUpTable->slots[hashed]->head = entry;
}




Node getType_Token(char* key, LookUpTable lookUpTable){
	int hashvalue = hash(key, lookUpTable->slotsNum);
	Node temp = lookUpTable->slots[hashvalue]->head;
	while(temp!=NULL){
		if(strcmp(temp->lexeme,key)==0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

