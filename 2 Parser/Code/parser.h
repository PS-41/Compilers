/*
Group Number  --> 23
Names and IDs --> 1. Garvit Soni                2017B3A70458H
                  2. Aman Badjate               2017B3A70559H
                  3. Prakhar Suryavansh         2017B4A71017H
*/

#include <stdio.h>
#include <stdlib.h>
#include "parserDef.h"
#include "NaryTreeDef.h"


Grammar StoreGrammarInStructures(char* grammar_text_file);



SymbolList initializeSymbolList();
Rule initializeRule(int* next_rule_no);
Symbolnode createSymbolnode(int enum_int, int IfTerminalOrNonTerm);
Symbolnode addSymbolnodetoSymbolList(SymbolList list, Symbolnode sym_node, Symbolnode curr_node);
void addRuletoGrammar(Grammar grm, NonTerminal non_term, Rule new_rule);
int findIndex(char* str, int IfTerminalOrNonTerm);
void displayGrammarStored(Grammar grm);



FirstAndFollow AutomatedFirstFollowFind(Grammar grm);



void printFIRSTFOLLOW(FirstAndFollow sets);
void printSet(int* set,char* toPrint);
void AutomatedFirstFind(Grammar grm, NonTerminal non_term, int** first);
int performUnion(int* set1, int* set2);
void AutomatedFollowFind(Grammar grm, FirstAndFollow sets);
int AutomatedFollowFindUtil(Grammar grm, int** first, int** follow, int hasChanged);


/****************************************************************************************************************************/

/**Parsing Table**/


void createParseTable(Grammar grm, FirstAndFollow sets, ParseTable table);




/****************************************************************************************************************************/


/**Parsing**/


ParseTree  parseCodeandPrintErrors(char *testcaseFile, ParseTable table);



void printParseTree(ParseTree tree,char* outFileName);
void printParseTree_util(TreeNode node, FILE** fp);
void printNode(FILE** fp, TreeNode node, int isLeaf);