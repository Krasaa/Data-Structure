#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED



class node {
public:
    node *next;//指向前节点
    node *prev;//指向后节点
//int num = 0;(It is valid in codeblocks while it should be invalid)
    int num;//存储数字
//store the number and the next node
    node();  //构造新的节点
};


#endif // NODE_H_INCLUDED
