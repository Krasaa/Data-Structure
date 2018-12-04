#include "car.h"

car::car(int number, int time)
{
    token = number;
    time_come = time;
    real = 0;
}

void car::park(int time)
{
    real = time;
}

