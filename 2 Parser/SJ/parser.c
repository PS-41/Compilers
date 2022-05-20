/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "parser.h"
#include "Stack.h"
#include "NaryTree.h"
#include "lookUpTable.h"
#include"lexer.h"

//Mappings of ENUM to String
char* TerminalMap[] = {
    "TK_ASSIGNOP",
    "TK_COMMENT",
    "TK_FIELDID",
    "TK_ID",
    "TK_NUM",
    "TK_RNUM",
    "TK_FUNID",
    "TK_RECORDID",
    "TK_WITH",
    "TK_PARAMETERS",
    "TK_END",
    "TK_WHILE",
    "TK_TYPE",
    "TK_MAIN",
    "TK_GLOBAL",
    "TK_PARAMETER",
    "TK_LIST",
    "TK_SQL",
    "TK_SQR",
    "TK_INPUT",
    "TK_OUTPUT",
    "TK_INT",
    "TK_REAL",
    "TK_COMMA",
    "TK_SEM",
    "TK_COLON",
    "TK_DOT",
    "TK_ENDWHILE",
    "TK_OP",
    "TK_CL",
    "TK_IF",
    "TK_THEN",
    "TK_ENDIF",
    "TK_READ",
    "TK_WRITE",
    "TK_RETURN",
    "TK_PLUS",
    "TK_MINUS",
    "TK_MUL",
    "TK_DIV",
    "TK_CALL",
    "TK_RECORD",
    "TK_ENDRECORD",
    "TK_ELSE",
    "TK_AND",
    "TK_OR",
    "TK_NOT",
    "TK_LT",
    "TK_LE",
    "TK_EQ",
    "TK_GT",
    "TK_GE",
    "TK_NE",
    "eps",
	"$"
};

char* NonTerminalMap[] = {
    "program",
    "mainFunction",
    "otherFunctions",
    "function",
    "input_par",
    "output_par",
    "parameter_list",
    "dataType",
    "primitiveDatatype",
    "constructedDatatype",
    "remaining_list",
    "stmts",
    "typeDefinitions",
    "typeDefinition",
    "fieldDefinitions",
    "fieldDefinition",
    "moreFields",
    "declarations",
    "declaration",
    "global_or_not",
    "otherStmts",
    "stmt",
    "assignmentStmt",
    "singleOrRecId",
	"tempSoRId",
    "funCallStmt",
    "outputParameters",
    "inputParameters",
    "iterativeStmt",
    "conditionalStmt",
    "elsePart",
    "ioStmt",
    "arithmeticExpression",
	"arithExp1",
    "term",
	"arithExp2",
    "oper1",
    "oper2",
    "factor",
    "booleanExpression",
    "var",
	"allVar",
	"temp",
    "logicalOp",
    "relationalOp",
    "returnStmt",
    "optionalReturn",
    "idList",
    "more_ids"
};




//Section 1




