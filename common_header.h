#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <fstream>
#include <string>
#include <queue>
#include <set>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <list>
#include <cctype>
#include <functional>
#include <iomanip>

#define maxnum 50
#define Terminator 1
#define NonTerminator 0
#define Table_width 20
using namespace std;

int indexOfNonT(char x);

int indexOfTerm(char x);


int indexOf(const vector<char>& v, char x);

void add_unique_item(vector<char>& f, char c);

int typeOf(char x);

void analyze(const char* str, int len = -1);

void input_grammar();
void pick_up();
void getFirstN();
void getFirstP();
void getFollow();
void generateTable(); 
void eliminateLeftRecursion();
void printAllTerminator();
void printAllNonTerminator();
void printAllFirstN();
void printAllFirstP();
void printAllFollow();
void printTable();
void saveAllInfoToFile();
void inputTitle();
#pragma once
