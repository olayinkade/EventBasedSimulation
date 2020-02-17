# Introduction
A discrete-event simulation
to simulate the operation of a multiprogramming Operating System. 
# Setup
1. To compile files ``make``
2. To run ``./main test.txt``
# Background
A data file is used to drive the simulation. The data file will be ordered by time, so you must
have only one arrival event in the event list at any time. Each arrival must cause the
next arrival event to be read. Each Process will get an ID number (start at 1) when it
arrives, and each new Process will have an ID one higher than that before it. You must use a
C++ static variable to keep track of the next Process number to be generated.
There are nine events that can happen to any Process:
### An Arrival 
occurs when the Process is submitted. If no Process is currently executing on
the CPU, you should schedule a StartCPU event; otherwise the Process is entered into a queue of Processes waiting for their turn to execute on the CPU. (Use a strict FCFS queuing
discipline.)
### A StartCPU event
causes the Process to be scheduled to execute on the CPU. Our OS
supports timesharing: each Process may use the CPU for a maximum time quantum of 4
time units. Note that a real OS does not know beforehand if a Process will exhaust its time
quantum, but in our simulation model, we know the length of a CPU burst, so we know
whether the process will timeout (you should schedule a Timeout event) or complete the
burst (you should schedule a CompleteCPU event).
### A CompleteCPU event 
occurs when the Process completes a CPU burst. The Process will
either have more bursts to process (the next one will be an I/O burst), or it will have
finished its processing, and an ExitEvent should be scheduled. Be sure to check if there are
Processes waiting their turn to execute, and schedule the first one on the queue to start
execution.
### A Timeout event
occurs when the process exhausts its time quantum. The Process goes to
the back of the queue and waits for another turn, to continue executing the CPU burst.
Again, check the queue of waiting processes.
### The StartIODevice1 and StartIODevice2 events
cause the Process to start an I/O
operation. I/O operations are not time-shared; a Process gets to complete its entire I/O
burst once it starts.
### The CompleteIODevice1 and CompleteIODevice2 events
occur when a Process
completes an I/O operation. Be sure to check if there are Processes waiting to start an I/O
operation. As with the CompleteCPU event, the Process will either have finished its
processing, or have more bursts to be scheduled.
### An Exit event
occurs once the Process has completed all its CPU and I/O bursts and leaves
the system. 
# Output
Final statistics are gathered about the execution of this Process.
You will need to maintain a list of future events in order by time. During the simulation
produce output that indicates the sequence of events processed and
when they occurred in order by time. At the end of the simulation a summary table will be produced.
# Design

### GENERIC NODE
The abstract Obj class act as a container which can hold all subclass instances. In this code the Obj class is a superclass for IntItem, Process and Event which means an Obj variable can hold IntItem, Process and Event instances. The Node class is created with Obj as the data to be stored, therefore even if I can’t create an Obj instance because it is abstract, I can create either IntItem, Process or Event are stored in the Node.

### LINKEDLIST STRUCTURE (CIRCULAR LINKED LIST)
At the top of the Linked ADT is the Queue class which is a super class to PriorityQueue. This hierarchy helps to pass methods from Queue to its subclass. The functionality that is required and shared by the subclass are
1. Add/ remove (in A strict FCFS basis)
2. traversal
Basically, these linked Structures all act as a link to connect Nodes together, and Nodes stores Obj, therefore this structure just helps to store Obj as collection or set. PriorityQueue uses specialization and stores nodes in order of the time of the Event.

### EVENT PROCESSING
The static Simulation class acts as a database class which helps to store Processes and Events. The Simulation class also has interface methods which help to carry out activities which are processed in the Event class. The Initializer method in the Simulation class helps to pass in an already opened ifstream ad uses that to read next arrivals when needed. The Event class is a superclass to all 9 possible Events. When processed each event enqueues a respective Event on to the event list.
Process class helps to store burst (Intitem) and Arrival times. This helps
The main class (class with the main method inside) main method is called first, it then calls Simulation::initializer, which basically drives this event based simulation(an Arrival is enqueue first).
Stored in
OBJ
Process
IntItem
NODE
QUEUE
PriorityQueue
Event
