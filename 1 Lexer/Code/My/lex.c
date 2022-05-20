#include "lex.h"
#include <string.h>
#include <ctype.h>

char *tokenStrings[] = {"TK_SQL_DELIMITER",
                        "TK_SQR_DELIMITER",
                        "TK_COMMA_DELIMITER",
                        "TK_SEM_DELIMITER",
                        "TK_OP_DELIMITER",
                        "TK_CL_DELIMITER",
                        "TK_FLOWERL_DELIMITER",
                        "TK_FLOWERR_DELIMITER",
                        "TK_PLUS_OPERATOR",
                        "TK_MINUS_OPERATOR",
                        "TK_MUL_OPERATOR",
                        "TK_DIV_OPERATOR",
                        "TK_MOD_OPERATOR",
                        "TK_BITWISE_AND_OPERATOR",
                        "TK_BITWISE_OR_OPERATOR",
                        "TK_BITWISE_XOR_OPERATOR",
                        "TK_LT_OPERATOR",
                        "TK_LE_OPERATOR",
                        "TK_EQ_OPERATOR",
                        "TK_GT_OPERATOR",
                        "TK_GE_OPERATOR",
                        "TK_NE_OPERATOR",
                        "TK_ASSIGN_OPERATOR",
                        "TK_INTEGER_LITERAL",
                        "TK_FLOATING_POINT_LITERAL",
                        "TK_IDENTIFIER",
                        "TK_FUNCTION_IDENTIFIER",
                        "TK_STRING_LITERAL",
                        "TK_INT_KEYWORD",
                        "TK_REAL_KEYWORD",
                        "TK_BOOL_KEYWORD",
                        "TK_STRING_KEYWORD",
                        "TK_LOOP_KEYWORD",
                        "TK_IF_KEYWORD",
                        "TK_ELSE_KEYWORD",
                        "TK_GAP_KEYWORD",
                        "ERROR"};

Keywords keywords[] = {{"int", TK_INT_KEYWORD},
                       {"real", TK_REAL_KEYWORD},
                       {"bool", TK_BOOL_KEYWORD},
                       {"string", TK_STRING_KEYWORD},
                       {"loop", TK_LOOP_KEYWORD},
                       {"if", TK_IF_KEYWORD},
                       {"else", TK_ELSE_KEYWORD},
                       {"gap", TK_GAP_KEYWORD}};

#define SIZEOFBUFFER 3000

char *buffer1;
char *buffer2;
char *currBuffer;

int lineNoGlob = 1;
int fLexerPtr = 0;
int endoffile = 0;
int noOfKeywords = 8;

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
            createToken(token, TK_MOD_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 14:
            strcpy(lexeme, "&");
            createToken(token, TK_BITWISE_AND_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 15:
            strcpy(lexeme, "|");
            createToken(token, TK_BITWISE_OR_OPERATOR, lexeme, -1, NULL);
            ifFinalReached = 1;
            break;

        case 16:
            strcpy(lexeme, "^");
            createToken(token, TK_BITWISE_XOR_OPERATOR, lexeme, -1, NULL);
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
            createToken(token, TK_NE_OPERATOR, lexeme, -1, NULL);
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
            if (checkKeyword(lexeme))
            {
                int check = checkKeyword(lexeme);
                lexeme[curLexemeIndex] = '\0';
                createToken(token, keywords[check - 1].type, lexeme, -1, NULL);
                ifFinalReached = 1;
            }
            else
            {
                lexeme[curLexemeIndex] = '\0';
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
            lexeme[curLexemeIndex] = '\0';
            createToken(token, TK_FUNCTION_IDENTIFIER, lexeme, -1, NULL);
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
            createToken(token, TK_STRING_LITERAL, lexeme, -1, NULL);
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
    // noOfKeywords = 8;
    return fp;
}

void modify(char *input_code_file)
{
    FILE *file = fopen(input_code_file, "r");
    char *tmp;
    size_t n = 0;
    int c;
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    tmp = malloc(f_size);
    while ((c = fgetc(file)) != EOF)
    {
        tmp[n++] = (char)c;
    }
    fclose(file);
    tmp[n] = ' ';
    file = fopen("modified_input_code.txt", "w");
    for (int i = 0; i <= n; i++)
        putc(tmp[i], file);
    fclose(file);
}

void printAllTokens(char *input_code_file)
{
    modify(input_code_file);
    char *modified_input_code_file = "modified_input_code.txt";
    FILE *fp = initLexer(modified_input_code_file);

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
    for (int i = 0; i < noOfKeywords; i++)
    {
        if (strcmp(key, keywords[i].word) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}