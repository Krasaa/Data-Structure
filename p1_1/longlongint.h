#ifndef LONGLONGINT_H
#define LONGLONGINT_H
#include <string>
#include <iostream>
#include "node.h"
class longlongint
{
    friend std::ostream & operator<<(std::ostream & out,longlongint &number);
                                //�������������������ϰ�ߵ�ģʽ��������е�����
private:
    int currentlength;          //�洢��ǰ������
    int ranking;                //ָ����һ��/�ڶ������֣�Ψһ��������get()�����н��������ֽ�������

public:
    node *head,*rear;           //ָ��ͷ�ڵ��β�ڵ��ָ��

    longlongint (int ranking);  //���캯������ʼ��һ������
    ~longlongint();             //�����������������п��ٵĿռ�
    longlongint(const longlongint &a);  //�������캯����Ĭ�Ͽ������캯����������������,��Ҫ�Զ����¿������캯��

    void get(std::string number);//ʹ��һ���ַ�����������и�ֵ���õ�һ��ÿ���ڵ�洢4�����ֵ�����

    longlongint operator + (longlongint another);//���ؼӷ�������longlongint�ļӷ����
    longlongint operator * (longlongint &another);
    longlongint & operator = (const longlongint & target);//���ظ�ֵ���㣬���д���Ϳ�������95%����
    int operator <(const longlongint &number);//������longlongint�洢�����ֽ��о���ֵ�Ƚϣ���Ҫ���ڸ�������ǰ����˵��(һ������ֵ��С������a;һ������ֵ�ϴ�ĸ���b;)�����

};

#endif
