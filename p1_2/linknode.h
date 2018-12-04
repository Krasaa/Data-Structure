#ifndef LINKNODE_H_INCLUDED
#define LINKNODE_H_INCLUDED
#include "node.h"
#include <iostream>

class linknode
{

    friend std::ostream & operator <<(std::ostream &os,const linknode &target);
private:
public:
    node *head, *rear;
    int length;
    linknode(double *c, int *e, int n);
    ~linknode();
    linknode(const linknode &a);
    linknode operator+(linknode &another);
    linknode operator-(linknode &another);

    linknode & operator=(const linknode &target);
    linknode derivate();
    void simplify();
    linknode sortme();

};




#endif // LINKNODE_H_INCLUDED
