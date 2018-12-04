#include <iostream>
#include "node.h"
#include "linknode.h"
using namespace std;

int main()
{

    int n1 = 0;
    cout<<"------------------------------------------------"<<endl;
    cout<<"|Welcome to use the polynomial system!         |"<<endl;
    cout<<"|Notice:                                       |"<<endl;
    cout<<"|1.The input must follow the rule.             |"<<endl;
    cout<<"|2.Remember to input the number of terms n     |"<<endl;
    cout<<"------------------------------------------------"<<endl;
    cout<<"Please input the number of terms in first function: "<<endl;
    cin>>n1;
    double * c1 = new double[n1];
    int * e1 = new int[n1];
    for (int k = 0; k < n1; k++)
    {
        cin>>c1[k]>>e1[k];
    }
    linknode link1(c1,e1,n1);

    int n2 = 0;
    cout<< "Please input the number of terms in second function: "<<endl;
    cin>>n2;
    double * c2 = new double[n2];
    int * e2 = new int[n2];
    for (int k = 0; k < n2; k++)
    {
        cin>>c2[k]>>e2[k];
    }
    linknode link2(c2,e2,n2);


    link1.simplify();
    link2.simplify();
    link1 = link1.sortme();
    link2 = link2.sortme();
    linknode link_sum = link1 + link2;
    cout<<"The sum is :"<<link_sum<<endl;
    linknode link_sub= link1 - link2;
    cout<<"The subtraction is : "<<link_sub<<endl;
    linknode link_derivate = link_sum.derivate();
    cout<<"The derivate of the sum is :"<<link_derivate<<endl;

    return 0;

}
