#ifndef A22150_PROCESS_H
#define A22150_PROCESS_H

#include "Obj.h"
class Queue;

class Process : public Obj{
private:
    int id;
    int arrival;
    int total;
    int exit;
    int cpu;
    int dev1;
    int dev2;
    Queue * list;

public:
    Process();
    ~Process();
    Queue * getList();
    void calculate();
    int getArrival();
    int getCpu();
    int getDev1();
    int getDev2();
    int getTotal();
    void setTotal(int );
    int getExit();
    int getID();
    void setArrival(int);
    void setID(int);
    void setExit(int );
    void print();

};


#endif //A22150_PROCESS_H
