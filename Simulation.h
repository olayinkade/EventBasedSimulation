//
// Created by OBTAdelakun on 3/21/2017.
//

#ifndef A22150_SIMULATION_H
#define A22150_SIMULATION_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;
class PriorityQueue;
class Queue;
class Process;
class Simulation {
private:
    static PriorityQueue * event;
    static  Queue * Cpu, *IODevice1,*IODevice2, *processes;
    static  std::ifstream * opener;


public:
    static void getnextArrival();
    static void intializer(std::ifstream * open);
    static bool Cpufree();
    static bool IODevice1free();
    static bool IODevice2free();

    static void  startCpuEnq(int time ,Process * level);
    static void  timeoutEnq(int time ,Process * level);
    static void CompleteCPUEnq(int time ,Process *level);
    static void StartIODevice1Enq(int time ,Process *level);
    static void StartIODevice2Enq(int time ,Process *level);
    static void CompleteIODevice1Enq(int time ,Process *level);
    static void CompleteIODevice2Enq(int time ,Process *level);
    static void printAll();
    static void exitEnq(int time,Process * process);
    static Queue * getCPU();
    static Queue * getIODevice1();
    static Queue * getIODevice2();
    static Queue * getprocesses();

};


#endif //A22150_SIMULATION_H
