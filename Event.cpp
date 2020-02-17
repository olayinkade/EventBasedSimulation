// CLASS: Event
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: an Abstract class that helps group
// together several events
//
//-----------------------------------------

#include <iomanip>
#include "Event.h"
#include "Process.h"
#include "Simulation.h"
#include "Queue.h"
#define TIME_SHARING 4
//Event implementation

Event::~Event(){}

void Event::print(){ }

Event::Event(int time, Process * process){
    this->time = time;
    this->process = process;
}
Process* Event::getProcess() {return process; }
int Event::getArrival() {return time;}



//Arrival implementation
Arrival::Arrival(int time, Process *process): Event::Event(time,process){}

/**********************************************
 * This fuction getNext arrival and insert on
 * the priorityQueue , it also check if the CPU
 * is free before before starting a StartCpu Event
 * and it is inserted in the CPU Queue
 * *********************************************/
void Arrival::processing() {
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID() <<" arrives in system:";
    Simulation::getnextArrival();

    if(Simulation::Cpufree()){
      Simulation::startCpuEnq(getArrival(),getProcess());
        cout <<"CPU is free (process begins execution)."<<endl;
    }
    else{
        cout <<" CPU is busy (process will be queued)."<< endl;
    }
    Simulation::getCPU()->enqueue(getProcess());

}


//StartCPU implementation
StartCPU::StartCPU(int time, Process *process): Event::Event(time,process){}
/*************************************************************************
 *if CPU burst is greater than 4 a timeout  tvent is scheduled(time sharing)
 * else it completes the event
 * ***********************************************************************/
void StartCPU::processing(){
    IntItem * holder = dynamic_cast<IntItem *>(getProcess()->getList()->front());
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID()<<" begins CPU burst of length " << holder->getInt()<<"."<<endl;
    if(holder->getInt() > TIME_SHARING){//if greater than four needs to have another go on the CPU
       Simulation::timeoutEnq(getArrival(),getProcess());
    }
    else{
        Simulation::CompleteCPUEnq(getArrival(),getProcess());
    }



}

//Timeout implementation
Timeout::Timeout(int time, Process *process): Event::Event(time,process){}
/*************************************************************************
 *it dequeues the current process that requires a timeout and reenqueues it
 * to acommodate the reduction of the  current Cpu burst
 * then processes  the a startCPU event for the prooces at the front of the
 * CPUqueue
 * ***********************************************************************/
void Timeout::processing(){
    IntItem * holder = dynamic_cast<IntItem *>(getProcess()->getList()->front());
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID()<<" exhausts its time quantum  (requires " << holder->getInt() <<" unit more)"<<endl ;
    Simulation::getCPU()->dequeue();
    Simulation::getCPU()->enqueue(getProcess());
    Process * hold = dynamic_cast<Process * >(Simulation::getCPU()->front());
    if(!Simulation::Cpufree()){
        if(hold !=NULL) {
            Simulation::startCpuEnq(getArrival(), hold);
        }
    }

    hold =NULL;


}
//CompleteCPU inplementation
CompleteCPU::CompleteCPU(int time, Process *process): Event::Event(time,process){}

/*************************************************************************
 *Occurs when startCPU completes. it deletes the just completed process
 * from the CPUQueue
 * if they are no more burst to be processed it exits
 * else if they are more burst to be processed
 * it finds out which IO burst it is and enqueues a startIO event
 * it also looks at the CPUQueue andStartCPu event if the CPU is not free
 * ***********************************************************************/
void CompleteCPU::processing(){
    Simulation::getCPU()->dequeue();
    getProcess()->getList()->dequeue() ;
    if ( getProcess()->getList()->isEmpty() ){
        cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID()<<" completes CPU burst."<<endl;
        Simulation::exitEnq(getArrival(),getProcess());
    }

    else{
        IntItem * holder = dynamic_cast<IntItem *>(getProcess()->getList()->front());

        if(holder != NULL) {
            if (holder->getInt() > 0) {
                cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID()<<" completes CPU burst. Queueing for I/O Device "<<1<<endl;
                if (Simulation::IODevice1free()) {
                   Simulation::StartIODevice1Enq(getArrival(),getProcess());
                }

                    Simulation::getIODevice1()->enqueue(getProcess());



            }
            else if (holder->getInt() < 0){
                cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<<getProcess()->getID()<<" completes CPU burst. Queueing for I/O Device "<<2<<endl;
                if (Simulation::IODevice2free()) {
                    Simulation::StartIODevice2Enq(getArrival(),getProcess());
                }
                    Simulation::getIODevice2()->enqueue(getProcess());
            }
        }
    }

    if(!Simulation::Cpufree()){
        Process * hold = dynamic_cast<Process * >(Simulation::getCPU()->front());
        if(hold !=NULL){
            Simulation::startCpuEnq(getArrival(),hold);
        }

    }



}


