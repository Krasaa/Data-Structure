#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

class car
{
public:
    int time_come;
    int token;
    int real;
    car(int token = 0, int time_come = 0);
    void park(int time);
};




#endif // CAR_H_INCLUDED
