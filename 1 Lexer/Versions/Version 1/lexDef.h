/*
Group Number  --> 23
Names and IDs --> 1. Garvit	Soni			    2017B3A70458H
				  2. Aman Badjate   		    2017B3A70559H
				  3. Prakhar Suryavansh         2017B4A71017H
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _LEXERDEF_
#define _LEXERDEF_

#define total_token_types 55

typedef enum
{
    TK_SQL,
    TK_SQR,
    TK_COMMA,
    TK_SEM,
    TK_OP,
    TK_CL,
    TK_FLOWERL,
    TK_FLOWERR,
    TK_PLUS,
    TK_MINUS,
    TK_MUL,
    TK_DIV,
    TK_MOD,
    TK_AND,
    TK_OR,
    TK_XOR,
    TK_LT,
    TK_LE,
    TK_EQ,
    TK_GT,
    TK_GE,
    TK_NE,
    TK_ASSIGNOP,
    TK_NUM,
    TK_RNUM,
    TK_ID,
    TK_FUNID,
    TK_STRING,
    TK_KEY,
    ERROR
} Tokentype;

typedef union
{
    int num;
    float realNum;
} Value;

struct token
{
    Tokentype type;
    char *lexeme; //Actual Lexeme
    int valType;  //Valuetype: 0 for int, 1 for real, -1 for other, -2 for ERROR
    int lineNum;  //Line number of the token
    Value *value; //For integers and real numbers
};

typedef struct token Token1;
typedef Token1 *Token;

#endif
