/*
Group Number  --> 23
Names and IDs --> 1. Garvit Soni                2017B3A70458H
                  2. Aman Badjate               2017B3A70559H
                  3. Prakhar Suryavansh         2017B4A71017H
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
