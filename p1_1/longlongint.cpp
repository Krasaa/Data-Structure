#include<string>
#include<iostream>
#include"longlongint.h"
#include "node.h"

//initialize the link list
//���캯������ʼ����������ͷβ�ڵ�
longlongint::longlongint(int n)
{
ranking = n;
head = new node;
head->next = rear = new node;
rear->prev = head;
currentlength = 0;
head->num = 1;
}

longlongint::~longlongint()
{
    while(head != rear)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }

}

//�������캯��������һ����ȫ�¿��ٵġ����ڵ�ֵ��ȫ��ȵ�������
longlongint::longlongint(const longlongint &target)
{
    node *temp = target.head;//temp���ڱ���target�еĸ��ڵ㣬��������ֵ���и���
    node *temp_rear = target.rear;//temp_rear������tempָ���βʱֹͣ����

    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    currentlength = 0;
    head->num = temp->num;//�½�������ʼ��head��rear�ڵ�

    temp = temp->next;
    node *add = this->head;//add�������½������н����½ڵ�
    while(temp != temp_rear)
    {
        node *link = new node;
        link->num = temp->num;
        add->next = link;
        link->next = this->rear;
        this->rear->prev = link;
        link->prev = add;

        add = add->next;
        temp = temp->next;
        currentlength ++;
    }
}

//get�������ڶ�longlongint������и�ֵ���õ�һ�����ڵ�洢�ĸ����ֵ�����
void longlongint::get(std::string number)//����Ϊ������ַ���
{
    int change = int(number.find(';'));//ȷ�������ַ����С�;����λ��
//the position of ';'
    int start = ranking ==1? 0:change + 1;
    int ending = ranking ==1? change - 1 : number.length()-2;
//����ranking��ֵ���ַ������в�ͬ�Ļ��֣�
//���rankingΪ1����ȡ;ǰ�Ĳ��֣����rankingΪ2����ȡ;��Ĳ���
//get the beginning and the ending for each number
    if (number[start] == '-')
        {
            head->num = -1;
            start++;
        }//�������Ǹ��ţ�����У�������ͷ�ڵ�
    number = number.substr(start,ending - start + 1);//����rankingȡ��Ӧ����
//get the target substring
//whether the number is positive or not
    node* temp = new node;
    rear->next = temp;
    temp->prev = rear;
    rear = rear->next;
    currentlength ++;                           //�Ƚ���һ���ڵ�
    int flag = 0;
    int tens[] = {1,10,100,1000};
    //flag����ѡȡtens����Ҫ�˵��������� 5879  = 5*1000+8*100+7*10+9
    while(number.length() != 0)
    {
        int length = number.length() - 1;
        if(number[length] == ',')
            //�����е�,�ָ����ĸ����֣����˽��б�������������Ϊ����ÿ��λ�ϵ����ֳ�����Ӧ
            //�е�Ȩֵ��������� 5879  = 5*1000+8*100+7*10+9
            {   number.erase(length);//��ȥ,��������һ���µĽڵ�
                flag = 0;
                node* temp = new node;
                temp->next = head->next;
                head->next = temp;
                temp->prev = head;
                temp->next->prev = temp;
                currentlength ++;
                length --;
            };
        head->next->num += tens[flag] * (number[length]-48);
        number.erase(length);   //ÿ����һλ���֣��Ͳ�ȥһλ
        flag ++;
    }
}

//��������������������ϰ����������е�����
std::ostream & operator << (std::ostream & out , longlongint &number)
{
    if(number.head->num == -1){out << '-';}//���Ϊ�������һ��-
    int tens[4] =  {1000,100,10,1};
    //����ѭ����ֹ�� ��1���Ϊ0001 ���ֶ���0���ֵ���������������ǰ��������
    //����ֵΪ0�Ľڵ�
    while(number.head->next->num == 0 && number.currentlength != 1)
    {
        node *temp1 = number.head->next;
        number.head->next = temp1->next;
        temp1->next->prev = number.head;
        delete temp1;
        number.currentlength--;
    }
    node *temp = number.head->next;
    //�����������������нڵ�����ֵľ���ֵ������ֵ��Ϊ�����ƺ��������ʵ�֣�
    //���⣬ÿ4�����ֱ���һ�α�֤�� 10010 �������Ϊ110����ֱֹ�����int���Ͷ�ʧǰ��Ӧ�е�0��
    while (temp != number.rear)
    {
        int the_number = temp->num > 0 ? temp->num : (temp->num *-1);
        if(temp != number.head->next)
        {
            for (int iter = 0; iter <= 3; iter ++)
            {
                out<<the_number / tens[iter];
                the_number = the_number - (the_number / tens[iter])*tens[iter];
            }
        }
        else
        {
            out<< ((temp->num > 0) ? temp->num : (temp->num* -1));
        }
        temp = temp->next;
        if(temp != number.rear)
        {
            out<<",";
        }

    }
}