Grammar StoreGrammarInStructures(char* inputGrammarFile){
    
	FILE* input = fopen(inputGrammarFile, "r");
	if(input==NULL){
        fprintf(stderr, "Grammar file can't be opened ------- ERROR\n");
        return NULL;
    }
	int eof = 0;
    int nextRuleNum = 1;
    
	Grammar grm = (Grammar)malloc(sizeof(Rules*));
    (*grm) = (Rules*)malloc(sizeof(Rules)*NONTERMINALS_COUNT);
    int i;
	for(i = 0; i<NONTERMINALS_COUNT;i++){
        (*grm)[i] = (Rules)malloc(sizeof(struct rules));
        (*grm)[i]->head = NULL;
        (*grm)[i]->length = 0;
    }
    
    char c;
    
    while(1){
        
        if(eof==1)
            return grm;
        c = fgetc(input);
		while(c!='<'){
            if(c==EOF){
                return grm;
            }
			c = fgetc(input);
        }
		
		char* NonTerm = (char*)malloc(sizeof(char)*40);
        int i = 0;
		c = fgetc(input);
        while(c!='>'){
            NonTerm[i] = c;
			i++;
			c = fgetc(input);
        }
        NonTerm[i] = '\0';
        
        Rule newRule = initializeRule(&nextRuleNum);
		NonTerminal NonTermIndex  =  findIndex(NonTerm,1);
		SymbolList list = initializeSymbolList();
        
        
        Symbolnode currentNode = list->head;
        
        
        while(1){
            if(eof==1)
                break;
       
	   		c = fgetc(input);
			while(c==' '|| c == '\t' || c== '=' || c== '>'){
				c = fgetc(input);
			}
            
			if(c == EOF){
                eof = 1;
                break;
            }
			else if(((c>='A')&&(c<='Z'))||(c=='e')||(c=='p')||(c=='s')||(c=='_')){
                
                char* Term = (char*)malloc(sizeof(char)*40);
                int i = 0;
                Term[i] = c;
				i = i + 1;
                c = fgetc(input);
				while(((c>='A')&&(c<='Z'))||(c=='e')||(c=='p')||(c=='s')||(c=='_')){
					Term[i++] = c;
					c = fgetc(input);
				}
				ungetc(c,input);
                Term[i] = '\0';
                
                int termNum = findIndex(Term,0);
                Symbolnode symbolNode = createSymbolnode(termNum, 0);
                
                currentNode = addSymbolnodetoSymbolList(list, symbolNode, currentNode);
                

				if(c=='\n'){
					break;
				}

				if(c==EOF){
					eof = 1;
					break;
				}

				
            }
			else if(c=='|'){
                newRule->symbols = list;
                addRuletoGrammar(grm,NonTermIndex,newRule);
                newRule = initializeRule(&nextRuleNum);                
                list = initializeSymbolList();                
                currentNode = list->head;
                continue;
            }
			else if(c=='<'){
                NonTerm = (char*)malloc(sizeof(char)*40);
                int i = 0;
				c = fgetc(input);
                while(c!='>'){
                    NonTerm[i] = c;
					i = i + 1;
					c = fgetc(input);
                }
                
                NonTerm[i] = '\0';
                
				int nonTermNum = findIndex(NonTerm,1);
                Symbolnode symbolNode = createSymbolnode(nonTermNum, 1);
                
                currentNode = addSymbolnodetoSymbolList(list, symbolNode, currentNode);
                
            }
			else if(c == '\n')
                break;
        }
        newRule->symbols = list;
        addRuletoGrammar(grm,NonTermIndex,newRule);
    }
}


SymbolList initializeSymbolList(){
    SymbolList newList = (SymbolList)malloc(sizeof(struct symbolList));
    newList->length = 0;
	newList->head = NULL;  
    return newList;
}

Rule initializeRule(int* nextRuleNum){
    Rule newRule = (Rule)malloc(sizeof(struct rule));
	newRule->symbols = NULL;
    newRule->next = NULL;
	newRule->ruleNum = *nextRuleNum;
    (*nextRuleNum)++;
    return newRule;
}

Symbolnode createSymbolnode(int IndexofEnum, int IfTerminalOrNonTerm){
    Symbolnode symbolNode = (Symbolnode)malloc(sizeof(struct SymbolNode));
    symbolNode->next=NULL;
    SymbolNodeType type;
    if(IfTerminalOrNonTerm==1){
		type.nonterm = (NonTerminal)IndexofEnum;
    }
    else{
        type.term = (Tokentype)IndexofEnum;
    }
	symbolNode->IfTerminalOrNonTerm = IfTerminalOrNonTerm;
    symbolNode->type = type;
    return symbolNode;
}

int findIndex(char* str, int IfTerminalOrNonTerm){
	int retValue = 0;
    if(IfTerminalOrNonTerm==1){
		for(int i=0;i<NONTERMINALS_COUNT;i++){
            if(strcmp(str,NonTerminalMap[i])==0){
				retValue = i;
				break;
			}
        }
    }
    else{
        for(int i=0;i<total_token_types;i++){
            if(strcmp(str,TerminalMap[i])==0){
				retValue = i;
				break;
			}
        }
    }
    return retValue;
}


