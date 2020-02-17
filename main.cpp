
//-----------------------------------------
// NAME		: Adelakun Olayinka
// STUDENT NUMBER	: 7790020
// COURSE		: COMP 2150
// INSTRUCTOR	: Gord Boyer
// ASSIGNMENT	: assignment 2
// QUESTION	: question 1
//
// REMARKS:discrete-event simulation to simulate the operation of a multiprogramming Operating System.
//
//
//-----------------------------------------

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Simulation.h"

using namespace std;


int main(int argc, char *argv[]){
    static ifstream infile;
    if(argc < 2){
        cout << "Usage: " << argv[0] << " <file name>\n";
        exit(1);
    }

    cout << "Simulation begins...\n";
    infile.open(argv[1]);
    Simulation::intializer(&infile);
    Simulation::printAll();
    infile.close();
    cout << "\nEnd of processing.\n";
    return 0;
}// main


