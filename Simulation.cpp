


#define MAX 100
#define TIME_SHARING 4
#include <iomanip>
#include "Simulation.h"
#include "Process.h"
#include "Queue.h"
#include "Event.h"
#include "PriorityQueue.h"

Queue * Simulation::processes = new Queue();
Queue * Simulation::IODevice2 = new Queue();
Queue * Simulation::IODevice1 = new Queue();
Queue * Simulation::Cpu = new Queue();
PriorityQueue * Simulation::event = new PriorityQueue();
ifstream * Simulation::opener = NULL;
Queue* Simulation::getCPU() { return Cpu;}
Queue* Simulation::getprocesses() {return processes;}
Queue* Simulation::getIODevice1() {return IODevice1 ;}
Queue* Simulation::getIODevice2() {return IODevice2 ;}

/**********************************************************
 * This method getnext process that need to be processed
 * it parses the string and creates a process which is then
 * enqueued on the process list
 * it also creates an arrival event which is enqueue on the
 * event list
 *************************************************************/
void Simulation::getnextArrival() {
    Process * newprocess;

    int total = 0;
    int value;
    static int id = 1;
    char buffer[MAX];
   if(!opener->eof()){
        newprocess = new Process();
        opener->getline(buffer, MAX);
        stringstream line(buffer);
        line >> value;
        total = value;
        newprocess->setArrival(value);

        
        while(!line.eof()) {
            line >> value;
            newprocess->getList()->enqueue(new IntItem(value));

            if (value < 0) {
                total += (-1 * value);
            }
            else {
                total += value;
            }

        }
        newprocess->setID(id);
        newprocess->calculate();
        id++;
        newprocess->setTotal(total);
        processes->enqueue(newprocess);
        event->enqueue(new Arrival(newprocess->getArrival(),newprocess));

    }
}
/**************************************************************
 *takes in an ifstream pointer which is passed in when called
 *dequeues current front Event  and processes current Event
 * which result in other event can be enqueued
 * basically the driver of this program
 * @param open
 */
void Simulation::intializer(std::ifstream * open) {
    if(open->is_open()) {
        opener = open;
        getnextArrival();
        while (!event->isEmpty()) {
            Event *holder = dynamic_cast<Event * >(event->dequeue());
            if (holder) {
                holder->processing();
                delete holder;
                holder = NULL;
            }
        }
    }
    else
        cout << "file not open"<<endl;
}
//All three check if corresponding Queue is free
//------------------------------------------------
bool Simulation::Cpufree(){
    return Cpu->isEmpty();
}
bool Simulation::IODevice1free() {
    return IODevice1->isEmpty();
}
bool Simulation::IODevice2free() {
    return IODevice2->isEmpty();
}
//--------------------------------------------------


//All of these method helps to enqueue a specific events
// onto the priority Queue to be ready to be dequeued
//later and processed

//--------------------------------------------------

void Simulation::startCpuEnq(int time , Process * level){
    event->enqueue(new StartCPU(time,level));
}
void Simulation::timeoutEnq(int time ,Process *level) {
    IntItem * holder = dynamic_cast<IntItem *>(level->getList()->front());
    holder->setInt(holder->getInt() - TIME_SHARING);
    holder =NULL;
    event->enqueue(new Timeout(time+ TIME_SHARING,level));
}
void Simulation::CompleteCPUEnq(int time ,Process *level) {
    IntItem * holder = dynamic_cast<IntItem *>(level->getList()->front());
    event->enqueue(new CompleteCPU(time + holder->getInt() ,level));
}
void Simulation::StartIODevice1Enq(int time ,Process *level) {
    event->enqueue(new StartIODevice1(time,level));
}
void Simulation::StartIODevice2Enq(int time ,Process *level) {
    event->enqueue(new StartIODevice2(time,level));
}
void Simulation::CompleteIODevice1Enq(int time ,Process *level) {
    IntItem * holder = dynamic_cast<IntItem *>(level->getList()->front());
    event->enqueue(new CompleteIODevice1(time+holder->getInt(),level));
}
void Simulation::CompleteIODevice2Enq(int time ,Process *level) {
    IntItem * holder = dynamic_cast<IntItem *>(level->getList()->front());
    event->enqueue(new CompleteIODevice2(time+(holder->getInt()*-1),level));
}
void Simulation::exitEnq(int time ,Process *level) {
    level->setExit(time);
    event->enqueue(new Exit(time,level));

}
//--------------------------------------------------


//print all processes and corresponding information
void Simulation::printAll(){
    cout<<"...All Processes complete. Final Summary:\n\n"<<endl;
    cout<<"Process      Arrival       CPU         I/O Time          Exit      Wait\n"
        <<"      #         TIme      Time    Dev 1      Dev 2       Time      Time\n"
        <<"...................................................................................."<<endl;




    while(Simulation::getprocesses()->front() != NULL){
        Process *hold = dynamic_cast<Process * >(Simulation::getprocesses()->dequeue());
            cout <<setw(7)<< hold->getID()<<setw(13)<<hold->getArrival()<<setw(9)<<hold->getCpu()<<setw(10)<<hold->getDev1()<< setw(11)<< hold->getDev2()<< setw(10)<<hold->getExit()<<setw(9)<< hold->getExit() - hold->getTotal()   <<endl;
    }

}
