/*
Group Number  --> 23
Names and IDs --> 1. Garvit	Soni			    2017B3A70458H
				  2. Aman Badjate   		    2017B3A70559H
				  3. Prakhar Suryavansh         2017B4A71017H
*/

#include "lexer.hpp"
#include <string.h>
#include <ctype.h>
#include <bits/stdc++.h>
using namespace std;

deque<pair<pair<string, string>, int> > lexer_generated_tokens;

char *tokenStrings[] = {(char *)"TK_SQL_DELIMITER",
                        (char *)"TK_SQR_DELIMITER",
                        (char *)"TK_COMMA_DELIMITER",
                        (char *)"TK_SEM_DELIMITER",
                        (char *)"TK_OP_DELIMITER",
                        (char *)"TK_CL_DELIMITER",
                        (char *)"TK_FLOWERL_DELIMITER",
                        (char *)"TK_FLOWERR_DELIMITER",
                        (char *)"TK_PLUS_OPERATOR",
                        (char *)"TK_MINUS_OPERATOR",
                        (char *)"TK_MUL_OPERATOR",
                        (char *)"TK_DIV_OPERATOR",
                        (char *)"TK_LT_OPERATOR",
                        (char *)"TK_LE_OPERATOR",
                        (char *)"TK_EQ_OPERATOR",
                        (char *)"TK_GT_OPERATOR",
                        (char *)"TK_GE_OPERATOR",
                        (char *)"TK_ASSIGN_OPERATOR",
                        (char *)"TK_INTEGER_LITERAL",
                        (char *)"TK_FLOATING_POINT_LITERAL",
                        (char *)"TK_IDENTIFIER",
                        (char *)"TK_FUNCTION_IDENTIFIER",
                        (char *)"TK_STRING_LITERAL",
                        (char *)"TK_INT_KEYWORD",
                        (char *)"TK_REAL_KEYWORD",
                        (char *)"TK_STRING_KEYWORD",
                        (char *)"TK_LOOP_KEYWORD",
                        (char *)"TK_IF_KEYWORD",
                        (char *)"TK_ELSE_KEYWORD",
                        (char *)"TK_GAP_KEYWORD",
                        (char *)"TK_LOGICAL_AND_KEYWORD",
                        (char *)"TK_LOGICAL_OR_KEYWORD",
                        (char *)"TK_READ_KEYWORD",
                        (char *)"TK_WRITE_KEYWORD",
                        (char *)"TK_RETURN_KEYWORD",
                        (char *)"TK_INPUT_KEYWORD",
                        (char *)"TK_PARAMETER_KEYWORD",
                        (char *)"TK_OUTPUT_KEYWORD",
                        (char *)"________________UNKNOWN_TOKEN_ERROR"};

Keywords keywords[] = {{(char *)"int", TK_INT_KEYWORD},
                       {(char *)"real", TK_REAL_KEYWORD},
                       {(char *)"string", TK_STRING_KEYWORD},
                       {(char *)"loop", TK_LOOP_KEYWORD},
                       {(char *)"if", TK_IF_KEYWORD},
                       {(char *)"else", TK_ELSE_KEYWORD},
                       {(char *)"_gap", TK_GAP_KEYWORD},
                       {(char *)"and", TK_LOGICAL_AND_KEYWORD},
                       {(char *)"or", TK_LOGICAL_OR_KEYWORD},
                       {(char *)"read", TK_READ_KEYWORD},
                       {(char *)"write", TK_WRITE_KEYWORD},
                       {(char *)"return", TK_RETURN_KEYWORD},
                       {(char *)"input", TK_INPUT_KEYWORD},
                       {(char *)"parameter", TK_PARAMETER_KEYWORD},
                       {(char *)"output", TK_OUTPUT_KEYWORD}};

#define SIZEOFBUFFER 3000

char *buffer1;
char *buffer2;
char *currBuffer;

int lineNoGlob = 1;
int fLexerPtr = 0;
int endoffile = 0;
int noOfKeywords = 15;
int checkOperator = 0;

