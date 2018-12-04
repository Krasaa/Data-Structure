#include "linknode.h"
#include "node.h"

std::ostream & operator <<(std::ostream &os,const linknode &target)
{
    node *temp = target.head->next;
    int flag = 0;
    for (int k = 0; k < target.length; k++)
    {
        if(temp->cterm>0 && temp != target.head->next && flag != 0){os<<"+";}
        if(temp->cterm == 1 && temp->eterm != 1 && temp->eterm != 0)
        {
            os<< "X^" << temp->eterm;
            temp = temp->next;
            flag++;
            continue;
        }
        if(temp->cterm == -1 && temp->eterm != 1 && temp->eterm != 0)
        {
            os<< "-X^" << temp->eterm;
            temp = temp->next;
            flag++;
            continue;
        }
        if(temp->cterm == 0 && k == target.length-1 && flag == 0)
        {
            os<<"0";
            break;
        }
        if(temp->cterm == 0)
        {
            temp = temp->next;
            continue;
        }
        if(temp->cterm == 1 && temp->eterm == 1)
        {
            os<<"X";
            temp = temp->next;
            flag++;
            continue;
        }
        if(temp->cterm == -1 && temp->eterm == 1)
        {
            os<<"-X";
            temp = temp->next;
            flag++;
            continue;
        }
        if(temp->eterm == 0)
        {
            os<<temp->cterm;
            temp = temp->next;
            flag++;
            continue;
        }
        if(temp->eterm ==1)
        {
            os<<temp->cterm<<"X";
            temp = temp->next;
            flag++;
            continue;
        }
        os<<temp->cterm<<"X^"<<temp->eterm;
        flag++;
        if(temp != target.rear)
        {
            temp = temp->next;
        }
    }
    return os;
}


linknode::linknode(double *c, int *e, int n)
{
    length = n;
    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    for (int k = 0; k < n; k++)
    {
        node *temp = new node;
        temp->cterm = c[k];
        temp->eterm = e[k];
        temp->next = rear;
        temp->prev = rear->prev;
        rear->prev->next = temp;
        rear->prev = temp;
    }
}

linknode::~linknode()
{
    node* temp = head;
    while(temp != rear)
    {
        node * temp1 = temp;
        temp = temp->next;
        delete temp1;
    }
    delete rear;
}

linknode::linknode(const linknode &a)
{
    length = a.length;
    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    node* iter = a.head->next;

    while (iter != a.rear)
    {
        node *temp = new node;
        temp->cterm = iter->cterm;
        temp->eterm = iter->eterm;
        temp->next = rear;
        temp->prev = rear->prev;
        rear->prev->next = temp;
        rear->prev = temp;
        iter = iter->next;
    }
}


linknode linknode::operator+(linknode &another)
{
    int k = length + another.length;
    double *c = new double[k]{0};
    int *e = new int [k]{0};
    linknode result(c,e,k);
    result.length = 0;
    node* iter_this, *iter_another, *iter_target;
    iter_this = this->head->next;
    iter_another = another.head->next;
    iter_target = result.head->next;

    for (int iter = 0; iter < k; iter++)
    {

        if(iter_this == this->rear || iter_another == another.rear)
        {
            if(iter_this == this->rear)
            {
                while(iter_another != another.rear)
                {
                    iter_target ->cterm = iter_another->cterm;
                    iter_target->eterm = iter_another->eterm;
                    iter_target = iter_target->next;
                    iter_another = iter_another->next;
                    result.length++;
                }
                break;
            }
            else
            {
                while(iter_this != this->rear)
                {
                    iter_target -> cterm = iter_this->cterm;
                    iter_target -> eterm = iter_this->eterm;
                    iter_target = iter_target->next;
                    iter_this = iter_this->next;
                    result.length++;
                }
                break;
            }
        }
        if(iter_this->eterm != iter_another->eterm)
        {
            int judge = iter_this->eterm > iter_another->eterm;
            iter_target->cterm = (judge == 1)? iter_this->cterm : iter_another->cterm;
            iter_target->eterm = (judge == 1)? iter_this->eterm : iter_another->eterm;
            iter_target = iter_target->next;
            iter_this = (judge == 1) ? iter_this->next : iter_this;
            iter_another = (judge == 1) ? iter_another : iter_another->next;
            result.length++;
            continue;
        }
        else
        {
            iter_target->cterm = iter_this->cterm + iter_another->cterm;
            iter_target->eterm = iter_another->eterm;
            iter++;
            result.length++;
            iter_another = iter_another->next;
            iter_this = iter_this->next;
            iter_target = iter_target->next;
            continue;
        }
    }

    while(iter_target != result.rear)
    {
        node * temp = iter_target;
        iter_target = iter_target->next;
        temp->prev->next = iter_target;
        iter_target->prev = temp->prev;
        delete temp;
    }
    return result;
}

