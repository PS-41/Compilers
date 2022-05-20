/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include <stdio.h>
#include <stdlib.h>

#ifndef _LEXERDEF_
#define _LEXERDEF_

#define total_token_types 55

typedef enum
{
	TK_ASSIGNOP,
	TK_COMMENT,
	TK_FIELDID,
	TK_ID,
	TK_NUM,
	TK_RNUM,
	TK_FUNID,
	TK_RECORDID,
	TK_WITH,
	TK_PARAMETERS,
	TK_END,
	TK_WHILE,
	TK_TYPE,
	TK_MAIN,
	TK_GLOBAL,
	TK_PARAMETER,
	TK_LIST,
	TK_SQL,
	TK_SQR,
	TK_INPUT,
	TK_OUTPUT,
	TK_INT,
	TK_REAL,
	TK_COMMA,
	TK_SEM,
	TK_COLON,
	TK_DOT,
	TK_ENDWHILE,
	TK_OP,
	TK_CL,
	TK_IF,
	TK_THEN,
	TK_ENDIF,
	TK_READ,
	TK_WRITE,
	TK_RETURN,
	TK_PLUS,
	TK_MINUS,
	TK_MUL,
	TK_DIV,
	TK_CALL,
	TK_RECORD,
	TK_ENDRECORD,
	TK_ELSE,
	TK_AND,
	TK_OR,
	TK_NOT,
	TK_LT,
	TK_LE,
	TK_EQ,
	TK_GT,
	TK_GE,
	TK_NE,
	EPSILON,
	DOLLAR,
	ERROR,
	BOOLEAN
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
