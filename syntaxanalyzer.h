#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#include <iostream>
#include <iomanip>
#include "constvalues.h"
#include <iomanip>
#include <vector>
#include <string>
#include "token.h"
#include <stack>

using namespace std;

int const FAIL = 0;
int const S = 0;
int const E = 1;
int const Q = 2;
int const T = 3;
int const R = 4;
int const F = 5;
int const STAR = 0;
int const PLUS = 1;
int const MINUS = 2;
int const DIV = 3;
int const LEFTB = 4;
int const RIGHTB = 5;
int const ID = 6;
int const DOLLAR = 7;
const vector<char> CAPROW = {'S','E','Q','T','R','F'};




int predictiveTable [F+1][DOLLAR+1];

void initPredictableTable(){
    for (int i=0; i< F+1; i++){
        for (int j=0; j< DOLLAR+1; j++){
            predictiveTable[i][j] = FAIL;
        }
    }

    ////table entry 1 [S]['i'] E->i=E
    predictiveTable[S][ID] = 1;

    ///table entry 2 [E]['('] E->TQ
    predictiveTable[E][LEFTB] = 2;

    ///table entry 3 [E]['i'] E-> TQ
    predictiveTable[E][ID] = 2;

    ///table entry 4 [Q]['+'] Q -> +TQ
    predictiveTable[Q][PLUS] = 3;

    ///table entry 5 [Q]['-']Q -> -TQ
    predictiveTable[Q][MINUS] = 4;

    ///table entry 6[Q][')'] Q ->epsilon
    predictiveTable[Q][RIGHTB] = 5;

    ///table entry 7[Q]['$'] Q -> epsilon
    predictiveTable[Q][DOLLAR] = 5;

    ///table entry 8 [T][(] T- > FR
    predictiveTable[T][LEFTB] = 6;

    //// table entry 9 [T][i] T -> FR
    predictiveTable[T][ID] = 6;

    ////table entry 10 [R][*] R -> *FR
    predictiveTable[R][STAR] = 7;


    ////table entry 10 [R][+] R -> epsilon
    predictiveTable[R][PLUS] = 9;

    ////table entry 11[R][-] R -> epsilon
    predictiveTable[R][MINUS] = 9;


    ////table entry 12 [R][/] R -> /FR
    predictiveTable[R][DIV] = 8;

    ////table entry 12[R][)] R -> epsilon
    predictiveTable[R][RIGHTB] = 9;

    ////table entry 13 [R][$] R -> epsilon
    predictiveTable[R][DOLLAR] = 9;

    ////table entry 14 [F][(E)] F -> (E)
    predictiveTable[F][LEFTB] = 10;

    ////table entry 14[F][i] F -> i
    predictiveTable[F][ID] = 11;


}

void printPredictionTable(){
    cout << setw(10) << left<< " ";
    cout << setw(10) << left<< "*";
    cout << setw(10) << left<< "+";
    cout << setw(10) << left<< "-";
    cout << setw(10) << left<< "/";
    cout << setw(10) << left<< "(";
    cout << setw(10) << left<< ")";
    cout << setw(10) << left<< "id";
    cout << setw(10) << left<< "$";
    cout << endl;



    for (int i=0; i< F+1; i++){
        cout << setw(10) << left<< CAPROW.at(i);

        for (int j=0; j< DOLLAR+1; j++){
            int rule;
            rule = predictiveTable[i][j];
            //            cout << setw(3) << left << rule << " ";
            cout << setw(10) << left<< productionRules.at(rule);

        }
        cout << endl;
    }
}

bool syntaxAnalyzer(vector<Token> tk){
    bool result = false;
    stack<char> s1;
    int size = tk.size();
    s1.push('$');
    s1.push('S');
    int index = 0;
    while(!s1.empty()){
        if (s1.top()=='$' && tk.at(index).getContent()=="$"){
            result = true;
            return result;
        }
    }


}


#endif // SYNTAXANALYZER_H
