#ifndef LONGLONGINT_H
#define LONGLONGINT_H
#include <string>
#include <iostream>
#include "node.h"
class longlongint
{
    friend std::ostream & operator<<(std::ostream & out,longlongint &number);
                                //重载输出函数，按人类习惯的模式输出链表中的数字
private:
    int currentlength;          //存储当前链表长度
    int ranking;                //指定第一个/第二个数字，唯一作用是在get()函数中将两个数字进行区分

public:
    node *head,*rear;           //指向头节点和尾节点的指针

    longlongint (int ranking);  //构造函数，初始化一个链表
    ~longlongint();             //析构函数，返还所有开辟的空间
    longlongint(const longlongint &a);  //拷贝构造函数，默认拷贝构造函数不适用于链表类,需要自定义新拷贝构造函数

    void get(std::string number);//使用一个字符串对链表进行赋值，得到一个每个节点存储4个数字的链表

    longlongint operator + (longlongint another);//重载加法，返回longlongint的加法结果
    longlongint operator * (longlongint &another);
    longlongint & operator = (const longlongint & target);//重载赋值运算，其中代码和拷贝构造95%相似
    int operator <(const longlongint &number);//对两个longlongint存储的数字进行绝对值比较，主要用于辅助处理前面所说的(一个绝对值较小的正数a;一个绝对值较大的负数b;)的情况

};

#endif
