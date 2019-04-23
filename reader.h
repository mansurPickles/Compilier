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
using namespace std;

void run(string fname){

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

        //NEED TO DO

        //syntaxAnalyzer (vector<Token> vt);

        //string S = "A+B=C$"


    }

    f.close();
}

#endif // READER_H
