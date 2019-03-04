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


    while(!f.eof())
    {

        getline(f,str);
        stateMachine(str);
    }

    f.close();
}

#endif // READER_H
