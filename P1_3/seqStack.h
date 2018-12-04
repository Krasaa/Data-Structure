#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED
#include <string>
#include "car.h"

class seqStack
{
private:
    car* elements;

public:
    int top_p;
    int max_size;

    seqStack(int initial_size);
    ~seqStack();
    void push (const car&x);
    car pop ();
    bool isEmpty();
    bool isFull();
    int length();
    car top();
};

#endif // SEQSTACK_H_INCLUDED
