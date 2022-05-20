/*
Group Number  --> 4
Names and IDs --> 1. Shubham Jain				2016A7PS0043P
				  2. Girinath R.   				2016A7PS0018P
				  3. Smith Rajeshkumar Shah     2016A7PS0039P
*/

#include"lexer.h"
#include"parser.h"
#include "AST.h"
#include<time.h>
#include "symbolTable.h"
#include "semanticAnalyzer.h"


int main(int argc,char** argv){
    /*if(argc!=3)
    {
        printf("Error in the Command Line Arguments");
        return -1;
    }*/
    Grammar grm = StoreGrammarInStructures("grammar.txt");
    FirstAndFollow sets = AutomatedFirstFollowFind(grm);
    ParseTable table = (ParseTable)malloc(sizeof(struct parseTable));
    createParseTable(grm,sets,table);
    clock_t start_time, end_time;
    double total_CPU_time, total_CPU_time_in_seconds;
    int option;
    while(1)
    {
        ParseTree p1;
        printf("Press 0 to stop execution\n");
        printf("Press 1 to print comment free code to file\n");
        printf("Press 2 to print the token list on the console\n");        
        printf("Press 3 to print all lexical and syntax errors(with line numbers) on console and to print the parse tree in the file\n");
        printf("Press 4 to print the total time taken by the code of lexer and parser to verify the syntactic correctness\n");
        printf("Enter the option to be selected:");
        scanf("%d",&option);
        getchar();
        if(option==0)
            break;
        switch(option)
        {
            case 1:
                printf("\n\n\t\tPrinting Comment Free Code to File cleanSourceCode.txt\n\n\n");
                //removeComments(argv[1],"cleanSourceCode.txt");
                printf("\n\n\t\tComment Free Code printed to File cleanSourceCode.txt\n\n\n");
                break;
            case 2:
                printf("\n\n\t\tPrinting all the tokens to console\n\n\n");
                //printAllTokens(argv[1]);
                printf("\n\n\t\tFinished printing tokens\n\n\n");
                break;
            case 3:
                //Parser will invoke the lexer
                printf("\n\n\t\tParsing the file & Printing the Syntax and Lexical Errors if any\n\n\n");
                //p1 = parseCodeandPrintErrors(argv[1],table);
                p1 = parseCodeandPrintErrors("testcase1.txt",table);
                //printParseTree(p1,argv[2]);
                printParseTree(p1,"outputfile.txt");
                ASTree x = createAST(p1);
                printASTree(x);
                print_compression_ratio(p1,x);
                SymbTabTreeRoot b = constructSymbTabs(x);
                semantic_analyzer(x);
                break;
            case 4:
                start_time = clock();
                p1 = parseCodeandPrintErrors(argv[1],table);
                end_time = clock();
                total_CPU_time  =  (double) (end_time - start_time);
                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;
                printf("Total CPU time elapsed: %f\n",total_CPU_time);
                printf("Total CPU time elapsed in seconds: %f\n\n\n\n",total_CPU_time_in_seconds);
                break;
            default:
                printf("\n\nWrong Option Selected. Please select again\n\n\n\n");
                break;
        }
    }
    return 0;
}