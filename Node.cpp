// CLASS:Node
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: containment system
//
//-----------------------------------------

#include "Node.h"
#include "Event.h"


Node::Node(Obj* data,Node * news):data(data),next(news){}
Obj * Node::getData() {return data;}
Node * Node::getNext() {return next;}
void Node::setData(Obj  * set){ data = set;}
void Node::setnext(Node * set){ next = set; }

Event * Node::getEvent(){
    Event * currdata= dynamic_cast<Event*>(this->getData());
    return currdata;
}

Node::~Node(){}