Symbolnode addSymbolnodetoSymbolList(SymbolList list, Symbolnode symbolNode, Symbolnode currentNode){
    if(currentNode!=NULL){
		currentNode->next = symbolNode;
        currentNode = currentNode->next;
    }
    else{
        symbolNode->next = list->head;
        list->head = symbolNode;
        currentNode = list->head;
    }
    list->length = list->length + 1;
    return currentNode;
}

void addRuletoGrammar(Grammar grm, NonTerminal NonTermIndex, Rule newRule){
	(*grm)[NonTermIndex]->length = (*grm)[NonTermIndex]->length + 1;
    newRule->next = (*grm)[NonTermIndex]->head;
    (*grm)[NonTermIndex]->head = newRule;
}

void displayGrammarStored(Grammar grm){
    printf("\n\t\t\t Grammar Stored\n\n\n");
    
    for(int i=0;i<NONTERMINALS_COUNT;i++){
        printf("%d)  <%s> ===> ",(i+1), NonTerminalMap[i]);
        
        Rules rules = (*grm)[i];
        Rule temp = rules->head;
        
        for(int j = 0;j< rules->length;j++){
            if(j!=0)
                printf("| ");
            
            SymbolList symbols = temp->symbols;
            Symbolnode temp1 = symbols->head;
            
            for(int k=0;k<symbols->length;k++){
                if(temp1->IfTerminalOrNonTerm==1)
					printf("<%s>", NonTerminalMap[temp1->type.nonterm]);
                else
                    printf("%s", TerminalMap[temp1->type.term]);
                
                printf(" ");
                temp1 = temp1->next;
            }
            
            
            temp = temp->next;
        }
        printf("\n");
    }
}


//SECTION 2



FirstAndFollow AutomatedFirstFollowFind(Grammar grm){

	FirstAndFollow sets = (FirstAndFollow)malloc(sizeof(struct firstAndFollow));
	sets->first = (int**)malloc(NONTERMINALS_COUNT*sizeof(int*));
	sets->follow = (int**)malloc(NONTERMINALS_COUNT*sizeof(int*));
	for(int i=0;i<NONTERMINALS_COUNT;i++){
		sets->first[i] = (int*)malloc(FIRSTFOLLOWCOLUMNS*sizeof(int));
		sets->follow[i] = (int*)malloc(FIRSTFOLLOWCOLUMNS*sizeof(int));
		int j;
		for(j=0;j<FIRSTFOLLOWCOLUMNS;j++){
			sets->first[i][j] = 0;
			sets->follow[i][j] = 0;	
		}				
	}
	for(int i=0;i<NONTERMINALS_COUNT;i++){
		AutomatedFirstFind(grm,(NonTerminal)i, sets->first);		
	}
	AutomatedFollowFind(grm,sets);
	return sets;
}

void printFIRSTFOLLOW(FirstAndFollow sets){
	for(int i=0;i<NONTERMINALS_COUNT;i++){
		printf("\n\n%d. %s => ",(i+1),NonTerminalMap[i]);
		printSet(sets->first[i],"FIRST");
		printSet(sets->follow[i],"FOLLOW");
	}	
}

void printSet(int* set,char* toPrint){
	printf("\n\t%s = { ",toPrint);
	for(int i=0;i<FIRSTFOLLOWCOLUMNS;i++){
		if(set[i]==1){
			printf("%s ",TerminalMap[i]);
		}
	}
	printf("}");
}