//operator: sum
longlongint longlongint::operator + (longlongint another)
{
    longlongint target(1);
//the 1 is of no use
    node *rear_temp = target.rear;
    node *number1 = this->rear->prev;
    node *number2 = another.rear->prev;
/*number1,number2 and rear-temp begin from the last one of link list
which is the same as people's summing behavior.*/
    int sign1 = this->head->num;
    int sign2 = another.head->num;
    int carry = 0;
    int judge = *this < another;


    //����ֵ��ȣ������෴������0
    if((judge == 2 && this->head->num * another.head->num == -1)||
       (judge ==2 && this->currentlength ==1 && this->head->next->num == 0))
    {
        node* temp = new node;
        temp->num = 0;
        target.currentlength = 1;
        rear_temp->prev = temp;
        target.head->next = temp;
        temp->next = rear_temp;
        temp->prev = target.head;
        rear_temp = rear_temp->prev;
        return target;
    }

    //����ķ��ŵ��ھ���ֵ���ߵķ���
    target.head->num = judge==1? another.head->num:this->head->num;

    int range_max;
    int range_min;
    range_max = target.head->num ==1? 9999:0;
    range_min = target.head->num ==1? 0:-9999;
    int carry_ini = -target.head->num;

    //����һ���㹻���������װ�½��������������Ϊ max(length) + 1
    int length = this->currentlength > another.currentlength ? currentlength : another.currentlength;
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
to store the sum result*/
    rear_temp = target.rear->prev;

    //��number1��ֵ�Ӻ���ǰ��ֵ��target�У��൱�� target + number1
    while (number1 != this->head)
    {
        rear_temp->num += sign1 * number1->num;
        rear_temp = rear_temp->prev;
        number1 = number1->prev;
    }
    rear_temp = target.rear->prev;

    //��target + number1 �ٴӺ���ǰ����number2
    while (number2 != another.head)
    {
        rear_temp->num += sign2 * number2->num + carry;
        carry = 0;
//plus the carry, and then return it to 0.
        if(rear_temp->num < range_min && rear_temp != target.head->next)
        {
            rear_temp->num += 10000;
            carry = -1;
        }
        if(rear_temp->num >range_max && rear_temp != target.head->next)
        {
            rear_temp->num -= 10000;
            carry = 1;
        }
        //�����ʱѭ�����˽���ĵ�һ���ڵ㣬����ʱ�ýڵ�ľ���ֵ���ڵ���10000����ʱ�Ѿ�û����ǰ��һλ���Խ��ˣ������½�һ���ڵ㲢����
        int abs_temp = rear_temp->num > 0 ? rear_temp->num : (rear_temp->num * -1);
        if(abs_temp >=10000 && rear_temp == target.head->next)
        {
            node *temp = new node;
            node *temp1 = target.head->next;
            temp->num = 1;
            temp1->num -= -carry_ini * 10000;
            target.head->next = temp;
            temp->prev = target.head;
            temp1->prev = temp;
            temp->next = temp1;
        }
//if the fist number >= 10000, then build a new node.
        rear_temp = rear_temp->prev;
        number2 = number2->prev;
//iteration of number2 and rear_temp
    }
    //�ڶ���ѭ����Ҫ���number2�������number2����С��number1����ô�п�����Ȼ������number2��������λδ��
    if (judge == 0)
    {
    rear_temp->num += carry;
    }
    return target;
}

longlongint longlongint::operator * (longlongint &another)
{

    int judge = *this < another;
    longlongint target = judge==2 ? *this : another;    //bigger
    longlongint other = judge==2 ? another : *this;     //smaller

    int sign2 = other.head->num;
    longlongint number1(1),number2(2);
    std::string temp = sign2 == 1? "-1":"1";
    number1.get(temp);
    number2.get("0");
    longlongint adder = target;
    other = (other + number1);
    while(other<number2 != 2)
    {
        target = target + adder;
        other = (other + number1);
    }
    return target;
}

longlongint& longlongint::operator=(const longlongint& target)
{
    node *temp = target.head;//temp���ڱ���target�еĸ��ڵ㣬��������ֵ���и���
    node *temp_rear = target.rear;//temp_rear������tempָ���βʱֹͣ����

    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    currentlength = 0;
    head->num = temp->num;//�½�������ʼ��head��rear�ڵ�

    temp = temp->next;
    node *add = this->head;//add�������½������н����½ڵ�
    while(temp != temp_rear)
    {
        node *link = new node;
        link->num = temp->num;
        add->next = link;
        link->next = this->rear;
        this->rear->prev = link;
        link->prev = add;

        add = add->next;
        temp = temp->next;
        currentlength ++;
    }
    longlongint result1(target);
    return result1;
}

//���رȽϺ�����ֻ�ȽϾ���ֵ��
int longlongint::operator < (const longlongint &number)
{
    //��������Ȼ����ֵ�������ﱾ����������Ŀд������ϧ�ִ��ڵ���С���������
    if(this->currentlength < number.currentlength){return 1;}
    else{;}
    if(this->currentlength > number.currentlength){return 0;}
    else{;}
    //���������ȣ���ǰ������������һֱ��ȣ��Ǿ����
    node* number1 = this->head->next;
    node* number2 = number.head->next;
    for (int i = 1; i <= currentlength; i++)
    {
        if (number1->num != number2->num)
        {
            return (number1->num < number2->num)? 1:0;
        }
        else
        {
            number1 = number1->next;
            number2 = number2->next;
        }
    }
    return 2;
}
