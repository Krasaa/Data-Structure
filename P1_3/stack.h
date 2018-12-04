#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


class seqStack
{
private:
    char* elements;
    int pop_p;
    int max_size;
    void double_space();

public:
    seqStack (int initial_size);



};




#endif // STACK_H_INCLUDED
