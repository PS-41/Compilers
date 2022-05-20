/*
Group Number  --> 23
Names and IDs --> 1. Garvit Soni                2017B3A70458H
                  2. Aman Badjate               2017B3A70559H
                  3. Prakhar Suryavansh         2017B4A71017H
*/

#include <bits/stdc++.h>
#include "parser.hpp"
using namespace std;
vector<string> symbols;
vector<vector<string> >rules;
map<pair<string, string>, int> table;
ofstream file;

/*
    * This function initialises the content required by the parser.
*/
void init()
{
    symbols = { "PROGRAM",
                "MAINFUNC",
                "OTHERFUNC",
                "FUNCTION",
                "INPUT_PAR",
                "OUTPUT_PAR",
                "PARAMETER_LIST",
                "DATA_TYPE",
                "REMAINING_LIST",
                "STMTS",
                "STMT",
                "DECLSTMT",
                "ASSIGNSTMT",
                "ARITHEXP",
                "EXPPRIME",
                "TERM",
                "TERMPRIME",
                "FACTOR",
                "HIGHPOP",
                "LOWPOP",
                "VAR",
                "LOOPSTMT",
                "BOOLEXP",
                "RELOP",
                "LOGOP",
                "CONDSTMT",
                "CONDSTMTPRIME",
                "IOSTMT",
                "FUNCALSTMT",
                "OUTPUT_PARAM",
                "INPUT_PARAM",
                "IDLIST",
                "MOREID",
                "RETSTMT",
                "OPRESTMT",
                "TK_GAP_KEYWORD",
                "TK_FLOWERL_DELIMITER",
                "TK_FLOWERR_DELIMITER",
                "TK_FUNCTION_IDENTIFIER",
                "TK_SEM_DELIMITER",
                "TK_INPUT_KEYWORD",
                "TK_PARAMETER_KEYWORD",
                "TK_SQL_DELIMITER",
                "TK_SQR_DELIMITER",
                "TK_OUTPUT_KEYWORD",
                "TK_IDENTIFIER",
                "TK_INT_KEYWORD",
                "TK_REAL_KEYWORD",
                "TK_STRING_KEYWORD",
                "TK_COMMA_DELIMITER",
                "TK_ASSIGN_OPERATOR",
                "TK_OP_DELIMITER",
                "TK_CL_DELIMITER",
                "TK_MUL_OPERATOR",
                "TK_DIV_OPERATOR",
                "TK_PLUS_OPERATOR",
                "TK_MINUS_OPERATOR",
                "TK_INTEGER_LITERAL",
                "TK_FLOATING_POINT_LITERAL",
                "TK_STRING_LITERAL",
                "TK_LOOP_KEYWORD",
                "TK_LT_OPERATOR",
                "TK_LE_OPERATOR",
                "TK_EQ_OPERATOR",
                "TK_GE_OPERATOR",
                "TK_GT_OPERATOR",
                "TK_LOGICAL_AND_KEYWORD",
                "TK_LOGICAL_OR_KEYWORD",
                "TK_IF_KEYWORD",
                "TK_ELSE_KEYWORD",
                "TK_READ_KEYWORD",
                "TK_WRITE_KEYWORD",
                "TK_RETURN_KEYWORD"
              };

    rules = { {"synch"},
        {"OTHERFUNC" , "MAINFUNC"},
        {"TK_GAP_KEYWORD", "TK_FLOWERL_DELIMITER", "STMTS", "TK_FLOWERR_DELIMITER"},
        {"FUNCTION", "OTHERFUNC"},
        {"epsilon"},
        {"TK_FUNCTION_IDENTIFIER" , "TK_FLOWERL_DELIMITER", "INPUT_PAR", "OUTPUT_PAR", "TK_SEM_DELIMITER", "STMTS", "TK_FLOWERR_DELIMITER" },
        {"TK_INPUT_KEYWORD", "TK_PARAMETER_KEYWORD", "TK_SQL_DELIMITER", "PARAMETER_LIST", "TK_SQR_DELIMITER"},
        {"TK_OUTPUT_KEYWORD", "TK_PARAMETER_KEYWORD", "TK_SQL_DELIMITER", "PARAMETER_LIST", "TK_SQR_DELIMITER"},
        {"epsilon"},
        {"DATA_TYPE", "TK_IDENTIFIER", "REMAINING_LIST"},
        {"TK_INT_KEYWORD"},
        {"TK_REAL_KEYWORD"},
        {"TK_STRING_KEYWORD"},
        {"TK_COMMA_DELIMITER", "PARAMETER_LIST"},
        {"epsilon"},
        {"STMT", "STMTS"},
        {"epsilon"},
        {"DECLSTMT"},
        {"LOOPSTMT"},
        {"ASSIGNSTMT"},
        {"FUNCALSTMT"},
        {"IOSTMT"},
        {"CONDSTMT"},
        {"RETSTMT"},
        {"TK_INT_KEYWORD", "TK_IDENTIFIER", "TK_SEM_DELIMITER"},
        {"TK_REAL_KEYWORD" , "TK_IDENTIFIER", "TK_SEM_DELIMITER"},
        {"TK_STRING_KEYWORD" , "TK_IDENTIFIER", "TK_SEM_DELIMITER"},
        {"TK_IDENTIFIER" , "TK_ASSIGN_OPERATOR", "ARITHEXP", "TK_SEM_DELIMITER"},
        {"TERM", "EXPPRIME"},
        {"LOWPOP", "TERM", "EXPPRIME"},
        {"epsilon"},
        {"FACTOR", "TERMPRIME" },
        {"HIGHPOP" , "FACTOR", "TERMPRIME"},
        {"epsilon"},
        {"TK_OP_DELIMITER", "ARITHEXP", "TK_CL_DELIMITER"},
        {"VAR"},
        {"TK_MUL_OPERATOR"},
        {"TK_DIV_OPERATOR"},
        {"TK_PLUS_OPERATOR"},
        {"TK_MINUS_OPERATOR"},
        {"TK_IDENTIFIER"},
        {"TK_INTEGER_LITERAL"},
        {"TK_FLOATING_POINT_LITERAL"},
        {"TK_STRING_LITERAL"},
        {"TK_LOOP_KEYWORD", "TK_OP_DELIMITER" , "BOOLEXP" , "TK_CL_DELIMITER" , "TK_FLOWERL_DELIMITER" , "STMTS", "TK_FLOWERR_DELIMITER"},
        {"TK_OP_DELIMITER", "BOOLEXP", "TK_CL_DELIMITER", "LOGOP", "TK_OP_DELIMITER" , "BOOLEXP", "TK_CL_DELIMITER"},
        {"TK_IDENTIFIER", "RELOP", "VAR"},
        {"TK_INTEGER_LITERAL", "RELOP", "VAR"},
        {"TK_FLOATING_POINT_LITERAL", "RELOP", "VAR"},
        {"TK_STRING_LITERAL", "RELOP", "VAR"},
        {"TK_LT_OPERATOR"},
        {"TK_LE_OPERATOR"},
        {"TK_EQ_OPERATOR"},
        {"TK_GE_OPERATOR"},
        {"TK_GT_OPERATOR"},
        {"TK_LOGICAL_AND_KEYWORD"},
        {"TK_LOGICAL_OR_KEYWORD"},
        {"TK_IF_KEYWORD" , "BOOLEXP", "TK_FLOWERL_DELIMITER" , "STMTS", "TK_FLOWERR_DELIMITER" , "CONDSTMTPRIME"},
        {"TK_ELSE_KEYWORD", "TK_FLOWERL_DELIMITER", "STMTS" , "TK_FLOWERR_DELIMITER"},
        {"epsilon"},
        {"TK_READ_KEYWORD", "TK_OP_DELIMITER", "TK_IDENTIFIER", "TK_CL_DELIMITER" , "TK_SEM_DELIMITER"},
        {"TK_WRITE_KEYWORD", "TK_OP_DELIMITER" , "VAR" , "TK_CL_DELIMITER" , "TK_SEM_DELIMITER"},
        {"OUTPUT_PARAM", "TK_FUNCTION_IDENTIFIER", "INPUT_PARAM", "TK_SEM_DELIMITER"},
        {"TK_SQL_DELIMITER", "IDLIST", "TK_SQR_DELIMITER", "TK_ASSIGN_OPERATOR"},
        {"TK_SQL_DELIMITER", "IDLIST", "TK_SQR_DELIMITER"},
        {"TK_IDENTIFIER", "MOREID"},
        {"TK_COMMA_DELIMITER", "IDLIST"},
        {"epsilon"},
        {"TK_RETURN_KEYWORD" , "OPRESTMT", "TK_SEM_DELIMITER"},
        {"TK_SQL_DELIMITER" , "IDLIST", "TK_SQR_DELIMITER"},
        {"epsilon"}
    };

    table = {{{"PROGRAM", "$"}, 0},
        {{"PROGRAM", "TK_GAP_KEYWORD"}, 1},
        {{"PROGRAM", "TK_FUNCTION_IDENTIFIER"}, 1},
        {{"MAINFUNC", "$"}, 0},
        {{"MAINFUNC", "TK_GAP_KEYWORD"}, 2},
        {{"OTHERFUNC", "TK_GAP_KEYWORD"}, 4},
        {{"OTHERFUNC", "TK_FUNCTION_IDENTIFIER"}, 3},
        {{"FUNCTION", "TK_GAP_KEYWORD"}, 0},
        {{"FUNCTION", "TK_FUNCTION_IDENTIFIER"}, 5},
        {{"INPUT_PAR", "TK_OUTPUT_KEYWORD"}, 0},
        {{"INPUT_PAR", "TK_GAP_KEYWORD"}, 0},
        {{"INPUT_PAR", "TK_FUNCTION_IDENTIFIER"}, 0},
        {{"INPUT_PAR", "TK_SEM_DELIMITER"}, 0},
        {{"INPUT_PAR", "TK_INPUT_KEYWORD"}, 6},
        {{"OUTPUT_PAR", "TK_SEM_DELIMITER"}, 8},
        {{"OUTPUT_PAR", "TK_OUTPUT_KEYWORD"}, 7},
        {{"PARAMETER_LIST", "TK_SQR_DELIMITER"}, 0},
        {{"PARAMETER_LIST", "TK_INT_KEYWORD"}, 9},
        {{"PARAMETER_LIST", "TK_REAL_KEYWORD"}, 9},
        {{"PARAMETER_LIST", "TK_STRING_KEYWORD"}, 9},
        {{"DATA_TYPE", "TK_IDENTIFIER"}, 0},
        {{"DATA_TYPE", "TK_INT_KEYWORD"}, 10},
        {{"DATA_TYPE", "TK_REAL_KEYWORD"}, 11},
        {{"DATA_TYPE", "TK_STRING_KEYWORD"}, 12},
        {{"REMAINING_LIST", "TK_SQR_DELIMITER"}, 14},
        {{"REMAINING_LIST", "TK_COMMA_DELIMITER"}, 13},
        {{"STMTS", "TK_FLOWERR_DELIMITER"}, 16},
        {{"STMTS", "TK_INT_KEYWORD"}, 15},
        {{"STMTS", "TK_REAL_KEYWORD"}, 15},
        {{"STMTS", "TK_STRING_KEYWORD"}, 15},
        {{"STMTS", "TK_LOOP_KEYWORD"}, 15},
        {{"STMTS", "TK_IDENTIFIER"}, 15},
        {{"STMTS", "TK_READ_KEYWORD"}, 15},
        {{"STMTS", "TK_WRITE_KEYWORD"}, 15},
        {{"STMTS", "TK_IF_KEYWORD"}, 15},
        {{"STMTS", "TK_RETURN_KEYWORD"}, 15},
        {{"STMTS", "TK_SQL_DELIMITER"}, 15},
        {{"STMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"STMT", "TK_INT_KEYWORD"}, 17},
        {{"STMT", "TK_REAL_KEYWORD"}, 17},
        {{"STMT", "TK_STRING_KEYWORD"}, 17},
        {{"STMT", "TK_LOOP_KEYWORD"}, 18},
        {{"STMT", "TK_IDENTIFIER"}, 19},
        {{"STMT", "TK_READ_KEYWORD"}, 21},
        {{"STMT", "TK_WRITE_KEYWORD"}, 21},
        {{"STMT", "TK_IF_KEYWORD"}, 22},
        {{"STMT", "TK_RETURN_KEYWORD"}, 23},
        {{"STMT", "TK_SQL_DELIMITER"}, 20},
        {{"DECLSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"DECLSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"DECLSTMT", "TK_IDENTIFIER"}, 0},
        {{"DECLSTMT", "TK_READ_KEYWORD"}, 0},
        {{"DECLSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"DECLSTMT", "TK_IF_KEYWORD"}, 0},
        {{"DECLSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"DECLSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"DECLSTMT", "TK_INT_KEYWORD"}, 24},
        {{"DECLSTMT", "TK_REAL_KEYWORD"}, 25},
        {{"DECLSTMT", "TK_STRING_KEYWORD"}, 26},
        {{"ASSIGNSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"ASSIGNSTMT", "TK_INT_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_READ_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_IF_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"ASSIGNSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"ASSIGNSTMT", "TK_IDENTIFIER"}, 27},
        {{"ARITHEXP", "TK_SEM_DELIMITER"}, 0},
        {{"ARITHEXP", "TK_CL_DELIMITER"}, 0},
        {{"ARITHEXP", "TK_OP_DELIMITER"}, 28},
        {{"ARITHEXP", "TK_IDENTIFIER"}, 28},
        {{"ARITHEXP", "TK_INTEGER_LITERAL"}, 28},
        {{"ARITHEXP", "TK_FLOATING_POINT_LITERAL"}, 28},
        {{"ARITHEXP", "TK_STRING_LITERAL"}, 28},
        {{"EXPPRIME", "TK_SEM_DELIMITER"}, 30},
        {{"EXPPRIME", "TK_CL_DELIMITER"}, 30},
        {{"EXPPRIME", "TK_PLUS_OPERATOR"}, 29},
        {{"EXPPRIME", "TK_MINUS_OPERATOR"}, 29},
        {{"TERM", "TK_SEM_DELIMITER"}, 0},
        {{"TERM", "TK_PLUS_OPERATOR"}, 0},
        {{"TERM", "TK_MINUS_OPERATOR"}, 0},
        {{"TERM", "TK_CL_DELIMITER"}, 0},
        {{"TERM", "TK_OP_DELIMITER"}, 31},
        {{"TERM", "TK_IDENTIFIER"}, 31},
        {{"TERM", "TK_INTEGER_LITERAL"}, 31},
        {{"TERM", "TK_FLOATING_POINT_LITERAL"}, 31},
        {{"TERM", "TK_STRING_LITERAL"}, 31},
        {{"TERMPRIME", "TK_SEM_DELIMITER"}, 33},
        {{"TERMPRIME", "TK_PLUS_OPERATOR"}, 33},
        {{"TERMPRIME", "TK_MINUS_OPERATOR"}, 33},
        {{"TERMPRIME", "TK_CL_DELIMITER"}, 33},
        {{"TERMPRIME", "TK_MUL_OPERATOR"}, 32},
        {{"TERMPRIME", "TK_DIV_OPERATOR"}, 32},
        {{"FACTOR", "TK_SEM_DELIMITER"}, 0},
        {{"FACTOR", "TK_PLUS_OPERATOR"}, 0},
        {{"FACTOR", "TK_MINUS_OPERATOR"}, 0},
        {{"FACTOR", "TK_MUL_OPERATOR"}, 0},
        {{"FACTOR", "TK_DIV_OPERATOR"}, 0},
        {{"FACTOR", "TK_CL_DELIMITER"}, 0},
        {{"FACTOR", "TK_OP_DELIMITER"}, 34},
        {{"FACTOR", "TK_IDENTIFIER"}, 35},
        {{"FACTOR", "TK_INTEGER_LITERAL"}, 35},
        {{"FACTOR", "TK_FLOATING_POINT_LITERAL"}, 35},
        {{"FACTOR", "TK_STRING_LITERAL"}, 35},
        {{"HIGHPOP", "TK_OP_DELIMITER"}, 0},
        {{"HIGHPOP", "TK_IDENTIFIER"}, 0},
        {{"HIGHPOP", "TK_INTEGER_LITERAL"}, 0},
        {{"HIGHPOP", "TK_FLOATING_POINT_LITERAL"}, 0},
        {{"HIGHPOP", "TK_STRING_LITERAL"}, 0},
        {{"HIGHPOP", "TK_MUL_OPERATOR"}, 36},
        {{"HIGHPOP", "TK_DIV_OPERATOR"}, 37},
        {{"LOWPOP", "TK_OP_DELIMITER"}, 0},
        {{"LOWPOP", "TK_IDENTIFIER"}, 0},
        {{"LOWPOP", "TK_INTEGER_LITERAL"}, 0},
        {{"LOWPOP", "TK_FLOATING_POINT_LITERAL"}, 0},
        {{"LOWPOP", "TK_STRING_LITERAL"}, 0},
        {{"LOWPOP", "TK_PLUS_OPERATOR"}, 38},
        {{"LOWPOP", "TK_MINUS_OPERATOR"}, 39},
        {{"VAR", "TK_SEM_DELIMITER"}, 0},
        {{"VAR", "TK_CL_DELIMITER"}, 0},
        {{"VAR", "TK_PLUS_OPERATOR"}, 0},
        {{"VAR", "TK_MINUS_OPERATOR"}, 0},
        {{"VAR", "TK_MUL_OPERATOR"}, 0},
        {{"VAR", "TK_DIV_OPERATOR"}, 0},
        {{"VAR", "TK_FLOWERL_DELIMITER"}, 0},
        {{"VAR", "TK_IDENTIFIER"}, 40},
        {{"VAR", "TK_INTEGER_LITERAL"}, 41},
        {{"VAR", "TK_FLOATING_POINT_LITERAL"}, 42},
        {{"VAR", "TK_STRING_LITERAL"}, 43},
        {{"LOOPSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"LOOPSTMT", "TK_INT_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_IDENTIFIER"}, 0},
        {{"LOOPSTMT", "TK_READ_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_IF_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"LOOPSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"LOOPSTMT", "TK_LOOP_KEYWORD"}, 44},
        {{"BOOLEXP", "TK_CL_DELIMITER"}, 0},
        {{"BOOLEXP", "TK_FLOWERL_DELIMITER"}, 0},
        {{"BOOLEXP", "TK_OP_DELIMITER"}, 45},
        {{"BOOLEXP", "TK_IDENTIFIER"}, 46},
        {{"BOOLEXP", "TK_INTEGER_LITERAL"}, 47},
        {{"BOOLEXP", "TK_FLOATING_POINT_LITERAL"}, 48},
        {{"BOOLEXP", "TK_STRING_LITERAL"}, 49},
        {{"RELOP", "TK_IDENTIFIER"}, 0},
        {{"RELOP", "TK_INTEGER_LITERAL"}, 0},
        {{"RELOP", "TK_FLOATING_POINT_LITERAL"}, 0},
        {{"RELOP", "TK_STRING_LITERAL"}, 0},
        {{"RELOP", "TK_LT_OPERATOR"}, 50},
        {{"RELOP", "TK_LE_OPERATOR"}, 51},
        {{"RELOP", "TK_EQ_OPERATOR"}, 52},
        {{"RELOP", "TK_GE_OPERATOR"}, 53},
        {{"RELOP", "TK_GT_OPERATOR"}, 54},
        {{"LOGOP", "TK_OP_DELIMITER"}, 0},
        {{"LOGOP", "TK_LOGICAL_AND_KEYWORD"}, 55},
        {{"LOGOP", "TK_LOGICAL_OR_KEYWORD"}, 56},
        {{"CONDSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"CONDSTMT", "TK_INT_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_IDENTIFIER"}, 0},
        {{"CONDSTMT", "TK_READ_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"CONDSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"CONDSTMT", "TK_IF_KEYWORD"}, 57},
        {{"CONDSTMTPRIME", "TK_FLOWERR_DELIMITER"}, 59},
        {{"CONDSTMTPRIME", "TK_INT_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_REAL_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_STRING_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_LOOP_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_IDENTIFIER"}, 59},
        {{"CONDSTMTPRIME", "TK_READ_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_WRITE_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_IF_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_RETURN_KEYWORD"}, 59},
        {{"CONDSTMTPRIME", "TK_SQL_DELIMITER"}, 59},
        {{"CONDSTMTPRIME", "TK_ELSE_KEYWORD"}, 58},
        {{"IOSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"IOSTMT", "TK_INT_KEYWORD"}, 0},
        {{"IOSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"IOSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"IOSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"IOSTMT", "TK_IDENTIFIER"}, 0},
        {{"IOSTMT", "TK_IF_KEYWORD"}, 0},
        {{"IOSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"IOSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"IOSTMT", "TK_READ_KEYWORD"}, 60},
        {{"IOSTMT", "TK_WRITE_KEYWORD"}, 61},
        {{"FUNCALSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"FUNCALSTMT", "TK_INT_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_IDENTIFIER"}, 0},
        {{"FUNCALSTMT", "TK_READ_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_IF_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_RETURN_KEYWORD"}, 0},
        {{"FUNCALSTMT", "TK_SQL_DELIMITER"}, 62},
        {{"OUTPUT_PARAM", "TK_FUNCTION_IDENTIFIER"}, 0},
        {{"OUTPUT_PARAM", "TK_SQL_DELIMITER"}, 63},
        {{"INPUT_PARAM", "TK_SEM_DELIMITER"}, 0},
        {{"INPUT_PARAM", "TK_SQL_DELIMITER"}, 64},
        {{"IDLIST", "TK_SQR_DELIMITER"}, 0},
        {{"IDLIST", "TK_IDENTIFIER"}, 65},
        {{"MOREID", "TK_SQR_DELIMITER"}, 67},
        {{"MOREID", "TK_COMMA_DELIMITER"}, 66},
        {{"RETSTMT", "TK_FLOWERR_DELIMITER"}, 0},
        {{"RETSTMT", "TK_INT_KEYWORD"}, 0},
        {{"RETSTMT", "TK_REAL_KEYWORD"}, 0},
        {{"RETSTMT", "TK_STRING_KEYWORD"}, 0},
        {{"RETSTMT", "TK_LOOP_KEYWORD"}, 0},
        {{"RETSTMT", "TK_IDENTIFIER"}, 0},
        {{"RETSTMT", "TK_READ_KEYWORD"}, 0},
        {{"RETSTMT", "TK_WRITE_KEYWORD"}, 0},
        {{"RETSTMT", "TK_IF_KEYWORD"}, 0},
        {{"RETSTMT", "TK_SQL_DELIMITER"}, 0},
        {{"RETSTMT", "TK_RETURN_KEYWORD"}, 68},
        {{"OPRESTMT", "TK_SEM_DELIMITER"}, 70},
        {{"OPRESTMT", "TK_SQL_DELIMITER"}, 69},
    };

    file.open("..\\output\\parseTree.txt");
}

/*
    * A utility function to print the input contents.
*/
void printInput(deque<pair<pair<string, string>, int> > &tokens)
{
    int sz = tokens.size();
    int k = min(3, sz);
    string output = "";
    for (int i = 0; i < k; i++) output += "(" + tokens[i].first.first + "," + tokens[i].first.second + ")";
    printf("%-110s", output.c_str());
}

/*
    * A utility function to print the stack contents.
*/
void printStack(stack<string> & s)
{
    int sz = s.size();
    int k = min(3, sz);
    vector<string> tmp(k);
    string output = "";
    for (int i = 0; i < k; i++)
    {
        tmp[i] = s.top();
        output += tmp[i];
        s.pop();
    }
    for (int i = k - 1; i >= 0; i--) s.push(tmp[i]);
    printf("%-82s", output.c_str());
}

/*
    * A utility function to print the parse tree contents.
*/
void printParseTree(string node, int level)
{
    for (int i = 0; i < level; i++)
        file << "    ";
    file << node << "\n";
}

/*
    * This function is called by the main to parse the input.
*/
void parse(deque<pair<pair<string, string>, int> > tokens)
{
    init();
    vector<vector<string>> parseTree(100000);
    parseTree[0].push_back("PROGRAM");
    stack<pair<string, int>> tree_stack;
    tree_stack.push({"PROGRAM", 0});
    stack<string> s;
    s.push("$");
    s.push("PROGRAM");

    int lineerr = -1;
    int check = 0;
    vector<pair<int, string> >lines;
    vector<pair<int, string> >lines2;

    printf("%-110s%-82s%s\n", "Input", "Stack", "Action");
    cout << "===================================================================================================================================================================================================================\n";
    while (1)
    {
        string top = s.top();
        if (top == "epsilon")
        {
            printParseTree(tree_stack.top().first, tree_stack.top().second);
            tree_stack.pop();
            s.pop();
            continue;
        }

        printInput(tokens);
        printStack(s);

        pair<pair<string, string>, int> tmp = tokens.front();
        string token = tmp.first.first, lexeme = tmp.first.second;
        int line = tmp.second;

        if (top == token)
        {
            if (top == "$")
            {
                break;
            }

            printParseTree(tree_stack.top().first, tree_stack.top().second);
            tree_stack.pop();
            s.pop();
            tokens.pop_front();
            cout << "Pop" << endl;
        }
        else if (table.count(make_pair(top, token)))
        {
            string left = tree_stack.top().first;
            int level = tree_stack.top().second;

            printParseTree(tree_stack.top().first, tree_stack.top().second);
            tree_stack.pop();
            s.pop();
            if (table[make_pair(top, token)] == 0)
            {
                cout << "SYNCH, line# " << tokens.front().second << endl;
                lines2.push_back({tokens.front().second, top});
                check = 1;
                continue;
            }
            stack<string>temp;
            cout << "Rule " << table[make_pair(top, token)] << endl;
            for (auto it : rules[table[make_pair(top, token)]])
            {
                parseTree[level + 1].push_back(it);
                temp.push(it);
            }
            while (!temp.empty())
            {
                s.push(temp.top());
                tree_stack.push({temp.top(), level + 1});
                temp.pop();
            }
        }
        else if (lexeme == "$")
        {
            if (top != "$") check = 3;
            else check = 1;
            break;
        }
        else if (top == "$")
        {
            lineerr = line;
            check = 2;
            break;
        }
        else
        {
            cout << "SKIP, line# " << tokens.front().second << endl;
            lines.push_back({tokens.front().second, lexeme});
            check = 1;
            tokens.pop_front();
        }
    }
    file.close();

    if (check)
    {
        cout << "\n\nErrors found in the input.\n";
        for (auto it : lines)
            cout << endl << "Line " << it.first << ": " << "Error " << it.second << endl;
        for (auto it : lines2)
            cout << endl << "Line " << it.first << ": " << "missing " << it.second << endl;
        if (check == 2)
            cout << endl << "line " << lineerr << " onwards not expected" << endl;
        if (check == 3)
            cout << "Line " << tokens.front().second << ": " << "Error Incomplete Program\n";
    }
    else
        cout << endl << "\nCorrect input, no errors found." << endl;

    cout << "\n\nLevel Order Traversal of the Parse Tree:\n";
    for (int i = 0; i < 100; i++)
    {
        if (parseTree[i].size())
        {
            cout << "Level " << i << " -> ";
            for (auto j : parseTree[i]) cout << j << " ";
            cout << "\n";
        }
    }
}