/*
    * This functions loads the buffer.
*/
FILE *loadBuffer(FILE *fp, int bufferNumber)
{
    if (feof(fp))
    {
        fclose(fp);
        return NULL;
    }
    int count = 0;
    if (bufferNumber == 1)
    {
        for (int i = 0; i < SIZEOFBUFFER; i++)
            buffer1[i] = 0;
        count = fread(buffer1, sizeof(char), SIZEOFBUFFER, fp);
        buffer1[SIZEOFBUFFER] = '\0';
    }
    else
    {
        for (int i = 0; i < SIZEOFBUFFER; i++)
            buffer2[i] = 0;
        count = fread(buffer2, sizeof(char), SIZEOFBUFFER, fp);
        buffer2[SIZEOFBUFFER] = '\0';
    }
    if (count <= 0)
    {
        fclose(fp);
        return NULL;
    }
    else
    {
        return fp;
    }
}

/*
    * This function returns the token one by one.
*/
Token getToken(FILE *fp)
{
    if (endoffile == 1)
    {
        if (fp != NULL)
            fclose(fp);
        return NULL;
    }
    Token token = (Token)malloc(sizeof(Token1));

    int state = 0;
    int ifFinalReached = 0;
    char *lexeme = (char *)malloc(100 * sizeof(char));
    int curLexemeIndex = 0;

    while (1)
    {
        if (currBuffer[fLexerPtr] == '\0')
        {
            fLexerPtr = 0;
            if (currBuffer == buffer1)
                fp = loadBuffer(fp, 2), currBuffer = buffer2;
            else
                fp = loadBuffer(fp, 1), currBuffer = buffer1;
            if (fp == NULL)
            {
                endoffile = 1;
                return NULL;
            }
        }
        char ch = currBuffer[fLexerPtr++];

        switch (state)
        {

        case 0:
            if (ch == ' ' || ch == '\t' || ch == '\r' || ch == 13)
            {
                state = 0;
            }
            else if (ch == '\n')
            {
                lineNoGlob++;
                checkOperator = 0;
                state = 0;
            }
            else if (ch == '{')
            {
                state = 1;
            }

            else if (ch == '}')
            {
                state = 2;
            }
            else if (ch == '(')
            {
                state = 3;
            }

            else if (ch == ')')
            {
                state = 4;
            }
            else if (ch == '[')
            {
                state = 5;
            }

            else if (ch == ']')
            {
                state = 6;
            }

            else if (ch == ',')
            {
                state = 7;
            }

            else if (ch == ';')
            {
                state = 8;
            }

            else if (ch == '+')
            {
                if (checkOperator)
                {
                    state = 9;
                }
                else
                {
                    lexeme[curLexemeIndex] = ch;
                    curLexemeIndex++;
                    state = 42;
                }
            }

            else if (ch == '-')
            {
                if (checkOperator)
                {
                    state = 10;
                }
                else
                {
                    lexeme[curLexemeIndex] = ch;
                    curLexemeIndex++;
                    state = 43;
                }
            }

            else if (ch == '*')
            {
                state = 11;
            }

            else if (ch == '/')
            {
                state = 12;
            }
            else if (ch == '<')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 17;
            }
            else if (ch == '>')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 18;
            }
            else if (ch == '=')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 19;
            }
            else if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 21;
            }
            else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 22;
            }
            else if (ch == '_')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 23;
            }
            else if (ch == 34)
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 24;
            }
            else if (ch == '$')
            {
                state = 40;
            }
            else if (ch == '.')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 41;
            }
            else
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 25;
            }
            break;

        case 1:
            strcpy(lexeme, "{");
            createToken(token, TK_FLOWERL_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 2:
            strcpy(lexeme, "}");
            createToken(token, TK_FLOWERR_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 3:
            strcpy(lexeme, "(");
            createToken(token, TK_OP_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 4:
            strcpy(lexeme, ")");
            createToken(token, TK_CL_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 5:
            strcpy(lexeme, "[");
            createToken(token, TK_SQL_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 6:
            strcpy(lexeme, "]");
            createToken(token, TK_SQR_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 7:
            strcpy(lexeme, ",");
            createToken(token, TK_COMMA_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 8:
            strcpy(lexeme, ";");
            createToken(token, TK_SEM_DELIMITER, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 9:
            strcpy(lexeme, "+");
            createToken(token, TK_PLUS_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 10:
            strcpy(lexeme, "-");
            createToken(token, TK_MINUS_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 11:
            strcpy(lexeme, "*");
            createToken(token, TK_MUL_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 12:
            strcpy(lexeme, "/");
            createToken(token, TK_DIV_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 13:
            strcpy(lexeme, "%");
            // createToken(token, TK_MOD_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 14:
            strcpy(lexeme, "&");
            // createToken(token, TK_BITWISE_AND_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 15:
            strcpy(lexeme, "|");
            // createToken(token, TK_BITWISE_OR_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 16:
            strcpy(lexeme, "^");
            // createToken(token, TK_BITWISE_XOR_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 17:
            if (ch == '=')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 26;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 27;
            }
            break;

        case 26:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_LE_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 27:
            strcpy(lexeme, "<");
            createToken(token, TK_LT_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 18:
            if (ch == '=')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 28;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 29;
            }
            break;

        case 28:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_GE_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 29:
            strcpy(lexeme, ">");
            createToken(token, TK_GT_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 19:
            if (ch == '=')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 30;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 31;
            }
            break;

        case 30:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_EQ_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 31:
            strcpy(lexeme, "=");
            createToken(token, TK_ASSIGN_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 20:
            if (ch == '=')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 32;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 25;
            }
            break;

        case 32:
            lexeme[curLexemeIndex] = '\0';
            // createToken(token, TK_NE_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 21:
            if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 21;
            }
            else if (ch == '.')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 33;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 34;
            }
            break;

        case 33:
            if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 33;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 35;
            }
            break;

        case 34:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_INTEGER_LITERAL, lexeme, 0, NULL);
            ifFinalReached = 1;
            break;

        case 35:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_FLOATING_POINT_LITERAL, lexeme, 1, NULL);
            ifFinalReached = 1;
            break;

        case 22:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 22;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 36;
            }
            break;

        case 36:
            lexeme[curLexemeIndex] = '\0';
            if (checkKeyword(lexeme))
            {
                int check = checkKeyword(lexeme);
                createToken(token, keywords[check - 1].type, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            else
            {
                // lexeme[curLexemeIndex] = '\0';
                createToken(token, TK_IDENTIFIER, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            break;

        case 23:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 37;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 25;
            }
            break;

        case 37:
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 37;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 38;
            }
            break;

        case 38:
            if (!strcmp(lexeme, "_gap"))
            {
                lexeme[curLexemeIndex] = '\0';
                createToken(token, TK_GAP_KEYWORD, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            else
            {
                lexeme[curLexemeIndex] = '\0';
                createToken(token, TK_FUNCTION_IDENTIFIER, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            break;

        case 24:
            if (ch == 10)
            {
                fLexerPtr--;
                state = 25;
            }
            else if (ch == 34)
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                if (lexeme[curLexemeIndex - 2] == 92)
                {
                    state = 24;
                }
                else
                {
                    state = 39;
                }
            }
            else
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 24;
            }
            break;

        case 39:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_STRING_LITERAL, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 40:
            if (ch == '$')
            {
                state = 0;
            }
            else
            {
                if (ch == '\n')
                    lineNoGlob++;
                state = 40;
            }
            break;

        case 41:
            if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 33;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 25;
            }
            break;

        case 42:
            if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 21;
            }
            else if (ch == '.')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 41;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 9;
            }
            break;

        case 43:
            if (isdigit(ch))
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 21;
            }
            else if (ch == '.')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 41;
            }
            else
            {
                fLexerPtr--; // Retract
                state = 10;
            }
            break;

        case 25:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, UNKNOWN_TOKEN_ERROR, lexeme, -2, NULL);
            ifFinalReached = 1;
            break;

        } // end of switch case
        if (ifFinalReached)
            break;
    } // end of while
    return token;
}

