#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "car.h"
#include <iostream>

class queque
{
private:
    car *elements;
    int max_size;
    int start, rear;

public:
    queque(int max_size = 0);
    ~queque();
    void enQueue(car target);
    car deQueue();
    int length();
    bool isEmpty();
    car head();
    car tail();
    int where(int target);
};


#endif // QUEUE_H_INCLUDED