// StartIODevice1 implementation
StartIODevice1::StartIODevice1(int time, Process *process): Event::Event(time,process){}
/*************************************************************************
 *enqueues a startIODevice1 on the Eventlist
 * ***********************************************************************/
void StartIODevice1::processing() {
    IntItem * holder = dynamic_cast<IntItem *>(getProcess()->getList()->front());
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
         <<" begins I/O Device 1 burst of length "
         <<holder->getInt()<<endl;
    Simulation::CompleteIODevice1Enq(getArrival(),getProcess());
}
// StartIODevice2 implementation
StartIODevice2::StartIODevice2(int time, Process *process): Event::Event(time,process){}
/*************************************************************************
 *enqueues a startIODevice2 on the Eventlist
 * ***********************************************************************/
void StartIODevice2::processing() {
    IntItem * holder = dynamic_cast<IntItem *>(getProcess()->getList()->front());
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
         <<" begins I/O Device 2 burst of length "
         <<holder->getInt() * -1<<endl;
    Simulation::CompleteIODevice2Enq(getArrival(),getProcess());

}
// CompleteIODevice1 implementation
CompleteIODevice1::CompleteIODevice1(int time, Process *process): Event::Event(time,process) {}
/*************************************************************************
 *Occurs when startIODevice1 completes. it deletes the just completed process
 * from the IODevice1Queue
 * if theIODevice1 is not free then enqueue a startIODevice1  (process at the front of IODevice1)
 * on the eventlist
 * if they are no more burst to be processed it exits
 * else if they are more burst to be processed
 * it starts a StartCPU event with the new burst
 * it also looks at the CPUQueue  and if it is free
 * andStartCPu event
 * ***********************************************************************/
void CompleteIODevice1::processing() {
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
         << " completes I/O Device 1 burst. Queueing for CPU." << endl;

    Simulation::getIODevice1()->dequeue();
    if (!Simulation::IODevice1free()) {
        Process *hold = dynamic_cast<Process * >(Simulation::getIODevice1()->front());
        if (hold != NULL) {
            Simulation::StartIODevice1Enq(getArrival(), hold);
        }

    }
    if (getProcess()->getList()->dequeue() != NULL && getProcess()->getList()->isEmpty() ){
        cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
             <<" completes I/O Device 1 burst."<<endl;
        Simulation::exitEnq(getArrival(),getProcess());
    }
    else{
        if(Simulation::Cpufree())
            Simulation::startCpuEnq(getArrival(), getProcess());
        Simulation::getCPU()->enqueue(getProcess());
    }
}
// CompleteIODevice2 implementation
CompleteIODevice2::CompleteIODevice2(int time, Process *process): Event::Event(time,process) {}

/*************************************************************************
 *Occurs when startIODevice2completes. it deletes the just completed process
 * from the IODevice2Queue
 * if theIODevice2 is not free then enqueue a startIODevice2(process at the front of IODevice2)
 * on the eventlist
 * if they are no more burst to be processed it exits
 * else if they are more burst to be processed
 * it starts a StartCPU event with the new burst
 * it also looks at the CPUQueue  and if it is free
 * andStartCPu event
 * ***********************************************************************/
void CompleteIODevice2::processing() {
    cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
         <<" completes I/O Device 2 burst. Queueing for CPU."<<endl;
    Simulation::getIODevice2()->dequeue();
    if (!Simulation::IODevice2free()) {
        Process *hold = dynamic_cast<Process * >(Simulation::getIODevice2()->front());
        if (hold != NULL) {
            Simulation::StartIODevice2Enq(getArrival(), hold);
        }

    }
    if (getProcess()->getList()->dequeue() != NULL && getProcess()->getList()->isEmpty()){
        cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()
             <<" completes I/O Device 2 burst."<<endl;
        Simulation::exitEnq(getArrival(),getProcess());
    }
    else{

       if(Simulation::Cpufree())
            Simulation::startCpuEnq(getArrival(), getProcess());
       Simulation::getCPU()->enqueue(getProcess());
    }

}


// Exit implementation
Exit::Exit(int time, Process *process): Event::Event(time,process) {}
/*****************************************
 * ends a particular Process
 *
 ***************************************/
void Exit::processing() {
        cout << "Time"<<setw(7)<< getArrival()<<":  Process"<<setw(3)<< getProcess()->getID()<< " complete Total wait time "<< getProcess()->getExit() - getProcess()->getTotal()  <<endl;


}
