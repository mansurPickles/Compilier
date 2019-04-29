#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include <iostream>
#include <iomanip>
#include "constvalues.h"
#include <iomanip>
#include <vector>
#include <string>
#include "token.h"



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
vector <Token> stateMachine(string str);
string convertToString(int state, string str);

Token printAndCheck(string result, char c, int state);

int stateFunctionTable [ROWLENGTH][COLUMNLENGTH];
vector<string> keywords;
vector<string> separator;
vector<string> operators;

//start FUNCTIONS

void initArray(){

    //set 2d array to all fail states
    for (int i=0; i< ROWLENGTH; i++){
        for (int j=0; j< COLUMNLENGTH; j++){
            markEntry(i,j,FAILED);
        }
    }

    //marking success states
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

    //init vectors
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
    separator.push_back("\n");

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

    //all valid states
    else if (state==NUM || state==ALPHA || state==REG || state==DOT){

        //KEYWORD
        if (isKeyword(str)){
            return "KEYWORD";
        }

        //DOUBLE
        if (state==DOT){
            return "REAL";
        }

        //INTEGER checks to see if state is NUM and if the first char in the string is a number
        if (state==NUM && isnumber(str.at(0)) ){
            return "INTEGER";
        }

        //ID
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
vector <Token> stateMachine(string str){
    vector<Token> vt;
    int size = str.size();
    int state = 0;      //set init state = 0

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

        //end the state machine when finding a seperator or operator
        else if(isSeparator(string(1,c)) || isOperator(string(1,c))){

            //print result
            Token temp = printAndCheck(result,c,state);

            if(temp.getType() != "FAILED"){
                vt.push_back(temp);
            }


            //reset state and result
            state = 0;
            result = "";
        }

        //if DOT
        else if(c=='.'){
            state = stateFunctionTable[state][DOT];
            result+=c;
        }


        //keep running the state machine and add it to result(string)
        else {
            int conversion = getType(c);
            state = stateFunctionTable[state][conversion];

            //remove all unnecessary spaces
            if (c!=' ' && c!='\t' && c!='\n'){
                result+=c;
            }
        }

    }

    if (state!= FAILED){
        Token temp = printAndCheck(result, ' ',  state);

        if(temp.getType() != "FAILED"){
            vt.push_back(temp);
        }
    }

    return vt;
}

Token printAndCheck(string result, char c, int state){
    if (state!= FAILED){

        //if its not a comment print
        if (state!=COMMENT){
            Token tk (result,convertToString(state, result));
            cout << tk;
            return tk;
            //            cout << left << setw(SPACING) << convertToString(state, result)  <<left <<  setw(SPACING) << "="  << left << setw(SPACING) << result << endl;
        }

        //if its a seperator print that after
        if (c != ' ' && isSeparator(string(1,c))){

            if (c==';'){
                Token tk ("$", "$");
                return tk;

            }
            else {
                Token tk (string(1,c), "SEPERATOR");
                cout << tk;
                return tk;

                //            cout  << left << setw(SPACING) << "SEPERATOR"  << left << setw(SPACING) << "="   << left << setw(SPACING) << c << endl;

            }
        }

        //if its an operator print that after
        if (c != ' ' && isOperator(string(1,c))){

            Token tk (string(1,c), "OPERATOR");
            cout << tk;
            return tk;
            //            cout  << left << setw(SPACING) << "OPERATOR" << left << setw(SPACING) << "=" << left << setw(SPACING) << c << endl;

        }

    }

    else {
        cout << "failed state\n";
        Token tk ("FAILED", "FAILED");
        return tk;
    }

    Token tk ("FAILED", "FAILED");
    return tk;
}

#endif // LEXANALYZER_H
