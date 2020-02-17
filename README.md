# Introduction
A discrete-event simulation
to simulate the operation of a multiprogramming Operating System. 
#Background
A data file is used to drive the simulation. The data file will be ordered by time, so you must
have only one arrival event in the event list at any time. Each arrival must cause the
next arrival event to be read. Each Process will get an ID number (start at 1) when it
arrives, and each new Process will have an ID one higher than that before it. You must use a
C++ static variable to keep track of the next Process number to be generated.
There are nine events that can happen to any Process:
## An Arrival 
occurs when the Process is submitted. If no Process is currently executing on
the CPU, you should schedule a StartCPU event; otherwise the Process is entered into a queue of Processes waiting for their turn to execute on the CPU. (Use a strict FCFS queuing
discipline.)
## A StartCPU event
causes the Process to be scheduled to execute on the CPU. Our OS
supports timesharing: each Process may use the CPU for a maximum time quantum of 4
time units. Note that a real OS does not know beforehand if a Process will exhaust its time
quantum, but in our simulation model, we know the length of a CPU burst, so we know
whether the process will timeout (you should schedule a Timeout event) or complete the
burst (you should schedule a CompleteCPU event).
## A CompleteCPU event 
occurs when the Process completes a CPU burst. The Process will
either have more bursts to process (the next one will be an I/O burst), or it will have
finished its processing, and an ExitEvent should be scheduled. Be sure to check if there are
Processes waiting their turn to execute, and schedule the first one on the queue to start
execution.
## A Timeout event
occurs when the process exhausts its time quantum. The Process goes to
the back of the queue and waits for another turn, to continue executing the CPU burst.
Again, check the queue of waiting processes.
## The StartIODevice1 and StartIODevice2 events
cause the Process to start an I/O
operation. I/O operations are not time-shared; a Process gets to complete its entire I/O
burst once it starts.
## The CompleteIODevice1 and CompleteIODevice2 events
occur when a Process
completes an I/O operation. Be sure to check if there are Processes waiting to start an I/O
operation. As with the CompleteCPU event, the Process will either have finished its
processing, or have more bursts to be scheduled.
## An Exit event
occurs once the Process has completed all its CPU and I/O bursts and leaves
the system. 
# Output
Final statistics are gathered about the execution of this Process.
You will need to maintain a list of future events in order by time. During the simulation
produce output that indicates the sequence of events processed and
when they occurred in order by time. At the end of the simulation a summary table will be produced.
