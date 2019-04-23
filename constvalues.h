#ifndef CONSTVALUES_H
#define CONSTVALUES_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

int const ROWLENGTH = 10;
int const COLUMNLENGTH = 10;
int const ALPHA = 1;
int const NUM = 2;
int const OPERATOR = 3;
int const SPACE = 4;
int const DOT = 5;
int const REG = 6;
int const COMMA = 7;
int const FAILED = 9;
int const COMMENT = 0;

int const SEPERATOR = 11;
int const REAL = 12;
int const IDENTIFIER  = 13;
int const KEYWORD = 14;
int const INTEGER = 15;

int const SPACING = 20;
int const SMALLSPACING = 10;

vector<string> productionRules;


string const rule0 = "FAILED";
string const rule1 = "i=e";
string const rule2 = "TQ";
string const rule3 = "+TQ";
string const rule4 = "-TQ";
string const rule5 = "epsilon";
string const rule6 = "FR";
string const rule7 = "*FR";
string const rule8 = "/FR";
string const rule9 = "epsilon";
string const rule10 = "(E)";
string const rule11 = "i";





#endif // CONSTVALUES_H
