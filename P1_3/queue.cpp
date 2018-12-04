#include "queue.h"
#include "car.h"
queque::queque(int size_)
{
    elements = new car[size_];
    max_size = size_;
    start = rear = 0;
}

queque::~queque()
{
    delete [] elements;
}

void queque::enQueue(car target)
{
    elements[rear] = target;
    rear = ( rear+1 ) % max_size;
}

car queque::deQueue()
{
    int temp = start;
    start = ( start + 1)%max_size;
    return elements[temp];
}

int queque::length()
{

    return start<rear? (rear - start) : (rear + max_size -start + 1) ;
}

bool queque::isEmpty()
{
    return start == rear;
}

car queque::head()
{
    int position = (start !=0 && rear ==0)? max_size - 1: rear - 1;
    return elements[position];
}

car queque::tail()
{
    return elements[start];
}


int queque::where(int target)
{
    if(start == rear) {return -1;}
    if(start < rear || start > 0 && rear == 0)
    {
        int point = (rear == 0) ? max_size : rear;
        for (int i = start; i < rear; i++)
        {
            if(elements[i].token == target){return i;}
        }
    }
    if(start > rear && rear !=0)
    {
        for (int i = start; i< max_size;i++)
        {
            if(elements[i].token == target){return i;}
        }
        for (int i = 0; i<rear; i++)
        {
            if(elements[i].token == target){return i;}
        }
    }
    return -1;
}

