#ifndef A22150_NODE_H
#define A22150_NODE_H
#include <iostream>
class Obj;
class Event;

class Node {

private:
    Obj* data;
    Node * next;

public:
    Node(Obj *,Node *);
    Obj* getData();
    Node* getNext();
    void setData(Obj *);
    void  setnext(Node *);
    Event*  getEvent();
    ~Node();
};


#endif //A22150_NODE_H
