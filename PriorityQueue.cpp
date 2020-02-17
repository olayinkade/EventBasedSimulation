// CLASS: PriorityQueue
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: Stores events in a priorityQueue
// with priority of their time
//
//-----------------------------------------
#include "Queue.h"
#include "PriorityQueue.h"
#include "Event.h"
#include "Process.h"

PriorityQueue::PriorityQueue(): Queue::Queue(){}

PriorityQueue::~PriorityQueue(){}
/*************************************************
 * this compareTO function helps with  cases
 * where two events are compared
 * if Event compared are Arrival or Timeout,
 * Arrival  should be inserted before Timeout
 *Also if they are of other types(not Timeout or Arrival)
 * i just compare Arrival time
 * This method just helps to place where the element is to
 * be placed
 * @param first item to be compared
 * @param second item to be compares
 * @return
 */
int PriorityQueue::compareTo(Obj *one, Obj *two) {
    Event * hold = dynamic_cast<Event *>(one);
    Event * holder = dynamic_cast<Event *>(two);
    int result = 0;
    if(hold != NULL && holder != NULL && holder->getArrival()  ==  hold->getArrival()){
        if(dynamic_cast<Timeout *>(one) && dynamic_cast<Arrival*>(two))
            result = 1;
        else if(dynamic_cast<Arrival*>(one)&& dynamic_cast<Timeout *>(two))
            result = -1;

        else {
            if (hold->getProcess()->getID() > holder->getProcess()->getID())
                result = 1;
            else if (hold->getProcess()->getID() < holder->getProcess()->getID())
                result = -1;
        }
    }
    return result;
}


/**************************************************
 * enqueues Event in order of arrival time or curr Event
 * @param item
 */
void PriorityQueue::enqueue(Obj * item) {
    if(isEmpty()){
        Queue::enqueue(item);
    }
    else{
        Event * itemdata = dynamic_cast<Event *>(item);
        Node * curr = getLast()->getNext();
        Node * prev = getLast();
        bool pos =false;
        int result =0;

        do{
            Event * currdata = dynamic_cast<Event * >(curr->getData());
            if(currdata->getArrival() > itemdata->getArrival()){
                pos = true;
            }
            else if(currdata->getArrival() == itemdata->getArrival()){
                result = compareTo(itemdata,currdata);
                if(result >= 0){
                    prev = curr;
                    curr = curr->getNext();
                }
                else
                    pos = true;

            }
            else{
                prev = curr;
                curr = curr->getNext();
            }

        }while (curr != getLast()->getNext() && !pos);

        prev->setnext(new Node(item,curr));
        if(!pos){// if false mean there is a bigger number in the list
            setLast(prev->getNext());// and need to set list
        }

        }





    }


