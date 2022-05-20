/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include "lexerDef.h"

Token getToken(FILE **file_ptr);
FILE *loadBuffer(FILE *file_ptr);
void printAllTokens(char *input_code_file);
void createToken(Token token, Tokentype type, char *lexeme, int valueType, Value *value);
void removeComments(char *testcaseFile, char *cleanFile);
FILE *initLexer(char *input_code_file);