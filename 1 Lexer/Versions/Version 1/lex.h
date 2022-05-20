/*
Group Number  --> 23
Names and IDs --> 1. Garvit	Soni			    2017B3A70458H
				  2. Aman Badjate   		    2017B3A70559H
				  3. Prakhar Suryavansh         2017B4A71017H
*/

#include "lexDef.h"

Token getToken(FILE *file_ptr);
FILE *loadBuffer(FILE *file_ptr, int bufferNumber);
void printAllTokens(char *input_code_file);
void createToken(Token token, Tokentype type, char *lexeme, int valueType, Value *value);
// void removeComments(char *testcaseFile, char *cleanFile);
FILE *initLexer(char *input_code_file);
int checkKeyword(char *key);