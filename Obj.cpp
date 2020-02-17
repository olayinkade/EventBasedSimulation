// CLASS: Obj
//
// Author: Adelakun olayinka, 77900202
//
// REMARKS: causes Node to be generic
//it can store an Intitem, Process, Event,

//-----------------------------------------
#include "Obj.h"

// CLASS: IntItem
//
// Author: Adelakun Olayinka, 7790020
//
// REMARKS: Since am going to be storing
//ints in the my process list
//i need this to inherit Obj class
//-----------------------------------------
IntItem::IntItem(int x):item(x){}
IntItem::~IntItem(){}
//accessor and mutator
int IntItem::getInt() { return item;}
void IntItem::setInt(int x) { item = x;}
void IntItem::print(){
    cout<< item<<endl;
}