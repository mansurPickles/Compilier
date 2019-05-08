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

    if (debug){
        printPredictionTable();
        sleep(2);
    }

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
        string str2;
        
        if (project2){
            for (int i=0; i<str.size(); i++){

                if (!isalpha(str.at(i))){
                    str2 += " ";
                }
                str2 += str.at(i);
            }
            str = str2;
        }
        vector<Token> tk = stateMachine(str);

        Token temp ("$", "$");
        tk.push_back(temp);

        if (debug){
            cout << "after getline\n";

            for (int i=0; i< tk.size(); i++){
                cout << tk.at(i) << "\n";
            }
        }

        if (syntaxAnalyzer(tk) == true){

            cout << "\n======================" << "ACCEPTED======================\n\n";
        }

        else{
            exit (-1);
            cout << "failed\n";
        }

    }

    f.close();
}

#endif // READER_H
