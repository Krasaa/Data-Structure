#include<string>
#include<iostream>
#include"longlongint.h"
#include "node.h"

//initialize the link list
//构造函数，初始化各参数与头尾节点
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

//拷贝构造函数，返回一个完全新开辟的、各节点值完全相等的新链表
longlongint::longlongint(const longlongint &target)
{
    node *temp = target.head;//temp用于遍历target中的各节点，并对其中值进行复制
    node *temp_rear = target.rear;//temp_rear用于在temp指向表尾时停止遍历

    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    currentlength = 0;
    head->num = temp->num;//新建链表并初始化head、rear节点

    temp = temp->next;
    node *add = this->head;//add用于在新建链表中接入新节点
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

//get函数用于对longlongint对象进行赋值，得到一个各节点存储四个数字的链表
void longlongint::get(std::string number)//参数为输入的字符串
{
    int change = int(number.find(';'));//确定输入字符串中’;’的位置
//the position of ';'
    int start = ranking ==1? 0:change + 1;
    int ending = ranking ==1? change - 1 : number.length()-2;
//根据ranking的值对字符串进行不同的划分：
//如果ranking为1，则取;前的部分，如果ranking为2，则取;后的部分
//get the beginning and the ending for each number
    if (number[start] == '-')
        {
            head->num = -1;
            start++;
        }//单独考虑负号，如果有，则输入头节点
    number = number.substr(start,ending - start + 1);//根据ranking取相应子链
//get the target substring
//whether the number is positive or not
    node* temp = new node;
    rear->next = temp;
    temp->prev = rear;
    rear = rear->next;
    currentlength ++;                           //先接入一个节点
    int flag = 0;
    int tens[] = {1,10,100,1000};
    //flag用于选取tens种所要乘的数，例如 5879  = 5*1000+8*100+7*10+9
    while(number.length() != 0)
    {
        int length = number.length() - 1;
        if(number[length] == ',')
            //输入中的,分隔了四个数字，依此进行遍历，遍历方法为：对每个位上的数字乘上它应
            //有的权值，并求和如 5879  = 5*1000+8*100+7*10+9
            {   number.erase(length);//擦去,，并接入一个新的节点
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
        number.erase(length);   //每加上一位数字，就擦去一位
        flag ++;
    }
}

//重载输出函数，以人类的习惯输出链表中的数字
std::ostream & operator << (std::ostream & out , longlongint &number)
{
    if(number.head->num == -1){out << '-';}//如果为负，输出一个-
    int tens[4] =  {1000,100,10,1};
    //以下循环防止了 将1输出为0001 这种多余0出现的情况，即将链表从前向后遍历，
    //跳过值为0的节点
    while(number.head->next->num == 0 && number.currentlength != 1)
    {
        node *temp1 = number.head->next;
        number.head->next = temp1->next;
        temp1->next->prev = number.head;
        delete temp1;
        number.currentlength--;
    }
    node *temp = number.head->next;
    //对链表遍历，输出所有节点的数字的绝对值（绝对值是为了完善后面减法的实现）
    //此外，每4个数字遍历一次保证了 10010 不会输出为110（防止直接输出int类型丢失前面应有的0）
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


    //绝对值相等，符号相反，返回0
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

    //结果的符号等于绝对值大者的符号
    target.head->num = judge==1? another.head->num:this->head->num;

    int range_max;
    int range_min;
    range_max = target.head->num ==1? 9999:0;
    range_min = target.head->num ==1? 0:-9999;
    int carry_ini = -target.head->num;

    //构造一个足够大的链表，以装下结果，构建的链表长为 max(length) + 1
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

    //将number1的值从后向前赋值入target中，相当于 target + number1
    while (number1 != this->head)
    {
        rear_temp->num += sign1 * number1->num;
        rear_temp = rear_temp->prev;
        number1 = number1->prev;
    }
    rear_temp = target.rear->prev;

    //将target + number1 再从后向前加上number2
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
        //如果此时循环到了结果的第一个节点，但此时该节点的绝对值大于等于10000，此时已经没有再前面一位可以进了，于是新建一个节点并存入
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
    //第二个循环主要针对number2，但如果number2长度小于number1，那么有可能虽然遍历了number2，但仍有位未进
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
    node *temp = target.head;//temp用于遍历target中的各节点，并对其中值进行复制
    node *temp_rear = target.rear;//temp_rear用于在temp指向表尾时停止遍历

    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    currentlength = 0;
    head->num = temp->num;//新建链表并初始化head、rear节点

    temp = temp->next;
    node *add = this->head;//add用于在新建链表中接入新节点
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

//重载比较函数，只比较绝对值！
int longlongint::operator < (const longlongint &number)
{
    //更长的显然绝对值更大，这里本来打算用三目写，但可惜分大于等于小于三种情况
    if(this->currentlength < number.currentlength){return 1;}
    else{;}
    if(this->currentlength > number.currentlength){return 0;}
    else{;}
    //如果长度相等，从前往后遍历，如果一直相等，那就相等
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
