/*
Group Number  --> 23
Names and IDs --> 1. Garvit	Soni			    2017B3A70458H
				  2. Aman Badjate   		    2017B3A70559H
				  3. Prakhar Suryavansh         2017B4A71017H
*/

#include "lexer.hpp"
#include "parser.hpp"

int main(int argc, char *argv[])
{
    parse(generateAllTokens(argv[1]));
    return 0;
}