// CLASS: Process
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: helps to store bursts
//id, arrival , exit time, total of all bursts
//total cpu, total dev1 , total dev2 of a process
//-----------------------------------------

#include "Process.h"
#include "Queue.h"

Process::Process(){
    id = 0;// id of the process
    arrival =0;// arrival time of the process
    total =0;// sum of all burst
    exit =0;// time process exited from the eventlist
    cpu=0;  // sum of all cpu times
    dev1 =0;// sum of all IODevice1 time
    dev2=0; //sum of all IODevice2 time
    list = new Queue();

}

Process::~Process(){
    list->~Queue();
}

// acessors and mutators
Queue *  Process::getList(){ return list; }
int Process::getCpu(){ return cpu;}
int Process::getDev1(){ return dev1;}
int Process::getDev2(){ return dev2;}
int Process::getArrival(){ return arrival; }
int Process::getID(){ return id; }
int Process::getExit(){ return exit; }
void Process::setArrival(int x){ arrival= x; }
void Process::setTotal(int x){ total= x; }
void Process::setExit(int x){ exit= x; }
int Process::getTotal(){ return total; }
void Process::setID(int x){ id= x;}


void Process::print(){
    list->print();
}
/*****************************************************
 * calculate function takes all burst and sets cpu , dev1,
 * dev2 summations
 *****************************************************/

void Process::calculate(){
    int count =0;
    Obj * curr =NULL ;
    list->top();
    do{
        curr = list->scan();
        IntItem * holder = dynamic_cast<IntItem *>(curr);
        if(count % 2 == 0){
            cpu += holder->getInt();
        }
        else{
            if(holder->getInt() < 0)
                dev2 -= holder->getInt();
            else
                dev1 += holder->getInt();
        }
        count++;

    }while ( curr != list->getLast()->getData());
}


