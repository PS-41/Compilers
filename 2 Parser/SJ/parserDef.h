/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/


#ifndef _PARSERDEF_
#define _PARSERDEF_

#include <stdio.h>
#include <stdlib.h>
#include "lexerDef.h"

#define NONTERMINALS_COUNT 49

#define TERMINALS_COUNT 54 //53+1



#define FIRSTFOLLOWCOLUMNS (TERMINALS_COUNT+1)

typedef Tokentype Terminal;


typedef enum{
    program,
	mainFunction,
	otherFunctions,
	function,
	input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    tempSoRId,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    arithExp1,
    term,
    arithExp2,
    oper1,
    oper2,
    factor,
    booleanExpression,
    var,
    allVar, 
    temp,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids
}NonTerminal;




typedef struct{
	Terminal term;
	NonTerminal nonterm;
}SymbolNodeType;


struct SymbolNode{
	SymbolNodeType type; //Terminal or non terminal
	int IfTerminalOrNonTerm; //0 - Terminal 1 - Non Terminal
	struct SymbolNode* next; 
};
typedef struct SymbolNode* Symbolnode;


struct symbolList{
	Symbolnode head;
	int length; 
};
typedef struct symbolList* SymbolList;


struct rule{
	SymbolList symbols; 
	struct rule* next; 
	int ruleNum;
};
typedef struct rule* Rule;


struct rules{
	Rule head; 
	int length; 
};

typedef struct rules* Rules;

typedef Rules** Grammar;


//1 OR 0
struct firstAndFollow{
	int** first;
	int** follow;
}; 
typedef struct firstAndFollow* FirstAndFollow;


struct parseTable{
	Rule  SlotTable[NONTERMINALS_COUNT][TERMINALS_COUNT];
};
typedef struct parseTable* ParseTable;

#endif
