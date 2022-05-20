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

#define total_token_types 37

typedef enum
{
    TK_SQL_DELIMITER,
    TK_SQR_DELIMITER,
    TK_COMMA_DELIMITER,
    TK_SEM_DELIMITER,
    TK_OP_DELIMITER,
    TK_CL_DELIMITER,
    TK_FLOWERL_DELIMITER,
    TK_FLOWERR_DELIMITER,
    TK_PLUS_OPERATOR,
    TK_MINUS_OPERATOR,
    TK_MUL_OPERATOR,
    TK_DIV_OPERATOR,
    TK_MOD_OPERATOR,
    TK_BITWISE_AND_OPERATOR,
    TK_BITWISE_OR_OPERATOR,
    TK_BITWISE_XOR_OPERATOR,
    TK_LT_OPERATOR,
    TK_LE_OPERATOR,
    TK_EQ_OPERATOR,
    TK_GT_OPERATOR,
    TK_GE_OPERATOR,
    TK_NE_OPERATOR,
    TK_ASSIGN_OPERATOR,
    TK_INTEGER_LITERAL,
    TK_FLOATING_POINT_LITERAL,
    TK_IDENTIFIER,
    TK_FUNCTION_IDENTIFIER,
    TK_STRING_LITERAL,
    TK_INT_KEYWORD,
    TK_REAL_KEYWORD,
    TK_BOOL_KEYWORD,
    TK_STRING_KEYWORD,
    TK_LOOP_KEYWORD,
    TK_IF_KEYWORD,
    TK_ELSE_KEYWORD,
    TK_GAP_KEYWORD,
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

struct key_
{
    char *word;
    Tokentype type;
};

typedef struct key_ Keywords;

#endif