void AutomatedFirstFind(Grammar grm, NonTerminal NonTermIndex, int** first){
	Rules rules = (*grm)[NonTermIndex];
	Rule temp = rules->head;
	int j,k;
	for(j = 0;j< rules->length;j++){
		SymbolList symbols = temp->symbols;
		Symbolnode temp1 = symbols->head;
		for(k=0;k<symbols->length;k++){
			if(temp1->IfTerminalOrNonTerm==1){
				AutomatedFirstFind(grm, temp1->type.nonterm,first);
				performUnion(first[NonTermIndex], first[temp1->type.nonterm]);
				if(!(first[temp1->type.nonterm][EPSILON]==1)){
					break;
				}
			}
			else{
				first[NonTermIndex][temp1->type.term] = 1;				
				break;
			}			
			temp1 = temp1->next;
		}
		if(k==symbols->length){			
			first[NonTermIndex][EPSILON] = 1;
		}
		temp = temp->next;
	}
}


int performUnion(int* set1, int* set2){
	int i,hasChanged = 0;
	for(i=0;i<TERMINALS_COUNT;i++){
		if((i!=EPSILON)&&(set2[i]==1)&&(set1[i]==0)){
				hasChanged = 1;
				set1[i] = 1;
		}
	}
	return hasChanged;
}

void AutomatedFollowFind(Grammar grm, FirstAndFollow sets){
	sets->follow[program][DOLLAR] = 1;
	sets->follow[mainFunction][DOLLAR] = 1;
	int hasChanged;
	do{
		hasChanged = AutomatedFollowFindUtil(grm,sets->first,sets->follow,0);
	}while(hasChanged==1);
}

int AutomatedFollowFindUtil(Grammar grm, int** first, int** follow, int hasChanged){
	int i,j,k;
	for(i=0;i<NONTERMINALS_COUNT;i++){
		Rules rules = (*grm)[i];
		Rule temp = rules->head;
		for(j = 0;j< rules->length;j++){
			SymbolList symbols = temp->symbols;
			Symbolnode temp1 = symbols->head;
			for(k=0;k<symbols->length;k++){
				if(temp1->IfTerminalOrNonTerm==1){
					Symbolnode temp2 = temp1->next;
					while(temp2!=NULL){
						if(temp2->IfTerminalOrNonTerm==1){
							int k1 = performUnion(follow[temp1->type.nonterm],first[temp2->type.nonterm]);
							hasChanged = (hasChanged>k1) ? hasChanged : k1;
							if(!(first[temp2->type.nonterm][EPSILON]==1))
								break;
						}
						else{
							if(!(follow[temp1->type.nonterm][temp2->type.term]==1))
								hasChanged = 1;
							follow[temp1->type.nonterm][temp2->type.term] = 1;
							break;
						}
						temp2 = temp2->next;						
					}
					if(temp2 == NULL){
						int k2 = performUnion(follow[temp1->type.nonterm],follow[i]);
						hasChanged = (hasChanged>k2) ? hasChanged : k2;
					}
				}								
				temp1 = temp1->next;
			}
			temp = temp->next;
		}		
	}
	return hasChanged;
}


//Section 3


void createParseTable(Grammar grm, FirstAndFollow sets, ParseTable table){
	int i,j,k,x,ContinueOrNot;
	for(i=0;i<NONTERMINALS_COUNT;i++){
		for(j=0;j<TERMINALS_COUNT;j++){
			table->SlotTable[i][j] = NULL;
		}
	}
	for(i=0;i<NONTERMINALS_COUNT;i++){
		Rules rules = (*grm)[i];
		Rule temp = rules->head;
		for(j=0;j<rules->length;j++){
			ContinueOrNot = 0;
			SymbolList symbols = temp->symbols;
			Symbolnode temp1 = symbols->head;
			for(k=0;k<symbols->length;k++){
				ContinueOrNot = 0;
				if(temp1->IfTerminalOrNonTerm==0){
					if(temp1->type.term!=EPSILON){
						table->SlotTable[i][temp1->type.term] = temp;
						break;
					}
					else{
						for(int x=0;x<TERMINALS_COUNT;x++){
							if(sets->follow[i][x]==1){	
								table->SlotTable[i][x] = temp;
							}
						}
						continue;
					}
				}
				else{
					for(x=0;x<TERMINALS_COUNT;x++){
						if(sets->first[temp1->type.nonterm][x]==1){
							if(x!=EPSILON){
								table->SlotTable[i][x] = temp;
							}
							else{
								ContinueOrNot = 1;
							}
						}
					}
				}

				if(ContinueOrNot==0)
					break;
				else
				{
					temp1 = temp1->next;
					continue;
				}							
			}
			temp = temp->next;
		}
	}
}






