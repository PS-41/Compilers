/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#ifndef _NARYTREEDEF_
#define _NARYTREEDEF_

#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h" 
#include "ASTDef.h"

struct node;
typedef struct node* ASTNode;


struct treeNodeInfo{
	int IfTerminalOrNonTerm;
	SymbolNodeType type;
};
typedef struct treeNodeInfo* TreeNodeInfo;


struct linkedlist{
	struct treeNode* head;
	int SiblingsNum;
};
typedef struct linkedlist* Children;



struct treeNode{
	struct treeNode* next; 

	TreeNodeInfo info;
	Token lexicalTOKEN; 

	Children children;	

	struct treeNode* parent;

	//AST
	ASTNode address; 
	ASTNode inhaddress;
	int ruleNum;
};
typedef struct treeNode* TreeNode;


struct parseTree{
	TreeNode root;		
};
typedef struct parseTree* ParseTree;

#endif