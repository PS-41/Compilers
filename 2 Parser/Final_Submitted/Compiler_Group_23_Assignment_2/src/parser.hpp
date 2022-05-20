/*
Group Number  --> 23
Names and IDs --> 1. Garvit Soni                2017B3A70458H
                  2. Aman Badjate               2017B3A70559H
                  3. Prakhar Suryavansh         2017B4A71017H
*/

#include <bits/stdc++.h>
using namespace std;

void init();
void printInput(deque<pair<pair<string, string>, int> > &tokens);
void printStack(stack<string> & s);
void printParseTree(string node, int level);
void parse(deque<pair<pair<string, string>, int> > tokens);
