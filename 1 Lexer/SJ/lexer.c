/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include "lexer.h"
#include "lookUpTable.h"
#include <ctype.h>

char *tokenStrings[] = {"TK_ASSIGNOP",
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
						"$",
						"ERROR",
						"BOOLEAN"};

#define SIZEOFBUFFER 3000

int SLOTS = 6;

char *currBuffer;
char *nextBuffer;

int lineNoGlob = 1;

int fLexerPtr = 0;

LookUpTable lookUpTable;

int endoffile = 0;

FILE *loadBuffer(FILE *fp)
{
	if (feof(fp))
	{
		fclose(fp);
		return NULL;
	}
	char *temp = nextBuffer;
	nextBuffer = currBuffer;
	currBuffer = temp;
	int i;
	for (i = 0; i < sizeof(currBuffer); i++)
		currBuffer[i] = '\0';
	int count = fread(currBuffer, sizeof(char), SIZEOFBUFFER, fp);
	if (count <= 0)
	{
		fclose(fp);
		return NULL;
	}
	else
	{
		currBuffer[SIZEOFBUFFER] = '\0';
		return fp;
	}
}

Token getToken(FILE **fp)
{
	if (endoffile == 1)
	{
		if (*fp != NULL)
			fclose(*fp);
		return NULL;
	}
	Token token = (Token)malloc(sizeof(Token1));
	if (currBuffer[fLexerPtr] == '\0')
	{
		fLexerPtr = 0;
		*fp = loadBuffer(*fp);
		if (*fp == NULL)
		{
			endoffile = 1;
			return NULL;
		}
	}
	int state = 0;
	int ifFinalReached = 0;
	char *lexeme = (char *)malloc(100 * sizeof(char));
	int curLexemeIndex = 0;

	while (1)
	{
		switch (state)
		{

		case 0:
			if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					endoffile = 1;
					return NULL;
				}

				state = 0;
			}
			else if (currBuffer[fLexerPtr] == ' ' || currBuffer[fLexerPtr] == '\t' || currBuffer[fLexerPtr] == '\r' || currBuffer[fLexerPtr] == (char)13)
			{
				state = 0;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\n')
			{
				state = 1;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '[')
			{
				state = 2;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == ']')
			{
				state = 3;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == ',')
			{
				state = 4;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == ';')
			{
				state = 5;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == ':')
			{
				state = 6;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '.')
			{
				state = 7;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '(')
			{
				state = 8;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == ')')
			{
				state = 9;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '+')
			{
				state = 10;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '-')
			{
				state = 11;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '*')
			{
				state = 12;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '/')
			{
				state = 13;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '~')
			{
				state = 14;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '<')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 15;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '!')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 21;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '=')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 23;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '>')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 25;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '&')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 28;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '@')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 31;
				fLexerPtr++;
			}
			else if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 34;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '#')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 39;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '_')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 42;
				fLexerPtr++;
			}
			else if ((currBuffer[fLexerPtr] == 'a') || ((currBuffer[fLexerPtr] >= 'e') && (currBuffer[fLexerPtr] <= 'z')))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 46;
				fLexerPtr++;
			}
			else if ((currBuffer[fLexerPtr] >= 'b') && (currBuffer[fLexerPtr] <= 'd'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 48;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '%')
			{
				state = 53;
				fLexerPtr++;
			}
			else
			{
				lexeme[curLexemeIndex++] = currBuffer[fLexerPtr];
				fLexerPtr++;
				curLexemeIndex++;
				state = 52;
			}
			break;
		case 1:
		{
			lineNoGlob++;
			state = 0;
		}
		break;
		case 2:
		{
			strcpy(lexeme, "[");
			createToken(token, TK_SQL, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;

		case 3:
		{
			strcpy(lexeme, "]");
			createToken(token, TK_SQR, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 4:
		{
			strcpy(lexeme, ",");
			createToken(token, TK_COMMA, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 5:
		{
			strcpy(lexeme, ";");
			createToken(token, TK_SEM, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 6:
		{
			strcpy(lexeme, ":");
			createToken(token, TK_COLON, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 7:
		{
			strcpy(lexeme, ".");
			createToken(token, TK_DOT, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 8:
		{
			strcpy(lexeme, "(");
			createToken(token, TK_OP, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 9:
		{
			strcpy(lexeme, ")");
			createToken(token, TK_CL, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 10:
		{
			strcpy(lexeme, "+");
			createToken(token, TK_PLUS, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 11:
		{
			strcpy(lexeme, "-");
			createToken(token, TK_MINUS, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 12:
		{
			strcpy(lexeme, "*");
			createToken(token, TK_MUL, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 13:
		{
			strcpy(lexeme, "/");
			createToken(token, TK_DIV, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 14:
		{
			strcpy(lexeme, "~");
			createToken(token, TK_NOT, lexeme, -1, NULL);
			ifFinalReached = 1;
		}
		break;
		case 15:
			if (currBuffer[fLexerPtr] == '=')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 16;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '-')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 17;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 18;
				}
				else
				{
					state = 15;
				}
			}
			else
			{
				state = 18;
				fLexerPtr++;
			}
			break;
		case 16:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_LE, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 17:
			if (currBuffer[fLexerPtr] == '-')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 19;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 17;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 18:
			strcpy(lexeme, "<");
			createToken(token, TK_LT, lexeme, -1, NULL);
			//retract
			fLexerPtr--;
			ifFinalReached = 1;
			break;
		case 19:
			if (currBuffer[fLexerPtr] == '-')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 20;
				fLexerPtr++;
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 20:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_ASSIGNOP, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 21:
			if (currBuffer[fLexerPtr] == '=')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 22;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 21;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 22:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_NE, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 23:
			if (currBuffer[fLexerPtr] == '=')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 24;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}

				else
				{
					state = 23;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 24:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_EQ, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 25:
			if (currBuffer[fLexerPtr] == '=')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 26;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 27;
				}
				else
				{
					state = 25;
				}
			}
			else
			{
				state = 27;
				fLexerPtr++;
			}
			break;
		case 26:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_LE, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 27:
			strcpy(lexeme, ">");
			createToken(token, TK_GT, lexeme, -1, NULL);

			//retract
			fLexerPtr--;
			ifFinalReached = 1;
			break;
		case 28:
			if (currBuffer[fLexerPtr] == '&')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 29;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 28;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 29:
			if (currBuffer[fLexerPtr] == '&')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 30;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 29;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 30:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_AND, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 31:
			if (currBuffer[fLexerPtr] == '@')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 32;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 31;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 32:
			if (currBuffer[fLexerPtr] == '@')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 33;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 32;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 33:
			lexeme[curLexemeIndex] = '\0';
			createToken(token, TK_OR, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 34:
			if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 34;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '.')
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 36;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					state = 35;
					fLexerPtr++;
					endoffile = 1;
				}

				else
				{
					state = 34;
				}
			}
			else
			{
				state = 35;
				fLexerPtr++;
			}

			break;
		case 35:
			lexeme[curLexemeIndex] = '\0';
			int value = atoi(lexeme);
			token->value = (Value *)malloc(sizeof(Value));
			token->value->num = value;

			createToken(token, TK_NUM, lexeme, 0, token->value);

			//retract
			fLexerPtr--;
			ifFinalReached = 1;
			break;
		case 36:
			if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 37;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					lexeme[curLexemeIndex] = '\0';
					state = 52;
					endoffile = 1;
				}

				else
				{
					state = 36;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 37:
			if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 38;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					lexeme[curLexemeIndex] = '\0';
					state = 52;
					endoffile = 1;
				}

				else
				{
					state = 37;
				}
			}
			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 38:
			lexeme[curLexemeIndex] = '\0';
			float value1 = (float)atof(lexeme);
			token->value = (Value *)malloc(sizeof(Value));
			token->value->realNum = value1;
			createToken(token, TK_RNUM, lexeme, 1, token->value);
			ifFinalReached = 1;
			break;
		case 39:
			if ((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 40;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}
				else
				{
					state = 39;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 40:
			if ((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 40;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 41;
				}

				else
				{
					state = 40;
				}
			}

			else
			{
				state = 41;
				fLexerPtr++;
			}
			break;
		case 41:
			lexeme[curLexemeIndex] = '\0';

			createToken(token, TK_RECORDID, lexeme, -1, NULL);

			//retract
			fLexerPtr--;
			ifFinalReached = 1;
			break;
		case 42:
			if (((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z')) || ((currBuffer[fLexerPtr] >= 'A') && (currBuffer[fLexerPtr] <= 'Z')))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 43;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}

				else
				{
					state = 42;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 43:
			if (((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z')) || ((currBuffer[fLexerPtr] >= 'A') && (currBuffer[fLexerPtr] <= 'Z')))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 43;
				fLexerPtr++;
			}
			else if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 44;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 43;
				}

				else
				{
					state = 43;
				}
			}

			else
			{
				state = 45;
				fLexerPtr++;
			}
			break;
		case 44:
			if (isdigit(currBuffer[fLexerPtr]))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 44;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 45;
				}

				else
				{
					state = 44;
				}
			}
			else
			{
				state = 45;
				fLexerPtr++;
			}
			break;
		case 45:
			lexeme[curLexemeIndex] = '\0';
			fLexerPtr--;
			if (strlen(lexeme) > 30)
			{
				fprintf(stderr, "Line No: %d, Lexical Error, Identifier is longer than the prescribed length of 20 characters\n", lineNoGlob);
				state = 52;
			}
			else
			{
				Node lookup = getType_Token(lexeme, lookUpTable);

				if (lookup == NULL)
					token->type = TK_FUNID;
				else
					token->type = lookup->type;

				createToken(token, token->type, lexeme, -1, NULL);
				ifFinalReached = 1;
			}
			break;
		case 46:
			if ((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 46;
				fLexerPtr++;
			}

			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 47;
				}

				else
				{
					state = 46;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				fLexerPtr++;
				state = 47;
			}
			break;
		case 47:
			lexeme[curLexemeIndex] = '\0';
			fLexerPtr--;
			Node lookup = getType_Token(lexeme, lookUpTable);

			if (lookup == NULL)
				token->type = TK_FIELDID;
			else
				token->type = lookup->type;

			createToken(token, token->type, lexeme, -1, NULL);
			ifFinalReached = 1;
			break;
		case 48:
			if ((currBuffer[fLexerPtr] >= 'a') && (currBuffer[fLexerPtr] <= 'z'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 46;
				fLexerPtr++;
			}
			else if ((currBuffer[fLexerPtr] >= '2') && (currBuffer[fLexerPtr] <= '7'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 49;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 52;
				}

				else
				{
					state = 48;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				state = 52;
			}
			break;
		case 49:
			if ((currBuffer[fLexerPtr] >= 'b') && (currBuffer[fLexerPtr] <= 'd'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 49;
				fLexerPtr++;
			}
			else if ((currBuffer[fLexerPtr] >= '2') && (currBuffer[fLexerPtr] <= '7'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 50;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 51;
				}

				else
				{
					state = 49;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				fLexerPtr++;
				state = 51;
			}
			break;
		case 50:
			if ((currBuffer[fLexerPtr] >= '2') && (currBuffer[fLexerPtr] <= '7'))
			{
				lexeme[curLexemeIndex] = currBuffer[fLexerPtr];
				curLexemeIndex++;
				state = 50;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0')
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{

					lexeme[curLexemeIndex] = '\0';
					endoffile = 1;
					state = 51;
				}

				else
				{
					state = 50;
				}
			}

			else
			{
				lexeme[curLexemeIndex] = '\0';
				fLexerPtr++;
				state = 51;
			}
			break;
		case 51:
			lexeme[curLexemeIndex] = '\0';
			fLexerPtr--;
			if (strlen(lexeme) > 20)
			{
				fprintf(stderr, "Line No: %d, Lexical Error, Identifier is longer than the prescribed length of 20 characters\n", lineNoGlob);
				state = 52;
			}
			else
			{
				createToken(token, TK_ID, lexeme, -1, NULL);
				ifFinalReached = 1;
			}
			break;
		case 52:
			lexeme[curLexemeIndex] = '\0';

			createToken(token, ERROR, lexeme, -2, NULL);
			fprintf(stderr, "Line No: %d, Lexical Error, Unknown Pattern %s\n", token->lineNum, token->lexeme);
			ifFinalReached = 1;
			break;
		case 53:
			if (currBuffer[fLexerPtr] == '\n')
			{
				lineNoGlob++;
				state = 0;
				fLexerPtr++;
			}
			else if (currBuffer[fLexerPtr] == '\0' || currBuffer[fLexerPtr] == -1)
			{
				fLexerPtr = 0;
				*fp = loadBuffer(*fp);
				if (*fp == NULL)
				{
					return NULL;
				}

				else
				{
					state = 53;
				}
			}
			else
			{
				state = 53;
				fLexerPtr++;
			}
			break;
		}
		if (ifFinalReached == 1)
			break;
	}
	return token;
}

FILE *initLexer(char *input_code_file)
{

	FILE *fp = fopen(input_code_file, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "File not opened ----- ERROR\n");
		return NULL;
	}
	else
	{
		printf("\n\n\t\tFile Opened\n\n");
	}

	currBuffer = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
	nextBuffer = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
	int i;
	for (i = 0; i < sizeof(currBuffer); i++)
		currBuffer[i] = '\0';
	for (i = 0; i < sizeof(nextBuffer); i++)
		nextBuffer[i] = '\0';

	endoffile = 0;
	fLexerPtr = 0;
	lineNoGlob = 1;

	lookUpTable = newLookUpTable(SLOTS);

	return fp;
}

void printAllTokens(char *input_code_file)
{

	FILE *fp = initLexer(input_code_file);

	Token token;

	printf("Printing tokens.............\n\n");

	token = getToken(&fp);
	int i = 1;
	while (token != NULL)
	{
		/*
		if(token->valType==-1)
			printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n",token->lineNum, token->lexeme, tokenStrings[token->type]);
		if(token->valType==0)
			printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n",token->lineNum, token->lexeme, tokenStrings[token->type]);
		if(token->valType==1)
			printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n",token->lineNum, token->lexeme, tokenStrings[token->type]);
		if(token->valType==-2)
			printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n",token->lineNum, token->lexeme, tokenStrings[token->type]);
		 */
		//NO IDEA WHY THIS IS DONE. REPLACING IT WITH NEXT LINE
		printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n", token->lineNum, token->lexeme, tokenStrings[token->type]);
		token = getToken(&fp);
		i++;
	}

	if (fp != NULL)
		fclose(fp);
}

void createToken(Token token, Tokentype type, char *lexeme, int valueType, Value *value)
{
	token->lineNum = lineNoGlob;
	token->type = type;
	token->valType = valueType;
	token->lexeme = lexeme;
	token->value = value;
}

void removeComments(char *testcaseFile, char *cleanFile)
{
	currBuffer = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
	nextBuffer = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
	int i;
	for (i = 0; i < sizeof(currBuffer); i++)
		currBuffer[i] = '\0';
	for (i = 0; i < sizeof(nextBuffer); i++)
		nextBuffer[i] = '\0';

	FILE *input = fopen(testcaseFile, "r");
	FILE *output = fopen(cleanFile, "w+");
	char ch;

	lineNoGlob = 1;
	fLexerPtr = 0;
	endoffile = 0;

	if (input == NULL)
	{
		fprintf(stderr, "File Not opened ---> ERROR\n");
		return;
	}
	input = loadBuffer(input);
	i = 0;
	int emptyline = 1;
	int eof = 0;

	while (1)
	{
		if ((currBuffer[fLexerPtr] == -1) || (currBuffer[i] == '\0'))
		{
			input = loadBuffer(input);
			if (input == NULL)
			{
				break;
			}
			i = 0;
		}
		if (currBuffer[i] == '%')
		{
			i++;
			while (currBuffer[i] != '\n')
			{
				if ((currBuffer[fLexerPtr] == -1) || (currBuffer[i] == '\0'))
				{
					input = loadBuffer(input);
					if (input == NULL)
					{
						eof = 1;
						break;
					}
					i = -1;
				}
				i++;
			}
		}
		if (eof == 1)
			break;
		if (currBuffer[i] == -1)
			break;
		if (currBuffer[i] != '\n')
			emptyline = 0;
		else
		{
			emptyline = 1;
			fprintf(output, "\n");
		}
		if ((emptyline != 1) || (currBuffer[i] != '\n'))
		{
			fprintf(output, "%c", currBuffer[i]);
		}
		i++;
	}
	if (input != NULL)
		fclose(input);
}
