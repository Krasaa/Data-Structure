#include "seqStack.h"
#include <iostream>
#include <string>
#include"queue.h"
using std::string;


void parking(string &sequence_action, int *sequence_number, int *sequence_time, int size_park)
{

    int number = sequence_action.length(),iteration_number = 0;  //the number of actions
    seqStack park(size_park);
    queque waiting(sequence_action.length()-size_park + 1);
    seqStack temp(size_park);

    for (int time_step =1; time_step <= sequence_time[number-1]; time_step ++)
    {
        std::cout<<"Time step "<<time_step<<std::endl;

        if(time_step == sequence_time[iteration_number])
        {

//------------------------------------------------------------------------------------------------
//Arrival

            if(sequence_action[iteration_number] == 'A')
            {
                car newcar(sequence_number[iteration_number],sequence_time[iteration_number]);
                if(park.isFull() == 0)                          //Park is not full
                {
                    newcar.park(time_step);
                    newcar.real = time_step;
                    park.push(newcar);
                    std::cout<<"Successful parking! The position of car "<<park.top().token<<" is in PARK "<<park.length()+1<<std::endl;
                }
                else                                            //Park is full
                {
                    waiting.enQueue(newcar);
                    std::cout<<"Please wait~ The position of car "<<waiting.head().token<<" is in Waiting"<<waiting.length()<<std::endl;
                }
            }
/*---------------------------------------------------------------------------
Arrival is finished.                                                        |
If the park is not full, the new car will be placed in the park             |
Else, it will wait in the waiting list                                      |
-----------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------------------------------------
//Departure
            else                                            //Departure
            {
                int position_of_number_in_waiting = 0;
                position_of_number_in_waiting = waiting.where(sequence_number[iteration_number]);
                if(position_of_number_in_waiting != -1)
                {
                    queque temp_queue(sequence_action.length()-size_park + 1);
                    while (waiting.tail().token != sequence_number[iteration_number])
                    {
                        temp_queue.enQueue(waiting.deQueue());
                    }
                    std::cout<< "The waiting car "<<waiting.tail().token<<" cant wait any more"<<std::endl;
                    waiting.deQueue();
                    while(temp_queue.isEmpty() == 0)
                    {
                        waiting.enQueue(temp_queue.deQueue());
                    }
                }



                else{
                while(sequence_number[iteration_number] != park.top().token)
                {
                    temp.push(park.top());
                    park.pop();
                }

                car temp2 = park.pop();
                std::cout<<"Successful departure of car "<<temp2.token<<" ! The time is "<< time_step - temp2.time_come
                <<" and the fee is " << time_step - temp2.real<<std::endl;
                while(temp.isEmpty() == 0)
                {
                    park.push(temp.top());
                    temp.pop();
                }
                if(waiting.isEmpty() == 0)
                {
                    car temp1 = waiting.deQueue();
                    temp1.real = time_step;
                    park.push(temp1);
                    std::cout<<"The waiting car "<<park.top().token<<" comes into the park! The position is in PARK "<<park.length()+1<<std::endl;
                }
                }
            }
            ++iteration_number;
        }
    }
}


int trans(string a )
{
    int length = a.length();
    int target = 0;
    for (int i = 0; i<length;++i)
    {
        target = target * 10;
        target += a[i] - 48;
    }
    return target;
}

string process(string sequence, int *sequence_number, int *sequence_time)
{
    int counter = 0, dot = 0;
    string sequence_action;
    while (sequence != "")
    {
        if(sequence[2] == 'E'){break;}

        sequence_action.insert(counter,1, sequence[2]);
        sequence = sequence.substr(int(sequence.find(',')) + 1);
        dot = sequence.find(',');
        string number = sequence.substr(0,dot);
        int temp_number = trans(number);
        sequence_number[counter] = temp_number;

        sequence = sequence.substr(int(sequence.find(',')) + 1);
        int right = sequence.find(')');
        string time = sequence.substr(0,right);
        int temp_time = trans(time);
        sequence_time[counter] = temp_time;

        sequence = sequence.substr(int(sequence.find(',')) + 1);

        counter ++;
    }
    return sequence_action;
}


seqStack::seqStack(int initial_size = 10)
{
    max_size = initial_size;
    elements = new car[max_size];
    top_p = -1;
}

seqStack::~seqStack()
{
    delete [] elements;
}

void seqStack::push(const car &x)
{
    elements[++top_p] = x;
}

car seqStack::pop()
{

    return elements[top_p--];

}

bool seqStack::isEmpty()
{
    return top_p == -1;
}

bool seqStack::isFull()
{
    return (top_p == max_size - 1);
}

car seqStack::top()
{
    return elements[top_p];
}

int seqStack::length()
{
    return top_p;
}
