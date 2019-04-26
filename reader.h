#ifndef READER_H
#define READER_H
#include <iostream>
#include <iomanip>
#include "constvalues.h"
#include "lexanalyzer.h"
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "token.h"
#include "syntaxanalyzer.h"
using namespace std;

void run(string fname){

    initPredictableTable();

    //init 2d Array and Vectprs
    initArray();

    ifstream f(fname.c_str());

    if (!f.is_open()){
        perror("open failed");
        exit(-1);
    }

    string str = "";
    cout  << left << setw(SPACING) << "TOKENS" << left << setw(SPACING) << "=" << left << setw(SPACING) << "Lexemes" << endl << endl;

    //main loop
    while(!f.eof())
    {

        getline(f,str);
        vector<Token> tk = stateMachine(str);
        Token temp ("$", "$");
        tk.push_back(temp);

        cout << "after getline\n";

        for (int i=0; i< tk.size(); i++){
            cout << tk.at(i) << "\n";
        }

        if (syntaxAnalyzer(tk) == true){
            cout << "accepted\n";
        }

        else{
            cout << "failed\n";
        }

        //NEED TO DO

//        syntaxAnalyzer (tk);

        //string S = "A+B=C$"


    }

    f.close();
}

#endif // READER_H
