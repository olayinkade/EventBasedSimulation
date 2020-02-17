#ifndef A22150_OBJ_H
#define A22150_OBJ_H


#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Obj {

public:
    virtual void print() =0;
};

class IntItem : public Obj{
private:
    int item;
public:
    void print();
    IntItem(int);
    ~IntItem();
    int getInt();
    void setInt(int x);
};


#endif //A22150_OBJ_H
