#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>
#include <iomanip>
#include "constvalues.h"
using namespace std;



class Token{
private:
    string content;
    string type;
//    int integer;

public:
    Token(string input, string type){
        content = input;
        this->type = type;
    }

    string getContent(){
        return content;
    }


    string getType(){
        return type;
    }

    friend ostream& operator<<(ostream& out, const Token& tk);

};



ostream& operator<<(ostream& out, const Token& tk){


out << left << setw(SPACING) << tk.type  << left  << setw(SPACING) << "="  << left << setw(SPACING) << tk.content << endl;

return out;
};


#endif // TOKEN_H
