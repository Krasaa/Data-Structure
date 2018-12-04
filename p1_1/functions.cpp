#include "functions.h"
#include <string>
bool obey(std::string number){
    for (int i = 0; i < number.length();i ++){
        if ((number[i]>='0' && number[i] <= '9') || (number[i] ==  '-')||(number[i] == ',')||(number[i] ==';'))
        {;
        }
        else{return 1;}
    //invalid character such as "1554,8459,as98"
    }
    return 0;
}




//It is abandoned because it is a relatively complicated way to complete the "get" function.
/*
longlongint longlongint::operator * (longlongint another)
{
    longlongint target(1);
//the 1 is of no use
    node *rear_temp = target.rear;
    node *number1 = this->rear->prev;
    node *number2 = another.rear->prev;
/*number1,number2 and rear-temp begin from the last one of link list
which is the same as people's summing behavior.
    int sign1 = this->head->num;
    int sign2 = another.head->num;
    target.head->num = sign1 * sign2;
//store the sign for each number
    int carry = 0;
//carry
    int length = this->currentlength > another.currentlength ? currentlength : another.currentlength;
//get the max length of the two link list
    for (int i = 0; i< length; i++)
    {
        node* temp = new node;
        rear_temp->prev = temp;
        target.head->next = temp;
        temp->next = rear_temp;
        temp->prev = target.head;
        rear_temp = rear_temp->prev;
    }
/*build a link list which has a length of max(length(number1),length(number2))
to store the sum result
    rear_temp = target.rear->prev;
    while (number2 != another.head)
    {
//plus the carry, and then return it to 0.
        rear_temp->num += carry;
        carry = 0;
        number1 = this->rear->prev;
        while (number1 != this->head)
        {
            rear_temp->num += number2->num * number1->num;
            number1 = number1->prev;
            if(rear_temp->num >= 10000)
            {
                int temp = rear_temp->num/10000;
                carry += temp;
                rear_temp->num -= 10000*temp;
            }
        }
//if the number except for the fist number >10000, carry = 1.
        if(rear_temp->num >=10000 && rear_temp == target.head->next)
        {
            node *temp = new node;
            node *temp1 = target.head->next;
            carry = rear_temp->num/10000;
            temp->num = carry;
            temp1->num -= carry * 10000;
            target.head->next = temp;
            temp->prev = target.head;
            temp1->prev = temp;
            temp->next = temp1;
        }
//if the fist number > 10000, then build a new node.
        rear_temp = rear_temp->prev;
        number2 = number2->prev;
//iteration of number2 and rear_temp
    }

    return target;
}





   int first = number.find(',');
    int flag = 0;
    while(true)
    {
        if((first == -1 && flag == 1)||(number == ""))
            {
                break;
            }
        //break the circle(end condition)
        if(first == -1 && number != "")
            {
                first = 4;
                flag = 1;
            }
        //for case such as 153
        for (int i = 0; i < first; i++)
            {
                rear->num = rear->num*10 + (int)(number[i]) - 48;
                std::cout<<"number:"<<rear->num<<std::endl;
            }
        node *tmp = new node;
        rear->next = tmp;
        tmp->prev = rear;
        rear = rear->next;
        currentlength ++;
        //append a new node
        first = number.find(',');
        number = number.substr(first+1);
        first = number.find(',');
        //std::cout<<"number:"<<number<<std::endl;
    }
*/

