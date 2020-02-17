// CLASS: Queue
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: stores NODES in a FCFS manner
//uses circular
//-----------------------------------------

#include "Queue.h"
#include "Obj.h"
//returns true if list is empty
bool Queue::isEmpty() { return last ==NULL;}

//traversal functions
/***************************************************************
 * it helps to  the traverse list and returns each curr item in
 * the list
 ***************************************************************/

//______________________________________________________________
void  Queue::top() {
    if(!isEmpty()){
        traversal = last;
    }
}

Obj* Queue::scan() {
    Obj * toreturn =NULL;
    if(!isEmpty()){
        traversal = traversal->getNext();
        toreturn = traversal->getData();

    }
    return toreturn;

}
//____________________________________________________

//print list
void Queue::print(){
    if(!isEmpty()){
        Node * curr= last;
        do{
            curr = curr->getNext();
            curr->getData()->print();

        }while(curr != last);
    }


}
Queue::Queue() {
    last = NULL;
}

Queue::~Queue() {}
//enqueues Node in a FCFS manner
void Queue::enqueue(Obj * item ){
    if(isEmpty()){
        last = new Node(item,NULL);
        last->setnext(last);
    }
    else{
        last->setnext(new Node(item,last->getNext()));// adds to the back
        last = last->getNext();// moves last

    }


}
// deletes at the front
Obj *Queue::dequeue(){

    Obj* toreturn = front();
    if(!isEmpty()){
        if(last == last->getNext()){
            last = NULL;
        }
        else{
            last->setnext(last->getNext()->getNext());
        }

    }
    return toreturn;
}
// returns element at the front
Obj* Queue::front(){
    Obj * toreturn = NULL;
    if(!isEmpty()){
        toreturn = last->getNext()->getData();

    }
    return toreturn;
}

// Acessors and mutators
Node * Queue::getLast(){ return last; }
void Queue::setLast(Node * last){ this->last = last; }



