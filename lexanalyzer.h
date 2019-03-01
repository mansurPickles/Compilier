#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include <iostream>
#include <iomanip>
#include "constvalues.h"
#include <iomanip>
#include <vector>
#include <string>


void markEntry(int x, int y, int mark);
void initArray();
void printTable();
void initKeywords();
void initOperators();
void initSeparator();
int getType (char c);
bool isKeyword(string str);
bool isSeparator(string str);
bool isOperator(string str);
void stateMachine(string str);
string convertToString(int state, string str);

void printAndCheck(string result, char c, int state);

int stateFunctionTable [ROWLENGTH][COLUMNLENGTH];
vector<string> keywords;
vector<string> separator;
vector<string> operators;

//start FUNCTIONS

void initArray(){
    for (int i=0; i< ROWLENGTH; i++){
        for (int j=0; j< COLUMNLENGTH; j++){
            markEntry(i,j,FAILED);
        }
    }

    markEntry(0,ALPHA, ALPHA);
    markEntry(ALPHA,NUM,NUM);
    markEntry(0,NUM, NUM);
    markEntry(0,OPERATOR, OPERATOR);
    markEntry(0, SPACE, SPACE);
    markEntry(0,COMMENT, COMMENT);
    markEntry(0,REG, REG);
    markEntry(DOT,DOT,DOT);
    markEntry(ALPHA,REG,REG);
    markEntry(NUM,REG,REG);
    markEntry(NUM,DOT,DOT);

    markEntry(ALPHA,ALPHA,ALPHA);
    markEntry(NUM, NUM, NUM);
    markEntry(OPERATOR, OPERATOR, OPERATOR);
    markEntry(SPACE, SPACE, SPACE);
    markEntry(REG,REG, REG);
    markEntry(DOT,NUM,DOT);


    initKeywords();
    initSeparator();
    initOperators();
};

void initKeywords(){

    keywords.push_back("int");
    keywords.push_back("float");
    keywords.push_back("if");
    keywords.push_back("else");
    keywords.push_back("then");
    keywords.push_back("do");
    keywords.push_back("while");
    keywords.push_back("whileend");
    keywords.push_back("do");
    keywords.push_back("doend");
    keywords.push_back("for");
    keywords.push_back("and");
    keywords.push_back("or");
    keywords.push_back("function");
}
void initOperators(){


    operators.push_back("*");
    operators.push_back("+");
    operators.push_back("-");
    operators.push_back("=");
    operators.push_back("/");
    operators.push_back(">");
    operators.push_back("<");
    operators.push_back("%");
}
void initSeparator(){
    separator.push_back("'");
    separator.push_back("(");
    separator.push_back(")");
    separator.push_back("{");
    separator.push_back("}");
    separator.push_back("[");
    separator.push_back("]");
    separator.push_back(",");
    //    separator.push_back(".");
    separator.push_back(":");
    separator.push_back(";");
    separator.push_back("!");
    separator.push_back(" ");
    separator.push_back("sp");
    separator.push_back("(space)");

}
void printTable(){
    for (int i=0; i< ROWLENGTH; i++){
        for (int j=0; j< COLUMNLENGTH; j++){
            cout << setw(5) << stateFunctionTable[i][j];
        }
        cout << endl;
    }
}

void markEntry(int x, int y, int mark){
    stateFunctionTable[x][y] = mark;
}

bool isKeyword(string str){
    bool result = false;
    int size = keywords.size();

    for (int i=0; i< size; i++){
        if (str==keywords.at(i)){
            result = true;
            return result;
        }
    }

    return result;
}

bool isSeparator(string str){
    int size = separator.size();
    bool result = false;

    for (int i=0; i< size; i++){
        if (str==separator.at(i)){
            result = true;
            return result;
        }
    }

    return result;

}

bool isOperator(string str){
    int size = operators.size();
    bool result = false;

    for (int i=0; i< size; i++){
        if (str==operators.at(i)){
            result = true;
            return result;
        }
    }

    return result;
}
int getType (char c){
    if (c=='!'){
        return COMMENT;
    }

    if (isalpha(c)){
        return ALPHA;
    }

    if (isnumber(c)){
        return NUM;
    }

    if (isSeparator(string(1,c))){
        return OPERATOR;
    }

    if (isOperator(string(1,c))){
        return OPERATOR;
    }

    if (c == ' '){
        return SPACE;
    }

    if (c =='$'){
        return REG;
    }

    else{
        return 0;
    }
}
string convertToString(int state, string str){

    if (state==COMMENT){
        return "COMMENT";
    }

    else if (state==NUM || state==ALPHA || state==REG || state==DOT){
        if (isKeyword(str)){
            return "KEYWORD";
        }

        else {
            return "IDENTIFIER";
        }
    }

    else if (state==OPERATOR){
        return "OPEARATOR";
    }

    else if(state==COMMENT){
        return "COMMENT";
    }

    else {
        return "UNKNWON";
    }

}
void stateMachine(string str){
    int size = str.size();
    int state = 0;

    string result = "";

    for (int i=0; i< size; i++){
        char c = str.at(i);


        //remove comments
        if (c=='!'){
            c = str.at(++i);

            while(c !='!'){
                result+=c;
                c = str.at(++i);
            }
        }

        else if(isSeparator(string(1,c)) || isOperator(string(1,c))){

            printAndCheck(result,c,state);
            state = 0;
            result.clear();
        }

        //if DOT
        else if(c=='.'){
            state = stateFunctionTable[state][DOT];
            result+=c;
        }



        else {
            int conversion = getType(c);
            state = stateFunctionTable[state][conversion];
//                        cout << "type\t" << conversion << "\t" << c << "\t" << "state: " << state << endl;
            result+=c;
        }


    }

    if (state!= FAILED){
        printAndCheck(result, ' ',  state);
    }
}

void printAndCheck(string result, char c, int state){
    if (state!= FAILED){

        if (state!=COMMENT)
            cout <<"STATE: " << setw(SPACING) << convertToString(state, result) << setw(SPACING) << result << endl;

        if (c != ' ' && isSeparator(string(1,c))){
            cout  <<"STATE: " << setw(SPACING) << "SEPERATOR" << setw(SPACING) << c << endl;

        }

        if (c != ' ' && isOperator(string(1,c))){
            cout  <<"STATE: " << setw(SPACING) << "OPERATOR" << setw(SPACING) << c << endl;

        }
    }

    else {
        cout << "failed state\n";
    }
}

#endif // LEXANALYZER_H