//Section 4

ParseTree  parseCodeandPrintErrors(char *testcaseFile, ParseTable table){
	FILE* fp = initLexer(testcaseFile);
	if(fp == NULL){
		printf("Test Case File opening error\n");
		return NULL;
	}
	Stack stk = initStack();
	TreeNode dollar_node =  createTreeNode(0,	DOLLAR, NULL);
	push(stk,dollar_node);
	ParseTree tree = (ParseTree)malloc(sizeof(struct parseTree));
	tree->root = createTreeNode(1,program,NULL);
	push(stk,tree->root);
	
	Token nextToken = getToken(&fp);
	if(nextToken==NULL){
		printf("\n\nTest Case File has nothing in it\n\n");
		return NULL;			
	}
	int error = 0;
	


	while(1){

		if(nextToken==NULL){
			if(top_isDollar(stk) && error!=1){
				printf("\n\n\tSyntactically Correct Source Code\n\n\n");
			}
			else{
				printf("\n\n\tSyntactically Wrong Source Code\n\n\n");
			}
			break;
		}
		if(nextToken->type==ERROR){
			nextToken= getToken(&fp);
			continue;
		}
		if(top_isDollar(stk)){
			printf("\n\n\tSyntactically Wrong Source Code ---> There may be extra tokens in the end\n\n\n");
			break;
		}

		Node_Stack stkNode = pop(stk);
		TreeNode treeNode = stkNode->Ptr_Tree;

		if(treeNode->info->IfTerminalOrNonTerm==1){
			Rule nextRule = table->SlotTable[treeNode->info->type.nonterm][nextToken->type];
			//Error Recovery
			if(nextRule == NULL){
				error = 1;
				printf("Line No: %d, Syntax error: The token %s for lexeme %s does not match <%s>\n", nextToken->lineNum,TerminalMap[nextToken->type],nextToken->lexeme, NonTerminalMap[stkNode->Ptr_Tree->info->type.nonterm]);
				Node_Stack stkNode1 = top(stk);
				TreeNode treeNode1 = stkNode1->Ptr_Tree;
				while(nextToken!=NULL){
					Rule to_be_applied_rule1 = table->SlotTable[treeNode->info->type.nonterm][nextToken->type];
					if(to_be_applied_rule1!=NULL){
						push(stk, treeNode);
						break;
					}
					if(treeNode1->info->IfTerminalOrNonTerm==0){
						if(nextToken->type != treeNode1->info->type.term){
							Rule to_be_applied_rule2 = table->SlotTable[treeNode1->info->type.nonterm][nextToken->type];
							if(to_be_applied_rule2!=NULL)
								break;
						}
						else
							break;
					}
					nextToken = getToken(&fp);
				}
				
			}
			else{				
				addChildrentoTree(treeNode, nextRule);
				pushSubtreeStack(stk,treeNode);
			}
		}			
		else{
			if(nextToken->type == treeNode->info->type.term){
				treeNode->lexicalTOKEN = nextToken;
				nextToken = getToken(&fp);
				continue;			
			}
			//Error Recovery
			else{				
				error = 1;
				printf("Line No. %d, Syntax error: The token %s for lexeme %s does not match %s\n", nextToken->lineNum,TerminalMap[nextToken->type],nextToken->lexeme, TerminalMap[stkNode->Ptr_Tree->info->type.term]);
				Node_Stack stkNode1 = top(stk);
				TreeNode treeNode1 = stkNode1->Ptr_Tree;
				while(nextToken!=NULL){
					if(nextToken->type == treeNode->info->type.term){
						push(stk, treeNode);
						break;
					}
					if(treeNode1->info->IfTerminalOrNonTerm==1){
						Rule to_be_applied_rule2 = table->SlotTable[treeNode1->info->type.nonterm][nextToken->type];
						if(to_be_applied_rule2!=NULL){
							break;
						}
					}
					else{
						if(nextToken->type == treeNode1->info->type.term){
							break;
						}
					}

					nextToken = getToken(&fp);
				}
		
				continue;			

			}
		}
	}
	return tree;

}