linknode linknode::operator-(linknode &another)
{
    double * sizeofit1 = new double [another.length];//c
    int * sizeofit2 = new int [another.length];//e
    linknode result(sizeofit1,sizeofit2,another.length);
    node* iter_this= another.head->next;
    node* iter_target = result.head->next;

    while(iter_this!=another.rear)
    {
        iter_target->cterm = -1 * iter_this->cterm;
        iter_target->eterm = iter_this->eterm;
        iter_target = iter_target->next;
        iter_this = iter_this->next;
    }
    return *this + result;
}


linknode& linknode::operator=(const linknode &a)
{
    length = a.length;
    head = new node;
    head->next = rear = new node;
    rear->prev = head;
    node* iter = a.head->next;

    while (iter != a.rear)
    {
        node *temp = new node;
        temp->cterm = iter->cterm;
        temp->eterm = iter->eterm;
        temp->next = rear;
        temp->prev = rear->prev;
        rear->prev->next = temp;
        rear->prev = temp;
        iter = iter->next;
    }
    linknode result(a);
    return result;
}

linknode linknode::sortme()
{
    double * sizeofit1 = new double [length];//c
    int * sizeofit2 = new int [length];//e
    int temp = this->head->next->eterm;
    linknode result(sizeofit1,sizeofit2,length);
    node* iter_this= this->head->next;
    node* iter_target = result.head->next;

    iter_target->cterm = iter_this->cterm;
    iter_target->eterm = iter_this->eterm;
    for (int k = 0;k < length; k++)
    {
        if(iter_this->eterm > temp)
        {
            temp = iter_this->eterm;
            iter_target->cterm = iter_this->cterm;
            iter_target->eterm = iter_this->eterm;
        }
        iter_this = iter_this->next;
    }
    if(length == 1){return result;}

    int e_temp = temp;
    double c_temp = 0;
    for (int k =0; k < length -1; k++)
    {
        iter_target = iter_target->next;
        iter_this = this->head->next;
        int last_biggest = e_temp;
        int flag = 0;
        for (int b = 0; b < length; b++)
        {
            if(iter_this->eterm < e_temp && flag == 0)
            {
                e_temp = iter_this->eterm;
                c_temp = iter_this->cterm;
                flag = 1;
            }
            if(iter_this->eterm > e_temp && iter_this->eterm < last_biggest && flag == 1)
            {
                e_temp = iter_this->eterm;
                c_temp = iter_this->cterm;
            }
            iter_this = iter_this->next;
        }
        iter_target->eterm = e_temp;
        iter_target->cterm = c_temp;
    }
    return result;
}

void linknode::simplify()
{
    if(length == 1){return;}
    node* temp1 = this->head->next;
    node* temp2 = temp1->next;
    while(temp1 != this->rear)
    {
        temp2 = temp1->next;

        while(temp2 != this->rear)
        {
            int flag = 0;
            if(temp1->eterm == temp2->eterm)
            {
                temp1->cterm = temp1->cterm + temp2->cterm;
                temp2->prev->next = temp2->next;
                temp2->next->prev = temp2->prev;
                length--;
                node* dele = temp2;
                temp2 = temp2->next;
                flag = 1;
                delete dele;
            }
            temp2 = flag == 1? temp2 : temp2->next;
        }
        temp1 = temp1->next;
    }
}

linknode linknode::derivate()
{
    double * sizeofit1 = new double [length];//c
    int * sizeofit2 = new int [length];//e
    linknode result(sizeofit1,sizeofit2,length);
    node* iter_this= this->head->next;
    node* iter_target = result.head->next;
    int flag = 0;
    while(iter_this != this->rear)
    {
        iter_target->cterm = iter_this->cterm * iter_this->eterm;
        iter_target->eterm = iter_this->eterm - 1;
        if(iter_this != this->rear->prev)
        {
            iter_this = iter_this->next;
            iter_target = iter_target->next;
            continue;
        }
        break;
    }
    return result;
}
