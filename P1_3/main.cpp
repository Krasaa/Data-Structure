#include <iostream>
#include "seqStack.h"
#include <string>
#include "car.h"
#include"queue.h"
using namespace std;

string process(string sequence, int *sequence_number, int *sequence_time);
void parking(string &sequence_action, int *sequence_number, int *sequence_time, int size_park);


int main()
{
    string sequence, sequence_action;
    int *sequence_number, *sequence_time, size_park;

    cout<<"-------------------------------------------------\n";
    cout<<"|Welcome to use the parking system simulation!   |\n";
    cout<<"|Instruction:                                    |\n";
    cout<<"|1. The input must follow the rule of parking    |\n";
    cout<<"|2. The output will follow the time sequence     |\n";
    cout<<"-------------------------------------------------\n";



    cout<<"     Please give the sequence of cars:"<<endl;
    cin>>sequence;
    cout<<"     Please give the size of park:"<<endl;
    cin>>size_park;

    sequence_number = new int[sequence.length()/10 + 1];
    sequence_time = new int[sequence.length()/10 + 1];
    sequence_action = process(sequence,sequence_number,sequence_time);
/*  -----------------------------------------------------------------------------------------------------------
    sequence_time   contains the using time of each car, notice: it must be sorted when inputed.              |
    sequence_number contains the token of each car when it comes in, notice: it must be a number when inputed.|
    sequence_action contains the action of each car, notice: it must be one of "A\D\E".                       |

    the above sequence are matched one by one. i.e. the i element in sequence_number will take action as the  |
    i element in sequence_action and using for the i element in sequence_time.                                |
    -----------------------------------------------------------------------------------------------------------
*/
    cout<<endl;                                                  //to be beautiful

    parking(sequence_action, sequence_number, sequence_time, size_park);



    delete [] sequence_number;
    delete [] sequence_time;

    return 0;
}
