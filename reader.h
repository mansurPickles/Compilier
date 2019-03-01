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
    initArray();

    ifstream f(fname.c_str());

    if (!f.is_open()){
        perror("open failed");
        exit(-1);
    }

    string str = "";

    while(!f.eof())
    {

        getline(f,str);
        stateMachine(str);
    }

    f.close();
}

#endif // READER_H
