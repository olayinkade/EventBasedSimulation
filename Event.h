#ifndef A22150_EVENT_H
#define A22150_EVENT_H



class Process;
#include "Obj.h"

class Event : public Obj {

private:
    int time;
    Process * process;
public:
    Event(int, Process*);
    virtual ~Event();
    void print();
    virtual int getArrival();
    virtual Process * getProcess();
    virtual void  processing() = 0;

};

class Arrival: public Event{
public:
    void processing();
    Arrival(int time, Process * process);
};

class StartCPU : public Event{
public:
    void processing();
    StartCPU(int time, Process * process);
};
class Timeout : public Event{
public:
    void processing();
    Timeout(int time, Process * process);
};
class CompleteCPU : public Event{
public:
    void processing();
    CompleteCPU (int time, Process * process);
};
class StartIODevice1: public Event{
public:
    void processing();
    StartIODevice1(int time, Process * process);
};
class StartIODevice2: public Event{
public:
    void processing();
    StartIODevice2(int time, Process * process);
};
class CompleteIODevice1: public Event{
public:
    void processing();
    CompleteIODevice1(int time, Process * process);};
class CompleteIODevice2: public Event{
public:
    void processing();
    CompleteIODevice2(int time, Process * process);
};
class Exit: public Event{
public:
    void processing();
    Exit(int time, Process * process);
};



#endif //A22150_EVENT_H