/*
    * This function initialises all the contents required by the lexer.
*/
FILE *initLexer(char *input_code_file)
{

    FILE *fp = fopen(input_code_file, "r");
    if (fp == NULL)
    {
        return NULL;
    }

    buffer1 = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
    buffer2 = (char *)malloc(sizeof(char) * (SIZEOFBUFFER + 1));
    int i;
    for (i = 0; i < sizeof(buffer1); i++)
        buffer1[i] = '\0';
    for (i = 0; i < sizeof(buffer2); i++)
        buffer2[i] = '\0';
    currBuffer = buffer1;
    endoffile = 0;
    fLexerPtr = 0;
    lineNoGlob = 1;
    noOfKeywords = 15;
    return fp;
}

/*
    * This modifies the input code by adding a newline at the end.
*/
void modify(char *input_code_file)
{
    FILE *file = fopen(input_code_file, "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nFile not found ----- ERROR\n");
        endoffile = 1;
        return;
    }
    char *tmp;
    size_t n = 0;
    int c;
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    tmp = (char *)malloc(f_size);
    while ((c = fgetc(file)) != EOF)
    {
        tmp[n++] = (char)c;
    }
    fclose(file);
    tmp[n] = 10;
    file = fopen("..\\output\\modified_input_code.txt", "w");
    for (int i = 0; i <= n; i++)
        putc(tmp[i], file);
    fclose(file);
}

