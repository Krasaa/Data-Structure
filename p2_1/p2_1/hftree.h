#ifndef HFTREE_H_INCLUDED
#define HFTREE_H_INCLUDED
#include <string>

class hfTree{
private:

    int length;
    struct Node
    {
        char data;
        double weight;
        int parent, left = -1, right = -1;
    };
public:
    Node *elem;

    struct hfCode
    {
        char data;
        std::string code;
    };

    hfTree(const std::string &input, const double *weight, const int input_length);
    void getCode(hfCode result[]);
    ~hfTree(){delete [] elem;}
};


#endif // HFTREE_H_INCLUDED
