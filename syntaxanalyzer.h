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
const vector<string> TERMINALROW = {"*","+","-","/","(",")","id","$"};


bool ruleS(stack<string> & s1, vector<Token> & tk, int &index);

bool ruleE(stack<string> & s1, vector<Token> & tk, int &index);


int predictiveTable [F+1][DOLLAR+1];



//bool ruleQ(stack<string> & s1, vector<Token> & tk, int &index);

//bool ruleT(stack<string> & s1, vector<Token> & tk, int &index);

//bool ruleR(stack<string> & s1, vector<Token> & tk, int &index);

//bool ruleF(stack<string> & s1, vector<Token> & tk, int &index);

int convertNonterminaltoInt(string str){
    int index = -1;

    for (int i=0; i< CAPROW.size(); i++){
        if (str.at(0) == CAPROW.at(i)){
            index = i;
            return i;
        }
    }
    return index;
}
int convertTokenInputtoRow(Token tk){
    string str = tk.getType();
    char iCheck = str.at(0);

    if (isalpha(iCheck)){
        return 6;
    }

    else {

        int index = -1;
        for (int i=0; i< TERMINALROW.size(); i++){
            if (str == TERMINALROW.at(i)){
                return i;
            }
        }

        return index;
    }
}
void reverseInputStack(stack<string> &s1, string str){
    for (int i=str.size()-1; i>= 0; i--){
        s1.push(str.substr(i,1));
        cout << "pushed " << str.substr(i,1) << endl;
    }
}

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

void showstack(stack <string> s)
{

    cout << "\nPRINTING CURRENT STACK\n";
    while (!s.empty())
    {
        cout <<  s.top() << endl;
        s.pop();
    }
    cout << '\n';
}

bool syntaxAnalyzer(vector<Token> tk) {

    int index = 0;
    bool result = false;
    stack<string> s1;
    int size = tk.size();

    if (tk.size() == 0){
        return true;
    }

    //init stack by pushing $ and S
    s1.push("$");
    s1.push("S");
    showstack(s1);

    //get the predictive table row from stack
    int rowLookUp = convertNonterminaltoInt(s1.top());
    s1.pop();       //now pop it

    //get the predictive table column from token (input)
    int columnLookup = convertTokenInputtoRow(tk.at(index));

    //print it (DEBUG ONLY)
    cout << "row " << rowLookUp << " column " << columnLookup << endl;

    //rule number to apply
    int temprule = predictiveTable[rowLookUp][columnLookup];

    cout << "rule " << productionRules.at(temprule) << endl;

    //add the rule to the stack in reverse order
    reverseInputStack(s1, productionRules.at(temprule));
    showstack(s1);

    return true;


    //now messing with stack

    cout << "end of token :" << tk.at(tk.size()-1).getContent() << endl;

    if (tk.at(tk.size()-1).getContent() != "$"){
        tk.push_back(Token("$", "$"));
    }

}




//bool rulesS(stack<string> & s1, vector<Token> & tk, int &index){
//    string str = s1.top();
//    string tokenContent = tk.at(index).getContent();
//    char iCheck = char(tokenContent.at(0));

//    if (isalpha(iCheck) && s1.top() == "i"){
//        s1.pop();
//        index++;
//    }

//    if (tokenContent == tk.at(index).getContent()){
//        s1.pop();
//        index++;
//    }

//    if (tokenContent == "E"){
//        s1.pop();
//        return ruleE(s1, tk, index);
//    }

//    else {
//        return false;
//    }
//}

//bool rulesE(stack<string> & s1, vector<Token> & tk, int &index){
//    string str = s1.top();
//    string tokenContent = tk.at(index).getContent();
//    char iCheck = char(tokenContent.at(0));

//    if (tokenContent == "("){
//        s1.pop();
//    }

//    if (isalpha(iCheck) && s1.top() == "i"){

//    }

//    return false;
//}
#endif // SYNTAXANALYZER_H
