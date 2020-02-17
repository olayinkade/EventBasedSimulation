//
// Created by OBTAdelakun on 3/9/2017.
//

#ifndef A22150_PRIORITYQUEUE_H
#define A22150_PRIORITYQUEUE_H



#include "Obj.h"



class PriorityQueue : public Queue {
public:
    void enqueue(Obj * item);
    PriorityQueue();
    ~PriorityQueue();
private:
int compareTo(Obj *one, Obj *two);


};


#endif //A22150_PRIORITYQUEUE_H