void printParseTree(ParseTree tree,char* outFileName){
	FILE* fp1 = fopen(outFileName,"w+");	
	fprintf(fp1,"%-25s %-12s %-15s %-15s %-25s %-8s %s\n\n\n", "LexemeCurrentNode","LineNumber","TokenName","ValueIfNo","ParentNodeSymbol","isLeaf","NodeSymbol");
	printParseTree_util(tree->root,&fp1);
}


void printParseTree_util(TreeNode node, FILE** fp1){
	if(node==NULL){
		return;
	}
	Children children = node->children;
	if(children== NULL)
		printNode(fp1,node, 1);
	else{
		TreeNode temp = children->head;	
		printParseTree_util(temp,fp1);
		printNode(fp1,node, 0);
		temp = temp->next;
		
		while(temp!=NULL){
			printParseTree_util(temp, fp1);
			temp = temp->next;
		}	
	}
}

void printNode(FILE** fp, TreeNode node, int Leaf){
	if(!Leaf){
		if(node->parent == NULL)
			fprintf(*fp,"%-25s %-12s %-15s %-15s %-25s %-8s <%s>\n", "----","----","----","----","ROOT","no",NonTerminalMap[node->info->type.nonterm]);
		else
			fprintf(*fp,"%-25s %-12s %-15s %-15s %-25s %-8s <%s>\n", "----","----","----","----",NonTerminalMap[node->parent->info->type.nonterm],"no",NonTerminalMap[node->info->type.nonterm]);	
	}
	else{
		if(node->info->type.term==EPSILON)
			fprintf(*fp,"%-25s %-12s %-15s %-15s %-25s %-8s %s\n", "----","----","----","----",NonTerminalMap[node->parent->info->type.nonterm],"yes","----");
		else if(node->lexicalTOKEN==NULL)
			fprintf(*fp,"%-25s %-12s %-15s %-15s %-25s %-8s %s\n", "Error", "Error", "Error", "----", NonTerminalMap[node->parent->info->type.nonterm], "yes", "----");
		else if(node->lexicalTOKEN->valType== -1)
			fprintf(*fp,"%-25s %-12d %-15s %-15s %-25s %-8s %s\n", node->lexicalTOKEN->lexeme, node->lexicalTOKEN->lineNum, TerminalMap[node->lexicalTOKEN->type], "----", NonTerminalMap[node->parent->info->type.nonterm], "yes", "----");
		else if(node->lexicalTOKEN->valType== 0)
			fprintf(*fp,"%-25s %-12d %-15s %-15d %-25s %-8s %s\n", node->lexicalTOKEN->lexeme, node->lexicalTOKEN->lineNum, TerminalMap[node->lexicalTOKEN->type], node->lexicalTOKEN->value->num, NonTerminalMap[node->parent->info->type.nonterm], "yes", "----");
		else if(node->lexicalTOKEN->valType== 1)
			fprintf(*fp,"%-25s %-12d %-15s %-15f %-25s %-8s %s\n", node->lexicalTOKEN->lexeme, node->lexicalTOKEN->lineNum, TerminalMap[node->lexicalTOKEN->type], node->lexicalTOKEN->value->realNum, NonTerminalMap[node->parent->info->type.nonterm], "yes", "----");
	}
}

