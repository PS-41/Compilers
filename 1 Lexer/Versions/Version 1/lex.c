#include "lex.h"
#include <string.h>
#include <ctype.h>

char *tokenStrings[] = {"TK_SQL",
                        "TK_SQR",
                        "TK_COMMA",
                        "TK_SEM",
                        "TK_OP",
                        "TK_CL",
                        "TK_FLOWERL",
                        "TK_FLOWERR",
                        "TK_PLUS",
                        "TK_MINUS",
                        "TK_MUL",
                        "TK_DIV",
                        "TK_MOD",
                        "TK_AND",
                        "TK_OR",
                        "TK_XOR",
                        "TK_LT",
                        "TK_LE",
                        "TK_EQ",
                        "TK_GT",
                        "TK_GE",
                        "TK_NE",
                        "TK_ASSIGNOP",
                        "TK_NUM",
                        "TK_RNUM",
                        "TK_ID",
                        "TK_FUNID",
                        "TK_STRING",
                        "TK_KEY",
                        "ERROR"};

char *keywords[] = {"int",
                    "real",
                    "bool",
                    "string",
                    "loop",
                    "if",
                    "else",
                    "gap"};

#define SIZEOFBUFFER 3000

char *buffer1;
char *buffer2;
char *currBuffer;

int lineNoGlob = 1;

int fLexerPtr = 0;

int endoffile = 0;

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
        // printf("ch=%c\nstate=%d\n\n", ch, state);
        // printf("start\n%s\n%s\n%s\nend\n\n", currBuffer, buffer1, buffer2);
        // printf("lexeme = %s\n", lexeme);

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
                state = 9;
            }

            else if (ch == '-')
            {
                state = 10;
            }

            else if (ch == '*')
            {
                state = 11;
            }

            else if (ch == '/')
            {
                state = 12;
            }
            else if (ch == '%')
            {
                state = 13;
            }
            else if (ch == '&')
            {
                state = 14;
            }
            else if (ch == '|')
            {
                state = 15;
            }
            else if (ch == '^')
            {
                state = 16;
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
            else if (ch == '!')
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 20;
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
            else
            {
                lexeme[curLexemeIndex] = ch;
                curLexemeIndex++;
                state = 25;
            }
            break;

        case 1:
            strcpy(lexeme, "{");
            createToken(token, TK_FLOWERL, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 2:
            strcpy(lexeme, "}");
            createToken(token, TK_FLOWERR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 3:
            strcpy(lexeme, "(");
            createToken(token, TK_OP, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 4:
            strcpy(lexeme, ")");
            createToken(token, TK_CL, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 5:
            strcpy(lexeme, "[");
            createToken(token, TK_SQL, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 6:
            strcpy(lexeme, "]");
            createToken(token, TK_SQR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 7:
            strcpy(lexeme, ",");
            createToken(token, TK_COMMA, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 8:
            strcpy(lexeme, ";");
            createToken(token, TK_SEM, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 9:
            strcpy(lexeme, "+");
            createToken(token, TK_PLUS, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 10:
            strcpy(lexeme, "-");
            createToken(token, TK_MINUS, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 11:
            strcpy(lexeme, "*");
            createToken(token, TK_MUL, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 12:
            strcpy(lexeme, "/");
            createToken(token, TK_DIV, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 13:
            strcpy(lexeme, "%");
            createToken(token, TK_MOD, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 14:
            strcpy(lexeme, "&");
            createToken(token, TK_AND, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 15:
            strcpy(lexeme, "|");
            createToken(token, TK_OR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 16:
            strcpy(lexeme, "^");
            createToken(token, TK_XOR, lexeme, -1, NULL);
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
            createToken(token, TK_LE, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 27:
            strcpy(lexeme, "<");
            createToken(token, TK_LT, lexeme, -1, NULL);
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
            createToken(token, TK_GE, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 29:
            strcpy(lexeme, ">");
            createToken(token, TK_GT, lexeme, -1, NULL);
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
            createToken(token, TK_EQ, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 31:
            strcpy(lexeme, "=");
            createToken(token, TK_ASSIGNOP, lexeme, -1, NULL);
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
            createToken(token, TK_NE, lexeme, -1, NULL);
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
            createToken(token, TK_NUM, lexeme, 0, NULL);
            ifFinalReached = 1;
            break;

        case 35:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_RNUM, lexeme, 1, NULL);
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
            if (checkKeyword(lexeme))
            {
                lexeme[curLexemeIndex] = '\0';
                createToken(token, TK_KEY, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            else
            {
                lexeme[curLexemeIndex] = '\0';
                createToken(token, TK_ID, lexeme, -1, NULL);
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
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_FUNID, lexeme, -1, NULL);
            ifFinalReached = 1;
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
            createToken(token, TK_STRING, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 25:
            lexeme[curLexemeIndex] = '\0';
            createToken(token, ERROR, lexeme, -2, NULL);
            fprintf(stderr, "Line No: %d, Lexical Error, Unknown Pattern %s\n", token->lineNum, token->lexeme);
            ifFinalReached = 1;
            break;

        } // end of switch case
        if (ifFinalReached)
            break;
    } // end of while
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
    return fp;
}

void printAllTokens(char *input_code_file)
{
    FILE *fp = initLexer(input_code_file);

    Token token;

    printf("Printing tokens.............\n\n");

    token = getToken(fp);
    int i = 1;
    while (token != NULL)
    {
        fLexerPtr--; // Retract
        printf("Line Number: %-5d     Lexeme: %22s               Token Type: %15s\n", token->lineNum, token->lexeme, tokenStrings[token->type]);
        token = getToken(fp);
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

int checkKeyword(char *key)
{
    for (int i = 0; i < 8; i++)
    {
        if (strcmp(key, keywords[i]) == 0)
            return 1;
    }
    return 0;
}