#include <iostream>
#include <iomanip>
#include "lexanalyzer.h"
#include <iomanip>
#include <constvalues.h>

using namespace std;

int main()
{
initArray();
printTable();

string str = "seperate this please 123 ! ! int abc$ 32.0111";

//for (int i=0; i< str.size(); i++){
//    cout << str.at(i) << " " <<getType(str.at(i)) << endl;
//}
stateMachine(str);
cout << "f1inished\n\n\n";

}
