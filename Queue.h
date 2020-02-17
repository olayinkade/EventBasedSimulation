//
// Created by OBTAdelakun on 2/27/2017.
//

#ifndef A22150_QUEUE_H
#define A22150_QUEUE_H

#include "Node.h"

class Obj;

class Queue {
public:
    void enqueue(Obj *);
    virtual void print();
    virtual Obj* dequeue();
    virtual Obj * front();
    virtual Node * getLast();
    Queue();
    virtual ~Queue();
    virtual bool isEmpty();
    virtual void  top();
    virtual Obj * scan();
private:
    Node * last;
    Node * traversal;

protected:


    virtual void setLast(Node *);
};


#endif //A22150_QUEUE_H
