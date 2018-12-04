#include<iostream>
#include<string>
#include "longlongint.h"
#include "functions.h"
using namespace std;

bool obey(string a);

int main()
{
    string number;
    cout<<"----------------------------------------------------------------------\n";
    cout<<"Welcome to use the Longlongint Calculator!                           |\n";
    cout<<"Instruction:                                                         |\n";
    cout<<"1. The input must follow the Chinese tradition                       |\n";
    cout<<"2. If you want to try the multiplication, delete the // in line 31~33|\n";
    cout<<"3. Multiplication just supports small product such as 1000*10000     |\n";
    cout<<"----------------------------------------------------------------------\n";
    cout<<"Please input two number following the basic rule:\n";
    cin>>number;
    if(obey(number) == 1)
    {
        cout<<"Invalid input!"<<endl;
        return 1;
    }
    //input the numbers to be added
    longlongint number1(1), number2(2);
    number1.get(number);
    number2.get(number);
    cout<<endl;
    cout<<"The first number is: "<<number1;
    cout<<endl;
    cout<<"The second number is: "<<number2;
    cout<<endl;
    longlongint target_plus = number1 + number2;
    cout<<"The sum is: "<<target_plus;
    cout<<endl;
    //longlongint target_mul = number1 * number2;
    //cout<<"The product is: "<<target_mul;
    //cout<<endl;
    return 0;
}
