/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "NaryTree.h"

TreeNode createTreeNode(int IfTerminalOrNonTerm,	int enum_int, TreeNode parent){
	TreeNode node = (TreeNode)malloc(sizeof(struct treeNode));
	node->info = (TreeNodeInfo)malloc(sizeof(struct treeNodeInfo));
	node->info->IfTerminalOrNonTerm = IfTerminalOrNonTerm;
	node->lexicalTOKEN = NULL;
	node->children = NULL;
	node->next = NULL;
	SymbolNodeType type;
	
	if(IfTerminalOrNonTerm!=0)
		type.nonterm = (NonTerminal)enum_int;
	else
		type.term = (Tokentype)enum_int;

	node->parent = parent;
	node->info->type = type;



	return node;
}


Children initChildren(){
	Children children = (Children)malloc(sizeof(struct linkedlist));
	children->head = NULL;
	children->SiblingsNum = 0;
	return children;
}


void addChildrentoTree(TreeNode node, Rule rule){
	node->ruleNum = rule->ruleNum;
	SymbolList symbols = rule->symbols;
	Symbolnode temp2 = symbols->head;
	Children children = initChildren();
	TreeNode temp = children->head;

	for(int k=0;k<symbols->length;k++){
		
		TreeNode newNode;

		if(temp2->IfTerminalOrNonTerm != 0){
			newNode = createTreeNode(temp2->IfTerminalOrNonTerm, temp2->type.nonterm, node);
		}
		else{
			newNode = createTreeNode(temp2->IfTerminalOrNonTerm, temp2->type.term, node);
		}
		
		if(temp!=NULL){
			temp->next = newNode;
			temp = temp->next;
		}
		else{
			temp = newNode;
			children->head = temp;
		}		
		temp2 = temp2->next;
		children->SiblingsNum = children->SiblingsNum + 1;
	}

	node->children = children;

}