/*
    * This function is called by the driver to generate all the tokens and return it to be parsed.
*/
deque<pair<pair<string, string>, int> > generateAllTokens(char *input_code_file)
{
    modify(input_code_file);
    if (endoffile)
        return lexer_generated_tokens;
    input_code_file = (char *)"..\\output\\modified_input_code.txt";
    FILE *fp = initLexer(input_code_file);

    Token token;

    printf("\nLine Number                              Lexeme                              Token Type/Error\n\n");

    FILE *lexout = fopen("..\\output\\lexer_out.txt", "w");
    token = getToken(fp);
    int i = 1;
    while (token != NULL)
    {
        fLexerPtr--; // Retract
        if (!strcmp(tokenStrings[token->type], "TK_INTEGER_LITERAL") || !strcmp(tokenStrings[token->type], "TK_FLOATING_POINT_LITERAL") || !strcmp(tokenStrings[token->type], "TK_IDENTIFIER"))
            checkOperator = 1;
        else
            checkOperator = 0;
        fputs(tokenStrings[token->type], lexout);
        fputs(" ", lexout);
        fputs(token->lexeme, lexout);
        fputs(" ", lexout);
        fprintf(lexout, "%d", token->lineNum);
        fputs(" ", lexout);
        printf("%11d%36s%46s\n", token->lineNum, token->lexeme, tokenStrings[token->type]);

        string a, b;
        int c;
        a = tokenStrings[token->type];
        if (a == "\0") {
            break;
        }
        b = token->lexeme;
        c = token->lineNum;
        
        lexer_generated_tokens.push_back(make_pair(make_pair(a, b), c));

        token = getToken(fp);
        i++;
    }
    lexer_generated_tokens.push_back(make_pair(make_pair("$", "$"), lineNoGlob - 1));

    fclose(lexout);
    if (fp != NULL)
        fclose(fp);

    return lexer_generated_tokens;
}


/*
    * A utility function to create the token.
*/
void createToken(Token token, Tokentype type, char *lexeme, int valueType, Value *value)
{
    token->lineNum = lineNoGlob;
    token->type = type;
    token->valType = valueType;
    token->lexeme = lexeme;
    token->value = value;
}

/*
    * A utility function to check if a given string is a keyword or not.
*/
int checkKeyword(char *key)
{
    for (int i = 0; i < noOfKeywords; i++)
    {
        if (strcmp(key, keywords[i].word) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}